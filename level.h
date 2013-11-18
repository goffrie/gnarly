#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "displayable.h"
#include "display.h"
#include "dungeon.h"
#include "player.h"

#include <vector>

class LevelObject;

// Represents a single dungeon floor in the game
class Level {
    // The base dungeon layout. Owned by this class.
    Dungeon dungeon;

    // A catalogue of the things on this level,
    // indexed by their location.
    std::vector<std::vector<LevelObject*> > grid;

    // All the items owned by this level.
    // This includes everything except the player.
    std::vector<LevelObject*> items;

public:
    Level();
    ~Level();

    unsigned int height() const { return grid.size(); }
    unsigned int width() const { return grid[0].size(); }

    void generate(Player* p);

    // Adds all of this level's contents to the display
    void addAllToDisplay(Display* d);

    // Add something to the level. `own` controls whether the level
    // should take ownership of it.
    void add(LevelObject* i, bool own = true);

    // Move something on this level to the given position.
    void move(LevelObject* i, int y, int x);

    // Check if a position is free (i.e. there is
    // nothing in that location).
    bool free(int y, int x) const;

    // Check if a location can be moved into
    // (i.e. it has nothing except gold).
    bool movable(int y, int x) const;
};

#endif
