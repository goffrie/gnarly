#ifndef __AGGREGATION_GEN_H__
#define __AGGREGATION_GEN_H__

#include "dungeongen.h"

class AggregationGen : public DungeonGen {
protected:
    virtual Dungeon gen() override;
public:
    AggregationGen(int h, int w) : DungeonGen(h, w) { }
};

#endif
