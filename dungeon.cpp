#include "dungeon.h"

#include <cstdlib>
#include "ui.h"

using namespace std;

inline char tileChar(Tile t) {
    switch (t) {
        case Floor: return '.';
        case WallV: return '|';
        case WallH: return '-';
        case Door: return '+';
        case Passage: return '#';
        case Rock: return ' ';
    }
    return ' ';
}

inline Tile tileFromChar(char c) {
    switch (c) {
        case '.': return Floor;
        case '|': return WallV;
        case '-': return WallH;
        case '+': return Door;
        case '#': return Passage;
        case ' ': return Rock;
        default: std::terminate();
    }
}

Dungeon::Dungeon(vector<vector<Tile> >& m) : grid(m) {
    loadRooms();
}
Dungeon::Dungeon(vector<vector<bool> >& m) {
    grid.resize(m.size());
    for (int y = 0; y < m.size(); ++y) {
        grid[y].resize(m[y].size());
        for (int x = 0; x < m[y].size(); ++x) {
            grid[y][x] = m[y][x] ? Floor : Rock;
        }
    }
    loadRooms();
}

void Dungeon::draw(UI& dgrid) const {
    for (unsigned y = 0; y < grid.size(); ++y) {
        for (unsigned x = 0; x < grid[y].size(); ++x) {
            dgrid.draw(y, x, tileChar(grid[y][x]));
        }
    }
}

Dungeon Dungeon::defaultDungeon() {
    return Dungeon(
        "|-----------------------------------------------------------------------------|\n"
        "|                                                                             |\n"
        "| |--------------------------|        |-----------------------|               |\n"
        "| |..........................|        |.......................|               |\n"
        "| |..........................+########+.......................|-------|       |\n"
        "| |..........................|   #    |...............................|--|    |\n"
        "| |..........................|   #    |..................................|--| |\n"
        "| |----------+---------------|   #    |----+----------------|...............| |\n"
        "|            #                 #############                |...............| |\n"
        "|            #                 #     |-----+------|         |...............| |\n"
        "|            #                 #     |............|         |...............| |\n"
        "|            ###################     |............|   ######+...............| |\n"
        "|            #                 #     |............|   #     |...............| |\n"
        "|            #                 #     |-----+------|   #     |--------+------| |\n"
        "|  |---------+-----------|     #           #          #              #        |\n"
        "|  |.....................|     #           #          #         |----+------| |\n"
        "|  |.....................|     ########################         |...........| |\n"
        "|  |.....................|     #           #                    |...........| |\n"
        "|  |.....................|     #    |------+--------------------|...........| |\n"
        "|  |.....................|     #    |.......................................| |\n"
        "|  |.....................+##########+.......................................| |\n"
        "|  |.....................|          |.......................................| |\n"
        "|  |---------------------|          |---------------------------------------| |\n"
        "|                                                                             |\n"
        "|-----------------------------------------------------------------------------|\n"
    );
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
        grid.back().push_back(tileFromChar(*str));
    }
    loadRooms();
}

bool Dungeon::inSameRoom(int y1, int x1, int y2, int x2) {
    return rooms[y1][x1] == rooms[y2][x2];
}

pair<int,int> Dungeon::randomPlacement() {
    // Pick a room.
    int roomNum = rand() % roomCount;
    // Pick a spot in the room.
    // XXX: pick a spot that isn't empty. make sure that such a spot exists.
    while (true) {
        int y = rand() % grid.size();
        int x = rand() % grid[y].size();
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
    if (x < 0 || y < 0 || y >= grid.size() || x >= grid[y].size() || rooms[y][x] != -1 || grid[y][x] != Floor) {
        return;
    }
    rooms[y][x] = n;
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            floodfill(y + dy, x + dx, n);
        }
    }
}
