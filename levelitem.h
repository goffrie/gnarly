#ifndef __LEVEL_ITEM_H__
#define __LEVEL_ITEM_H__

#include "displayable.h"

// An abstract class representing any object
// (whether a monster, player, or item)
// that has a position in a Level.

class Level;

class LevelItem : public Displayable {
    friend class Level;
    Level* level;
    // The item's position.
    int y, x;

public:
    // The item's ASCII tile.
    virtual char tile() const = 0;

public:
    LevelItem(int y = -1, int x = -1) : y(y), x(x) { }
    virtual ~LevelItem() { }

    virtual void draw(UI& ui) const override;

    int getY() const { return y; }
    int getX() const { return x; }

    void moveTo(int y, int x);
};

#endif
