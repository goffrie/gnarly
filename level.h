#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "displayable.h"
#include "dungeon.h"
#include "player.h"
#include "randomspawn.h"

#include <vector>
#include <set>

class LevelObject;
class Memory;

// Represents a single dungeon floor in the game
class Level : public Displayable {
    // The number of the current level (how many levels have passed + 1)
    static int currentLevel;
    enum { lastLevel = 8 };

    // The base dungeon layout. Owned by this class.
    Dungeon dungeon;

    // A catalogue of the things on this level,
    // indexed by their location.
    std::vector<std::vector<LevelObject*> > grid;

    // What tiles are currently visible by the player?
    // Needs to be kept up-to-date using `computeFOV`.
    std::vector<std::vector<bool> > fov;

    // All the items owned by this level.
    // This includes everything except the player.
    std::set<LevelObject*> objects;
    std::vector<Character*> dying;
    std::vector<LevelObject*> adding;

    int numberGold;
    int numberPotions;
    int numberEnemies;

    void removeDead();
    void addStored();

public:
    Level();
    virtual ~Level();

    unsigned int height() const { return grid.size(); }
    unsigned int width() const { return grid[0].size(); }

    void generate(Player* p);

    // Add something to the level. `own` controls whether the level
    // should take ownership of it.
    void add(LevelObject* i, bool own = true);
    void remove(LevelObject* i);

    // Move something on this level to the given position.
    void move(LevelObject* i, int y, int x);
    void notifyDeath(Character* i);
    void notifyAdd(LevelObject* i);

    bool valid(int y, int x) const;

    // Check if a position is free (i.e. there is
    // nothing in that location). A passage or door usually not free
    bool free(int y, int x, bool canGoBetweenRooms = false) const;

    Tile tileAt(int y, int x) const { return dungeon.tileAt(y, x); }
    LevelObject* objectAt(int y, int x) const { return grid[y][x]; }

    // Update the field of view for the player at position (y, x).
    // This method should be called before drawing the level.
    // However, if it is never called, then the whole level
    // will be considered in view.
    void computeFOV(int y, int x, int radius);
    // Draw the parts of the level that the player can see.
    void draw(Surface& target) const override;

    void stepObjects();
    std::vector<LevelObject*> neighbours(int y, int x);
    static int levelCount() { return currentLevel; }
    static void resetLevelCount() { currentLevel = 0; }
    static bool isLastLevel() { return currentLevel == lastLevel; }
};

#endif
