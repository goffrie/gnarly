#ifndef __CURSES_GRID_H__
#define __CURSES_GRID_H__

#include "grid.h"

class CursesGrid : public Grid {
    void draw(int y, int x, char c);
};

#endif
