#include "direction.h"
#include <ncurses.h>

using namespace std;

Direction::Direction(Orientation o) : orientation(o), _dy(directionDy(o)), _dx(directionDx(o)) {
}

string Direction::name() const {
    switch (orientation) {
        case NORTH: return "north";
        case SOUTH: return "south";
        case EAST: return "east";
        case WEST: return "west";
        case NE: return "northeast";
        case NW: return "northwest";
        case SE: return "southeast";
        case SW: return "southwest";
        default: std::terminate();
    }
}

int Direction::directionDy(Orientation o) {
    static int r[8] = { -1, 1, 0, 0, -1, -1, 1, 1 };
    return r[o];
}

int Direction::directionDx(Orientation o) {
    static int r[8] = { 0, 0, 1, -1, 1, -1, 1, -1 };
    return r[o];
}

Direction Direction::basicGet(std::string s) {
    if (s == "no") {
        return Direction(NORTH);
    } else if (s == "so") {
        return Direction(SOUTH);
    } else if (s == "ea") {
        return Direction(EAST);
    } else if (s == "we") {
        return Direction(WEST);
    } else if (s == "ne") {
        return Direction(NE);
    } else if (s == "nw") {
        return Direction(NW);
    } else if (s == "se") {
        return Direction(SE);
    } else if (s == "sw") {
        return Direction(SW);
    }
    return Direction(INVALID_DIRECTION);
}

Direction Direction::get(int c) {
    switch (c) {
        case 'h': case KEY_LEFT: case '4': return Direction(WEST);
        case 'j': case KEY_DOWN: case '2': return Direction(SOUTH);
        case 'k': case KEY_UP: case '8': return Direction(NORTH);
        case 'l': case KEY_RIGHT: case '6': return Direction(EAST);
        case 'y': case KEY_A1: case '7': return Direction(NW);
        case 'u': case KEY_A3: case '9': return Direction(NE);
        case 'b': case KEY_C1: case '1': return Direction(SW);
        case 'n': case KEY_C3: case '3': return Direction(SE);
    }

    return Direction(INVALID_DIRECTION);
}
