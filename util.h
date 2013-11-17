#ifndef __UTIL_H__
#define __UTIL_H__

enum Direction {
    NORTH = 0,
    SOUTH,
    EAST,
    WEST,
    NE,
    NW,
    SE,
    SW,
    INVALID_DIRECTION
};

inline int directionDy(Direction d) {
    static int r[8] = { -1, 1, 0, 0, -1, -1, 1, 1 };
    return r[d];
}

inline int directionDx(Direction d) {
    static int r[8] = { 0, 0, 1, -1, 1, -1, 1, -1 };
    return r[d];
}

#endif
