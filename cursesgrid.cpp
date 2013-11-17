#include "cursesgrid.h"

#include <ncurses.h>

void CursesGrid::draw(int y, int x, char c) {
    mvaddch(y, x, c);
}

