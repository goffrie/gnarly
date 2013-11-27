#ifndef __LEVEL_OBJECT_H__
#define __LEVEL_OBJECT_H__

#include "displayable.h"
#include "direction.h"
#include "language.h"
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
    Level* level;
    // The item's position.
    int y, x;

protected:
    // Returns all free adjacent locations.
    virtual std::vector<std::pair<int, int> > getFreeAdjacent();

public:
    // The item's ASCII tile.
    virtual char tile() const = 0;

    LevelObject() : level(0), y(-1), x(-1) { }
    virtual ~LevelObject();

    virtual void draw(Surface& target) const override;

    int getY() const { return y; }
    int getX() const { return x; }
    void setPos(int y, int x);

    Level* getLevel() const { return level; }

    // TODO: throw an exception instead of returning bool?
    // Returns true if the movement succeeded.
    bool moveTo(int y, int x);
    virtual bool moveRelative(Direction d);
    virtual void step();
    virtual bool canMove(int y, int x);
    virtual bool isEnemy(Team* t) const;
    virtual bool canPickUp() { return false; }
    virtual bool isItem() { return false; }
    virtual bool dead() const { return false; }

    virtual void accept(LevelObjectVisitor& v);
};

#endif
