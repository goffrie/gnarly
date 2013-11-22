#ifndef __STAIRCASE_H__
#define __STAIRCASE_H__

#include "levelobject.h"
#include <string>

class Staircase : public LevelObject {
public:
    // Moves down the staircase (and thus to a new level)
    virtual void descend();

    virtual char tile() const override { return '\\'; }

    virtual void accept(LevelObjectVisitor& v);
};

#endif