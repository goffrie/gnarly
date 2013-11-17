#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "displayable.h"

#include <vector>

class Dungeon;
class LevelItem;

class Level : public Displayable {
    // The base dungeon layout. Not owned by this class.
    Dungeon& dungeon;

    // A catalogue of the things on this level,
    // indexed by their location.
    std::vector<std::vector<LevelItem*> > grid;

    // All the items owned by this level.
    // This includes everything except the player.
    std::vector<LevelItem*> items;

public:
    Level(Dungeon& dungeon);
    ~Level();

    unsigned int height() const { return grid.size(); }
    unsigned int width() const { return grid[0].size(); }

    // Add something to the level. `own` controls whether the level
    // should take ownership of it.
    void add(LevelItem* i, bool own = true);

    // Move something on this level to the given position.
    void move(LevelItem* i, int y, int x);

    // Check if a position is free (i.e. there is
    // nothing in that location).
    bool free(int y, int x) const;

    // Check if a location can be moved into
    // (i.e. it has nothing except gold).
    bool movable(int y, int x) const;
};

#endif
