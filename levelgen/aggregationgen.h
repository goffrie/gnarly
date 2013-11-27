#ifndef __AGGREGATION_GEN_H__
#define __AGGREGATION_GEN_H__

#include "levelgen.h"

class AggregationGen : public LevelGen {
protected:
    virtual Dungeon gen() override;
public:
    AggregationGen(int h, int w) : LevelGen(h, w) { }
};

#endif
