#include "aggregationgen.h"

#include "dungeon.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cassert>
#include "ui.h"

using namespace std;

// 0 = rock, 1 = passage, 2 = floor
typedef vector<vector<int> > Map;

int diffuse(Map& m, int h, int w, int y, int x, int rH, int rW, int val) {
    int limit = 1000000;
    for (int dy = 0; dy < rH; ++dy) for (int dx = 0; dx < rW; ++dx) {
        if (m[y+dy][x+dx]) {
            // TODO: what to do here?
//            goto gen;
            return 0;
        }
    }
    while (1) {
        if (--limit <= 0) {
            throw DungeonGen::GenerationError();
        }
        int cy, cx;
        // Pick a direction.
        switch (rand() % 4) {
            case 0: cy = -1; cx = 0; break; // up
            case 1: cy = 1; cx = 0; break; // down
            case 2: cy = 0; cx = -1; break; // left
            case 3: cy = 0; cx = 1; break; // right
        }
        // Sanity check.
        if (y + cy < 1 || x + cx < 1 || y + cy + rH >= h - 1 || x + cx + rW >= w - 1) {
            // try again
            continue;
        }
        // Check for aggregation.
        int off = (cy == 0) ? (cx < 0) ? x-1 : (x+rW) : (cy < 0) ? y-1 : (y+rH);
        int on1 = (cy == 0) ? y : x;
        int on2 = (cy == 0) ? y + rH : (x + rW);
        int& Y = (cy == 0) ? on1 : off;
        int& X = (cx == 0) ? on1 : off;
        bool stick = false;
//        cerr << y << ',' << x << ':' << rH << ',' << rW << '&' << cy << ',' << cx << endl;
        for (; on1 < on2; ++on1) {
//            cerr << Y << ';' << X << endl;
            if (m[Y][X]) {
                stick = true;
                break;
            }
        }
        if (stick) break;
        y += cy;
        x += cx;
    }
gen:
    int n = 0;
    for (int dy = 0; dy < rH; ++dy) for (int dx = 0; dx < rW; ++dx) {
        if (!m[y+dy][x+dx]) {
            m[y+dy][x+dx] = max(m[y+dy][x+dx], val);
            ++n;
        }
    }
    return n;
}

Dungeon AggregationGen::gen(int height, int width) {
    assert(height > 12 && width > 12);
    // Initialize with all rock.
    Map m(height, vector<int>(width, 0));

    // Add a seed.
    m[height/2][width/2] = 2;

    // Aggregate rectangles.
    int tilesFilled = 1;
    while (tilesFilled < (height * width) / 2) {
        // rectangle size
        int rH, rW, val;
        switch (rand() % 3) {
            case 0: // horizontal corridor
                rH = 1; rW = rand() % 6; val = 1; break;
            case 1: // vertical corridor
                rW = 1; rH = rand() % 6; val = 1; break;
            case 2: // room
                rW = rand() % 8 + 3; rH = rand() % 8 + 3; val = 2; break;
        }
        // initial position
        int y = rand() % (height - rH - 2) + 1;
        int x = rand() % (width - rW - 2) + 1;
        tilesFilled += diffuse(m, height, width, y, x, rH, rW, val);
    }

    vector<vector<Tile> > result(height, vector<Tile>(width, Rock));
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (m[y][x] < 1) continue;
            int bit = 0;
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    if (dy == 0 && dx == 0) continue;
                    const int ny = y + dy, nx = x + dx;
                    if (ny >= 0 && ny < height && nx >= 0 && nx < width && m[ny][nx] < 1) {
                        m[ny][nx] -= 1 << bit;
                    }
                    ++bit;
                }
            }
        }
    }
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            switch (m[y][x]) {
                case 1: result[y][x] = Passage; break;
                case 2: result[y][x] = Floor; break;
            }
            if (m[y][x] < 0) {
                int flags = -m[y][x];
                if ((flags & 8) || (flags & 16) || !((flags & 2) || (flags & 64))) {
                    result[y][x] = WallV;
                } else {
                    result[y][x] = WallH;
                }
            }
        }
    }
    return Dungeon(result);
}
