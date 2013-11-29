#include "roomsgen.h"

#include "dungeon.h"
#include "util.h"
#include "rand.h"
#include "ui.h"

#include <vector>
#include <cassert>
#include <cmath>
#include <iostream>

using namespace std;

typedef vector<vector<Tile> > Map;

// Implements the disjoint-set forest data structure, with path compression.
class UnionFind {
    vector<int> parent_;
    int components_;
public:
    UnionFind(int n) : parent_(n), components_(n) {
        for (int i = 0; i < n; ++i) parent_[i] = i;
    }
    int parent(int a) {
        //cerr << a << endl;
        if (parent_[a] != a) parent_[a] = parent(parent_[a]);
        return parent_[a];
    }
    void join(int a, int b) {
        a = parent(a); b = parent(b);
        if (a != b) {
            parent_[a] = b;
            --components_;
        }
    }
    bool same(int a, int b) {
        return parent(a) == parent(b);
    }
    int components() const {
        return components_;
    }
};

// Returns a number in [lo, hi), biased toward `lo`.
inline int smallRnd(int lo, int hi) {
    const double x = rnd.dbl(0, 1);
    const int r = floor(x * x * (hi - lo)) + lo;
    if (r >= hi) return hi-1;
    return r;
}

// Returns the sign of a: 1, 0, or -1.
inline int sgn(int a) {
    return (a > 0) - (a < 0);
}

Dungeon RoomsGen::gen() {
    assert(width > 12 && height > 10);

    int area = 0;
    const int wanted = width * height / 2;

    // We use trees as marker tiles here.
    Map m(height, vector<Tile>(width, Tree));
    vector<vector<int> > room(height, vector<int>(width, -1));
    vector<pair<int, int> > rooms;

    int tries = 10000;

    while (area < wanted) {
        // Don't spin too hard.
        if (--tries <= 0) throw LevelGen::GenerationError();

        // Place a room.
        int w, h;
        switch (rnd(0, 40)) {
            case 0: // small room
                w = rnd(6, 17);
                h = rnd(4, w * 3 / 5 + 2);
                break;
            default: // medium-sized room
                w = smallRnd(12, 23);
                h = smallRnd(8, w * 4 / 5);
                break;
                /*
            case 39: // big room
                w = rnd(width / 3, width * 2 / 3);
                h = rnd(height / 3, height * 2 / 3);
                if ((h-w)*(height-width) < 0) swap(w, h);
                break;
                */
        }
        // x + w < width - 1
        const int x = rnd(1, width - w),
                  y = rnd(1, height - h);

        // Make sure the area is clear.
        bool ok = true;
        for (int dy = 0; ok && dy < h; ++dy) {
            for (int dx = 0; ok && dx < w; ++dx) {
                if (m[y+dy][x+dx] != Tree) {
                    ok = false;
                }
            }
        }
        if (!ok) continue;

        // Carve it out.
        rect(m, y-1, x-1, h+2, w+2, Rock);
        rect(m, y, x, h, w, Floor);
        rect(m, y, x, 1, w, WallH);
        rect(m, y+h-1, x, 1, w, WallH);
        rect(m, y, x, h, 1, WallV);
        rect(m, y, x+w-1, h, 1, WallV);

        // Mark the corners of the room.
        m[y][x] = Door;
        m[y+h-1][x] = Door;
        m[y+h-1][x+w-1] = Door;
        m[y][x+w-1] = Door;

        // Record the room.
        rect(room, y, x, h, w, static_cast<int>(rooms.size()));
        rooms.push_back(make_pair(y + h/2, x + w/2));

        area += h * w;
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (m[y][x] == Tree) m[y][x] = Rock;
            else if (m[y][x] == Door) m[y][x] = Tree;
        }
    }

    tries = 1000;

    // Keep track of the connections between rooms.
    UnionFind con(rooms.size());
    while (con.components() > 1) {
        const int a = rnd(0, rooms.size()),
                  b = rnd(0, rooms.size());
        if (con.same(a, b)) continue;
        if (--tries <= 0) throw LevelGen::GenerationError();
        const int y1 = rooms[a].first,
                  x1 = rooms[a].second,
                  y2 = rooms[b].first,
                  x2 = rooms[b].second;

        // Check the path.
        const int dy = sgn(y2 - y1), dx = sgn(x2 - x1);
        int y = y1, x = x1;
        bool ok = true;
        for (; ok && (y != y2 || x != x2); (y == y2) ? (x += dx) : (y += dy)) {
            // Avoid passing through the corner of a room.
            if (m[y][x] == Tree) {
                ok = false;
            }
            // Avoid placing adjacent corridors, because that looks bad.
            if (y == y2) {
                if (m[y+1][x] == Passage || m[y+1][x] == Door
                || m[y-1][x] == Passage || m[y-1][x] == Door) ok = false;
            } else {
                if (m[y][x+1] == Passage || m[y][x+1] == Door
                || m[y][x-1] == Passage || m[y][x-1] == Door) ok = false;
            }
        }
        if (!ok) continue;

        // Carve the path.
        y = y1;
        x = x1;

        int currentRoom = a;
        for (; y != y2 || x != x2; (y == y2) ? (x += dx) : (y += dy)) {
            if (m[y][x] == WallH || m[y][x] == WallV) m[y][x] = Door;
            else if (m[y][x] == Rock) m[y][x] = Passage;
            const int thisRoom = room[y][x];
            if (thisRoom != currentRoom && thisRoom >= 0) {
                // Join rooms that we go through.
                con.join(currentRoom, thisRoom);
                currentRoom = thisRoom;
            }
        }
    }

    // Fix the corners of rooms to not be trees.
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (m[y][x] == Tree) m[y][x] = WallV;
        }
    }

    if (outdoor) {
        // Make the map "outdoor"-like.
        rect(m, 0, 0, 1, width, WallH);
        rect(m, height-1, 0, 1, width, WallH);
        rect(m, 0, 0, height, 1, WallV);
        rect(m, 0, width-1, height, 1, WallV);
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                if (m[y][x] == Rock) m[y][x] = Floor;
            }
        }
    }

    return Dungeon(m);
}
