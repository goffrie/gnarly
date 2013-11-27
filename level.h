#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "displayable.h"
#include "dungeon.h"
#include "player.h"

#include <vector>
#include <set>

class LevelObject;
struct LevelImpl;

// Represents a single dungeon floor in the game
class Level : public Displayable {
    // pointer to implementation
    LevelImpl* d;

    void removeDead();
    void addStored();

public:
    Level(Dungeon layout);
    virtual ~Level();

    // Accessor methods.
    unsigned int height() const;
    unsigned int width() const;

    const Dungeon& getDungeon() const;

    Tile tileAt(int y, int x) const;
    LevelObject* objectAt(int y, int x) const;

    // A convenience method: check if the given point
    // lies in [0, height()) x [0, width()).
    bool valid(int y, int x) const;

    // XXX take param
    void loadLayout(Player* p);

    // Add something to the level. `own` controls whether the level
    // should take ownership of it.
    void add(LevelObject* i, bool own = true);
    void remove(LevelObject* i);

    // Move something on this level to the given position.
    void move(LevelObject* i, int y, int x);
    void notifyDeath(Character* i);
    void notifyAdd(LevelObject* i);

    // Check if a position is free (i.e. there is
    // nothing in that location). A passage or door usually not free
    bool free(int y, int x, bool canGoBetweenRooms = false) const;

    // Update the field of view for the player at position (y, x).
    // This method should be called before drawing the level.
    // However, if it is never called, then the whole level
    // will be considered in view.
    void computeFOV(int y, int x, int radius);
    // Draw the parts of the level that the player can see.
    void draw(Surface& target) const override;

    std::vector<LevelObject*> getVisible(int y, int x, int radius) const;

    void stepObjects();
    std::vector<LevelObject*> neighbours(int y, int x);
};

#endif
