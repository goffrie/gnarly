#ifndef __CONSTANT_GEN_H__
#define __CONSTANT_GEN_H__

#include "levelgen.h"
#include "dungeon.h"

class ConstantGen : public LevelGen {
    const Dungeon& d;
public:
    ConstantGen(const Dungeon& d) : LevelGen(d.height(), d.width()), d(d) { }
    virtual Dungeon gen() override { return d; }
};

#endif
