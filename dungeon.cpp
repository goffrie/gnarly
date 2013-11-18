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

void Dungeon::draw(UI& dgrid) const {
    for (unsigned y = 0; y < grid.size(); ++y) {
        for (unsigned x = 0; x < grid[y].size(); ++x) {
            dgrid.draw(y, x, tileChar(grid[y][x]));
        }
    }
}

Dungeon Dungeon::defaultDungeon() {
    return loadDungeon(
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


Dungeon Dungeon::loadDungeon(const char* str) {
    Dungeon r;
    bool newLine = true;
    for (; *str; ++str) {
        if (*str == '\n') {
            newLine = true;
            continue;
        }
        if (newLine) {
            r.grid.push_back(std::vector<Tile>());
            newLine = false;
        }
        r.grid.back().push_back(tileFromChar(*str));
    }
    r.loadRooms();

    return r;
}

bool Dungeon::inSameRoom(int y1, int x1, int y2, int x2) {
    return rooms[y1][x1] == rooms[y2][x2];
}

pair<int,int> Dungeon::randomPlacement() {
    // Get room
    int roomNum = rand() % numberRooms;
    // Get position in room
    while (true) {
        int y = rand() % grid.size();
        int x = rand() % grid[y].size();
        if (rooms[y][x] == roomNum) {
            return pair<int,int>(y, x);
        }
    }
}

void Dungeon::loadRooms() {
    // Floodfills to identify rooms
    for (unsigned int y = 0; y < grid.size(); y++) {
        rooms.push_back(vector<int>(grid[y].size(), -1));
    }

    for (unsigned int y = 0; y < grid.size(); y++) {
        for (unsigned int x = 0; x < grid[y].size(); x++) {
            if (grid[y][x] == Floor && rooms[y][x] == -1) {
                floodfill(y, x, numberRooms);
                numberRooms++;
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