#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "displayable.h"
#include "display.h"
#include "dungeon.h"
#include "player.h"
#include "randomspawn.h"
#include "display.h"

#include <vector>
#include <set>

class LevelObject;
class Memory;

// Represents a single dungeon floor in the game
class Level {
    // The number of the current level (how many levels have passed + 1)
    static int currentLevel;
    enum { lastLevel = 8 };

    // The base dungeon layout. Owned by this class.
    Dungeon dungeon;
    Display* display;

    // A catalogue of the things on this level,
    // indexed by their location.
    std::vector<std::vector<LevelObject*> > grid;

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
    Level(Display* d);
    ~Level();

    unsigned int height() const { return grid.size(); }
    unsigned int width() const { return grid[0].size(); }

    void generate(Player* p);

    // Add something to the level. `own` controls whether the level
    // should take ownership of it. Also, adds to display if owned by level
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

    // Draw the level as seen from the given point of view.
    void drawPOV(int y, int x, int radius, UI& ui, Memory& mem);

    void stepObjects();
    std::vector<LevelObject*> neighbours(int y, int x);
    static int levelCount() { return currentLevel; }
    static void resetLevelCount() { currentLevel = 0; }
    static bool isLastLevel() { return currentLevel == lastLevel; }
};

#endif
