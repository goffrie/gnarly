#include "bspgen.h"
#include "ui.h"

#include "dungeon.h"
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

typedef vector<vector<Tile> > Map;

int rnd(int a, int b) {
    if (a >= b) return a;
    return rand() % (b - a) + a;
}

int tw(int s) {
    cerr << "tw " << s << endl;
    if (s <= 4) return s;
    return rnd(0, s-4) / 2 + 1;
}

void room(Map& m, int y, int x, int h, int w) {
    // twiddle the width
    int twiddle = tw(w);
    w -= twiddle;
    if (twiddle > 0) x += rand() % twiddle + 1;
    // twiddle the height
    twiddle = tw(h);
    h -= twiddle;
    cerr << w << ',' << h << endl;
    if (twiddle > 0) y += rand() % twiddle + 1;
    cerr << x+w << ',' << y+h << endl;
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

void joinV(Map& m, int y, int x, int h, int w) {
}

void joinH(Map& m, int y, int x, int h, int w) {
}

void partition(Map& m, int y, int x, int h, int w) {
    cerr << "partition" << endl;
    if (h * w < rand() % 150 + 200) {
        room(m, y, x, h, w);
        return;
    }
    // h * w >= 150
    int splitAmt = rand() % 30 + 35;
    if (h > 12 && h * 5 + rand() % 70 > w * 3 + rand() % 40) {
        // room is tall: split vertically
        int sp = h * splitAmt / 100;
        partition(m, y, x, sp, w);
        partition(m, y+sp, x, h-sp, w);
        joinV(m, y, x, h, w);
    } else {
        // split horizontally
        int sp = w * splitAmt / 100;
        partition(m, y, x, h, sp);
        partition(m, y, x+sp, h, w-sp);
        joinH(m, y, x, h, w);
    }
}

Dungeon BSPGen::gen(int height, int width) {
    Map grid(height, vector<Tile>(width, Rock));
    partition(grid, 0, 0, height, width);
    cerr << "done" << endl;
    cerr << grid.size() << endl;
    cerr << grid[0].size() << endl;
    Dungeon r(grid);
    r.draw(*UI::instance());
    UI::instance()->redraw();
    return r;
}
