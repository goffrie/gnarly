#include "forestgen.h"

#include "dungeon.h"

#include <cstdlib>
#include <vector>

using namespace std;

Dungeon ForestGen::gen() {
    vector<vector<Tile> > m(height, vector<Tile>(width, Floor));

    const int numTrees = height * width / 8;
    for (int i = 0; i < numTrees; ++i) {
        m[rand() % height][rand() % width] = Tree;
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
