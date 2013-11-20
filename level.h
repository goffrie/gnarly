#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "displayable.h"
#include "display.h"
#include "dungeon.h"
#include "player.h"
#include "randomspawn.h"

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
    std::vector<LevelObject*> objects;

    int numberPotions;
    int numberEnemies;

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
    void remove(LevelObject* i);

    // Move something on this level to the given position.
    void move(LevelObject* i, int y, int x);

    bool valid(int y, int x) const;

    // Check if a position is free (i.e. there is
    // nothing in that location).
    bool free(int y, int x) const;

    Tile tileAt(int y, int x) const { return dungeon.tileAt(y, x); }
    LevelObject* objectAt(int y, int x) const { return grid[y][x]; }

    void stepObjects();
    std::vector<LevelObject*> neighbours(int y, int x);
};

#endif
