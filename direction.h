#ifndef __DIRECTION_H__
#define __DIRECTION_H__

#include <string>

// Represents a direction
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

    // Returns the y and x distance travelled by an orientation
    static int directionDy(Orientation o);
    static int directionDx(Orientation o);
    Direction(Orientation o);

public:
    // Accessor methods
    int dy() const { return _dy; }
    int dx() const { return _dx; }
    std::string name() const;
    bool valid() const { return orientation != INVALID_DIRECTION; }
    // Returns a direction from either basic input or curses input
    static Direction basicGet(std::string s);
    static Direction get(int c);
};

#endif