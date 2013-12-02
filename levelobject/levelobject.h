#ifndef __LEVEL_OBJECT_H__
#define __LEVEL_OBJECT_H__

#include "displayable.h"
#include "direction.h"
#include "object.h"

#include <vector>
#include <string>

// An abstract class representing any object
// (whether a monster, player, or item)
// that has a position in a Level.

class Level;
class LevelObjectVisitor;
class Team;

class LevelObject : public Displayable, public Object {
    friend class Level;
    // The level it belongs to
    Level* level;
    // The item's position.
    int y, x;

protected:
    // Returns all free adjacent locations.
    virtual std::vector<std::pair<int, int> > getFreeAdjacent();
    // Moves to a location. Called after placement on a level
    bool moveTo(int y, int x);

public:
    // The item's ASCII tile.
    virtual char tile() const = 0;

    LevelObject() : level(0), y(-1), x(-1) { }
    virtual ~LevelObject();

    virtual void draw(Surface& target) const;

    // Accessor methods for basic LevelObject properties
    int getY() const { return y; }
    int getX() const { return x; }
    Level* getLevel() const { return level; }

    // Changes the position of self. Should only be called before being placed onto a level
    void setPos(int y, int x);

    // Returns true if the movement succeeded.
    virtual bool moveRelative(Direction d);
    // Takes any action. By default, nothing
    virtual void step();
    // Whether on not a position is a valid for this LevelObject
    virtual bool canMove(int y, int x);
    // Returns true of the other team is not allied
    virtual bool isEnemy(Team* t) const;
    // Basic accessors for properties of the object
    // XXX Are these necessary?
    virtual bool canPickUp() { return false; }
    virtual bool isItem() { return false; }
    virtual bool dead() const { return false; }
    // Visits a LevelObjectVisitor
    virtual void accept(LevelObjectVisitor& v);
};

#endif
