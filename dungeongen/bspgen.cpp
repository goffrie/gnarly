#include "bspgen.h"
#include "ui.h"

#include "dungeon.h"
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

typedef vector<vector<Tile> > Map;

class GenerationError{};

int rnd(int a, int b) {
    if (a >= b) return a;
    return rand() % (b - a) + a;
}

int tw(int s) {
    if (s <= 4) return s;
    return rnd(0, s-4) / 2;
}

void room(Map& m, int y, int x, int h, int w) {
    // twiddle the width
    int twiddle = tw(w);
    w -= twiddle;
    if (twiddle > 0) x += rand() % twiddle + 1;
    // twiddle the height
    twiddle = tw(h);
    h -= twiddle;
    if (twiddle > 0) y += rand() % twiddle + 1;
    for (int dy = 0; dy < h; ++dy) {
        for (int dx = 0; dx < w; ++dx) {
            const int ny = y + dy, nx = x + dx;
            if (dx == 0 || dx == w-1) {
                m[ny][nx] = WallV;
            } else if (dy == 0 || dy == h-1) {
                m[ny][nx] = WallH;
            } else {
                m[ny][nx] = Floor;
            }
        }
    }
}

template<int yy, int yx, int xy, int xx>
void join(Map& m, int y, int x, int h, int w, int sp) {
    // XXX macro
    #define M(Y,X) (m[(Y) * yy + (X) * yx][(Y) * xy + (X) * xx])
    // XXX passages can go along walls: no
    vector<pair<int, pair<int, int> > > P;
    for (int dx = 0; dx < w; ++dx) {
        int dy1 = sp;
        while (dy1 < h && M(y+dy1, x+dx) != Floor
                       && M(y+dy1, x+dx) != Passage) ++dy1;
        if (dy1 == h) continue;
        int dy2 = sp;
        while (dy2 >= 0 && M(y+dy2, x+dx) != Floor
                        && M(y+dy2, x+dx) != Passage) --dy2;
        if (dy2 < 0) continue;
        P.push_back(make_pair(dx, make_pair(dy1, dy2)));
        ++dx;
    }
    if (P.size() == 0) throw GenerationError();
    int count = (P.size() > 1) ? !(rand() % 3) + 1 : 1;
    for (int i = 0; count > 0 && i < P.size(); ++i) {
        // P(i) = count / (P.size() - i)
        if (rand() % (P.size() - i) < count) {
            int dx = P[i].first;
            int dy1 = P[i].second.first;
            int dy2 = P[i].second.second;
            for (int dy = dy2+1; dy < dy1; ++dy) {
                if (M(y+dy, x+dx) == WallH || M(y+dy, x+dx) == WallV) {
                    M(y+dy, x+dx) = Door;
                } else {
                    M(y+dy, x+dx) = Passage;
                }
            }
            --count;
        }
    }
}


void joinV(Map& m, int y, int x, int h, int w, int sp) {
    join<1, 0, 0, 1>(m, y, x, h, w, sp);
}
void joinH(Map& m, int y, int x, int h, int w, int sp) {
    join<0, 1, 1, 0>(m, x, y, w, h, sp);
}

void partition(Map& m, int y, int x, int h, int w) {
    if (h * w < rand() % 150 + 200) {
        room(m, y, x, h, w);
        return;
    }
    // h * w >= 150
    int splitAmt = rand() % 30 + 35;
    if (h > 12 && h * 5 + rand() % 70 > w * 3 + rand() % 30) {
        // room is tall: split vertically
        int sp = h * splitAmt / 100;
        partition(m, y, x, sp, w);
        partition(m, y+sp+1, x, h-sp-1, w);
        joinV(m, y, x, h, w, sp);
    } else {
        // split horizontally
        int sp = w * splitAmt / 100;
        partition(m, y, x, h, sp);
        partition(m, y, x+sp+1, h, w-sp-1);
        joinH(m, y, x, h, w, sp);
    }
}

Dungeon BSPGen::gen(int height, int width) {
    while (1) {
        try {
            Map grid(height, vector<Tile>(width, Rock));
            partition(grid, 0, 0, height, width);
            return Dungeon(grid);
        } catch (GenerationError&) {
            // try again
        }
    }
}
