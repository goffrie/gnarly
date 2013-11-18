#ifndef __LEVEL_OBJECT_H__
#define __LEVEL_OBJECT_H__

#include "displayable.h"
#include "levelobjectvisitor.h"
#include "util.h"

// An abstract class representing any object
// (whether a monster, player, or item)
// that has a position in a Level.

class Level;

class LevelObject : public Displayable {
public:
    friend class Level;
    Level* level;
    // The item's position.
    int y, x;

    // The item's ASCII tile.
    virtual char tile() const = 0;

public:
    LevelObject(int y = -1, int x = -1) : level(0), y(y), x(x) { }
    virtual ~LevelObject() { }

    virtual void draw(UI& ui) const override;

    int getY() const { return y; }
    int getX() const { return x; }

    void moveTo(int y, int x);
    void moveRelative(Direction d);
    virtual bool canMove(int y, int x);

    virtual void accept(LevelObjectVisitor& v) { v.visit(*this); }
};

#endif
