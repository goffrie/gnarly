#include "aggregationgen.h"

#include "dungeon.h"
#include "rand.h"
#include <iostream>
#include <vector>
#include <cassert>
#include "ui.h"

using namespace std;

// true = carved out, false = rock
typedef vector<vector<bool> > Map;

int diffuse(Map& m, int h, int w, int y, int x, int rH, int rW) {
    int limit = 1000000;
    for (int dy = 0; dy < rH; ++dy) for (int dx = 0; dx < rW; ++dx) {
        if (m[y+dy][x+dx]) {
            // TODO: what to do here?
            goto gen;
            return 0;
        }
    }
    while (1) {
        if (--limit <= 0) {
            throw LevelGen::GenerationError();
        }
        int cy, cx;
        // Pick a direction.
        switch (rnd(0, 4)) {
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
            m[y+dy][x+dx] = true;
            ++n;
        }
    }
    return n;
}

Dungeon AggregationGen::gen() {
    assert(height > 12 && width > 12);
    // Initialize with all rock.
    Map m(height, vector<bool>(width, false));

    // Add a seed.
    m[height/2][width/2] = true;

    // Aggregate rectangles.
    int tilesFilled = 1;
    while (tilesFilled < (height * width) / 2) {
        // rectangle size
        int rH, rW;
        switch (rnd(0, 3)) {
            case 0: // horizontal corridor
                rH = 1; rW = rnd(0, 6); break;
            case 1: // vertical corridor
                rW = 1; rH = rnd(0, 6); break;
            case 2: // room
                rW = rnd(3, 11); rH = rnd(3, 11); break;
        }
        // initial position
        int y = rnd(1, height - rH - 1);
        int x = rnd(1, width - rW - 1);
        tilesFilled += diffuse(m, height, width, y, x, rH, rW);
    }

    return Dungeon(m);
}
