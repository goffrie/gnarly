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
    friend class Level;
    Level* level;
    // The item's position.
    int y, x;


public:
    // The item's ASCII tile.
    virtual char tile() const = 0;

    LevelObject(int y = -1, int x = -1) : level(0), y(y), x(x) { }
    virtual ~LevelObject() { }

    virtual void draw(UI& ui) const override;

    int getY() const { return y; }
    int getX() const { return x; }

    Level* getLevel() const { return level; }

    // TODO: throw an exception instead of returning bool?
    // Returns true if the movement succeeded.
    bool moveTo(int y, int x);
    bool moveRelative(Direction d);
    virtual void step();
    virtual bool canMove(int y, int x);

    virtual void accept(LevelObjectVisitor& v) { v.visit(*this); }
};

#endif
