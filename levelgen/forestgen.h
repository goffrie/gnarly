#ifndef __FOREST_GEN_H__
#define __FOREST_GEN_H__

#include "levelgen.h"

// A class representing the forest method for generating level.
// Just places trees everywhere
class ForestGen : public LevelGen {
protected:
    // Randomly generates the dungeon
    virtual Dungeon gen();
public:
    ForestGen(int h, int w) : LevelGen(h, w) { }
};

#endif
