#ifndef __DIRECTION_H__
#define __DIRECTION_H__

#include <string>

class Direction {
    enum Orientation {
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
    Orientation orientation;
    int _dy, _dx;

    static int directionDy(Orientation o);
    static int directionDx(Orientation o);
    Direction(Orientation o);

public:
    int dy() const { return _dy; }
    int dx() const { return _dx; }
    std::string name() const;
    bool valid() const { return orientation != INVALID_DIRECTION; }
    static Direction basicGet(std::string s);
    static Direction get(int c);
};

#endif