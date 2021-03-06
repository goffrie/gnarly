#include "dungeon.h"
#include "surface.h"
#include "rand.h"

#include <ncurses.h>

using namespace std;

char tileChar(Tile t) {
    switch (t) {
        case Floor: return '.';
        case WallV: return '|';
        case WallH: return '-';
        case Door: return '+';
        case Passage: return '#';
        case Rock: return ' ';
        case Tree: return '#';
    }
    return ' ';
}

Tile tileFromChar(char c) {
    switch (c) {
        case '.': return Floor;
        case '|': return WallV;
        case '-': return WallH;
        case '+': return Door;
        case '#': return Passage;
        case ' ': return Rock;
        case '%': return Tree;
        default: return Floor;
    }
}

inline int color(Tile t) {
    switch (t) {
        case Tree: return COLOR_GREEN;
        default: return COLOR_WHITE;
    }
}

Dungeon::Dungeon(vector<vector<Tile> >& m) : grid(m) {
    loadRooms();
}
Dungeon::Dungeon(vector<vector<bool> >& m) {
    grid.resize(m.size());
    const int height = m.size(),
              width = m[0].size();
    // Generates the grid from a bool of passable/not passable
    for (unsigned int y = 0; y < m.size(); ++y) {
        grid[y].resize(m[y].size());
        for (unsigned int x = 0; x < m[y].size(); ++x) {
            if (m[y][x]) {
                // Passable
                grid[y][x] = Floor;
                continue;
            }
            // Not passable. Check for surroundings to determine what to use
            const bool left = x > 0, right = (signed)x + 1 < width, top = y > 0, bottom = (signed)y + 1 < height;
            if ((left && m[y][x-1]) || (right && m[y][x+1])) grid[y][x] = WallV;
            else if ((top && m[y-1][x]) || (bottom && m[y+1][x])) grid[y][x] = WallH;
            else if ((top && left && m[y-1][x-1])
                  || (top && right && m[y-1][x+1])
                  || (bottom && left && m[y+1][x-1])
                  || (bottom && right && m[y+1][x+1])) grid[y][x] = WallV;
            else grid[y][x] = Rock;
        }
    }
    loadRooms();
}
Dungeon::Dungeon(const char* str) {
    bool newLine = true;
    for (; *str; ++str) {
        if (*str == '\n') {
            newLine = true;
            continue;
        }
        if (newLine) {
            grid.push_back(std::vector<Tile>());
            newLine = false;
        }
        // Place exactly what was specified
        grid.back().push_back(tileFromChar(*str));
    }
    loadRooms();
}


void drawTile(Tile t, Surface& target, unsigned y, unsigned x) {
    // Color the drawing if necessary
    target.setColor(color(t), COLOR_BLACK);
    target.draw(y, x, tileChar(t));
    target.unsetColor(color(t), COLOR_BLACK);
}

void Dungeon::draw(Surface& target) const {
    for (unsigned y = 0; y < grid.size(); ++y) {
        for (unsigned x = 0; x < grid[y].size(); ++x) {
            drawTile(grid[y][x], target, y, x);
        }
    }
}

bool Dungeon::inSameRoom(int y1, int x1, int y2, int x2) const {
    return rooms[y1][x1] == rooms[y2][x2];
}

pair<int,int> Dungeon::randomPlacement() const {
    // Pick a room.
    int roomNum = rnd(0, roomCount);
    // Pick a spot in the room.
    while (true) {
        int y = rnd(0, grid.size());
        int x = rnd(0, grid[y].size());
        if (rooms[y][x] == roomNum) {
            return make_pair(y, x);
        }
    }
}

void Dungeon::loadRooms() {
    // Identifies rooms in the dungeon by performing a flood fill.
    roomCount = 0;
    rooms.clear();
    for (unsigned int y = 0; y < grid.size(); y++) {
        rooms.push_back(vector<int>(grid[y].size(), -1));
    }

    for (unsigned int y = 0; y < grid.size(); y++) {
        for (unsigned int x = 0; x < grid[y].size(); x++) {
            if (grid[y][x] == Floor && rooms[y][x] == -1) {
                floodfill(y, x, roomCount);
                roomCount++;
            }
        }
    }
}

void Dungeon::floodfill(unsigned int y, unsigned int x, int n) {
    if (y >= grid.size() || x >= grid[y].size() || rooms[y][x] != -1 || grid[y][x] != Floor) {
        return;
    }
    rooms[y][x] = n;
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            floodfill(y + dy, x + dx, n);
        }
    }
}
