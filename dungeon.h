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
    Rock,
    Tree
};

char tileChar(Tile t);

// A dungeon layout.
class Dungeon : public Displayable {
    std::vector<std::vector<Tile> > grid;
    std::vector<std::vector<int> > rooms;
    int roomCount;
public:
    // Initialize a dungeon from a string representation.
    Dungeon(const char* dungeonStr);
    // Initialize a dungeon from a matrix of Tiles.
    Dungeon(std::vector<std::vector<Tile> >& m);
    // Initialize a dungeon from a passable/not passable map.
    // Infers walls. Never produces passages.
    Dungeon(std::vector<std::vector<bool> >& m);

    virtual void draw(Surface& target) const override;

    unsigned int height() const { return grid.size(); }
    unsigned int width() const { return grid[0].size(); }
    int numRooms() const { return roomCount; }

    Tile tileAt(int y, int x) const { return grid[y][x]; }

    bool inSameRoom(int y1, int x1, int y2, int x2) const;
    std::pair<int,int> randomPlacement() const;
    void loadRooms();
    void floodfill(unsigned int y, unsigned int x, int n);

    static Dungeon defaultDungeon();
};

#endif
