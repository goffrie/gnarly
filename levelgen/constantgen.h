#ifndef __CONSTANT_GEN_H__
#define __CONSTANT_GEN_H__

#include "levelgen.h"
#include "dungeon.h"

// Generates a constant dungeon: one with a fixed layout
class ConstantGen : public LevelGen {
    const Dungeon& d;
protected:
    // Give them the layout we were given
    virtual Dungeon gen() override { return d; }
public:
    ConstantGen(const Dungeon& d) : LevelGen(d.height(), d.width()), d(d) { }
};

#endif
