#ifndef __AGGREGATION_GEN_H__
#define __AGGREGATION_GEN_H__

#include "levelgen.h"

// Generates a cave-like level through aggregation generation
class AggregationGen : public LevelGen {
protected:
    virtual Dungeon gen();
public:
    AggregationGen(int h, int w) : LevelGen(h, w) { }
};

#endif
