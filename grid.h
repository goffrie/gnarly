#ifndef __GRID_H__
#define __GRID_H__

// An abstract class representing a grid that can be drawn on.
class Grid {
public:
    virtual void draw(int y, int x, char c) = 0;
};

#endif
