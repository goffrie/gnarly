#ifndef __STAIRCASE_H__
#define __STAIRCASE_H__

#include "levelobject.h"
#include <string>

// An object representing a staircase. Doesn't actually do anything on its own, going down stairs
// is managed in game
class Staircase : public LevelObject {
public:
    virtual char tile() const override { return '\\'; }
    virtual std::string basicName() const override { return "staircase"; }

    virtual void accept(LevelObjectVisitor& v);
};

#endif
