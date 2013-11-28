#include "forestgen.h"

#include "dungeon.h"
#include "rand.h"
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

double munge(double a) {
    return (a < 0) ? -pow(-a, 2/3.) : pow(a, 2/3.);
}

// Generate a random number in the interval [a, b),
// biased toward the edges of the interval.
int bias(int a, int b) {
    const double m = (munge(rnd.dbl(-1, 1)) + 1) / 2;
    const int r = m * (b - a) + a;
    if (r == b) return b-1;
    return r;
}

Dungeon ForestGen::gen() {
    vector<vector<Tile> > m(height, vector<Tile>(width, Floor));

    const int numTrees = height * width / 4;
    for (int i = 0; i < numTrees; ++i) {
        m[bias(0, height)][bias(0, width)] = Tree;
    }

    for (int y = 0; y < height; ++y) {
        m[y][0] = m[y][width - 1] = Tree;
    }
    for (int x = 0; x < width; ++x) {
        m[0][x] = m[height - 1][x] = Tree;
    }

    Dungeon dungeon(m);
    // Make sure the dungeon is connected.
    if (dungeon.numRooms() > 1) throw LevelGen::GenerationError();
    return dungeon;
}
