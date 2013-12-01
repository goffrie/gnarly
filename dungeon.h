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

// Gets a character from a tile, or vice versa
char tileChar(Tile t);
Tile tileFromChar(char c);
// Draws a tile
void drawTile(Tile t, Surface& target, unsigned y, unsigned x);

// A dungeon layout.
class Dungeon : public Displayable {
    std::vector<std::vector<Tile> > grid;
    // A representation of the grid, with every position in given room marked with a number
    std::vector<std::vector<int> > rooms;
    // The number of rooms in the dungeon
    int roomCount;

    // Identifies the rooms in the dungeon, using floodfill
    void loadRooms();
    // Floodfills a room
    void floodfill(unsigned int y, unsigned int x, int n);
public:
    // Initialize a dungeon from a string representation.
    Dungeon(const char* dungeonStr);
    // Initialize a dungeon from a matrix of Tiles.
    Dungeon(std::vector<std::vector<Tile> >& m);
    // Initialize a dungeon from a passable/not passable map.
    // Infers walls. Never produces passages.
    Dungeon(std::vector<std::vector<bool> >& m);

    // Draws the entire dungeon layout
    virtual void draw(Surface& target) const override;

    unsigned int height() const { return grid.size(); }
    unsigned int width() const { return grid[0].size(); }
    int numRooms() const { return roomCount; }

    Tile tileAt(int y, int x) const { return grid[y][x]; }

    // Returns true iff two positions are in the same room
    bool inSameRoom(int y1, int x1, int y2, int x2) const;
    // Gets a 'random' placement: equal chance of being in any room, 
    // with any position in each room having equal chance
    std::pair<int,int> randomPlacement() const;
};

#endif
