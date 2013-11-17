#ifndef __DUNGEON_H__
#define __DUNGEON_H__

#include "displayable.h"

#include <vector>

enum Tile {
    Floor,
    WallV,
    WallH,
    Door,
    Passage,
    Rock
};

// A dungeon layout.
class Dungeon : public Displayable {
    std::vector<std::vector<Tile> > grid;
    Dungeon() { }
public:
    virtual void draw(UI& grid) const override;

    unsigned int height() const { return grid.size(); }
    unsigned int width() const { return grid[0].size(); }

    static Dungeon defaultDungeon();
    static Dungeon loadDungeon(const char* dungeonStr);
};

#endif
