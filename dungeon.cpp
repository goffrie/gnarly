#include "dungeon.h"

#include <cstdlib>
#include <iostream>
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
    return r;
}
