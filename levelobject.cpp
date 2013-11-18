#include "levelobject.h"

#include "ui.h"
#include "level.h"

void LevelObject::draw(UI& ui) const {
    ui.draw(y, x, tile());
}

void LevelObject::moveTo(int nY, int nX) {
    if (canMove(nY, nX)) {
        // Let the Level handle the movement.
        level->move(this, nY, nX);
    }
}

void LevelObject::moveRelative(Direction d) {
    moveTo(y + directionDy(d), x + directionDx(d));
}
 
bool LevelObject::canMove(int nY, int nX) {
    if (
           nX < 0 
        || nY < 0 
        || (unsigned)nX >= level->width() 
        || (unsigned)nY >= level->height() 
        || !level->free(nY, nX)
    ) {
        return false;
    }
    return true;
}