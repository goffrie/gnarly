#ifndef __FOREST_GEN_H__
#define __FOREST_GEN_H__

#include "levelgen.h"

class ForestGen : public LevelGen {
protected:
    virtual Dungeon gen() override;
public:
    ForestGen(int h, int w) : LevelGen(h, w) { }
};

#endif
