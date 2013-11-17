#include "levelitem.h"

#include "ui.h"
#include "level.h"

void LevelItem::draw(UI& ui) const {
    ui.draw(y, x, tile());
}

void LevelItem::moveTo(int nY, int nX) {
    if (level) {
        // Let the Level handle the movement.
        level->move(this, nY, nX);
    } else {
        // Not associated; just set y, x.
        y = nY;
        x = nX;
    }
}
