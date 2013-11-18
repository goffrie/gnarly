#ifndef __DUNGEON_H__
#define __DUNGEON_H__

#include "displayable.h"

#include <vector>
#include <utility>

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
    std::vector<std::vector<int> > rooms;
    int numberRooms;
    Dungeon() { }
public:
    virtual void draw(UI& grid) const override;

    unsigned int height() const { return grid.size(); }
    unsigned int width() const { return grid[0].size(); }

    Tile tileAt(int y, int x) const { return grid[y][x]; }

    bool inSameRoom(int y1, int x1, int y2, int x2);
    std::pair<int,int> randomPlacement();
    void loadRooms();
    void floodfill(unsigned int y, unsigned int x, int n);

    static Dungeon defaultDungeon();
    static Dungeon loadDungeon(const char* dungeonStr);
};

#endif
