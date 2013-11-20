#include "levelobject.h"

#include "ui.h"
#include "level.h"
#include "levelobjectvisitor.h"

LevelObject::~LevelObject() {
    if (level) {
        level->remove(this);
    }
}

void LevelObject::draw(UI& ui) const {
    ui.draw(y, x, tile());
}

bool LevelObject::moveTo(int nY, int nX) {
    if (canMove(nY, nX)) {
        // Let the Level handle the movement.
        level->move(this, nY, nX);
        return true;
    }
    // TODO: throw an exception instead?
    return false;
}

bool LevelObject::moveRelative(Direction d) {
    return moveTo(y + directionDy(d), x + directionDx(d));
}

bool LevelObject::canMove(int nY, int nX) {
    return level->valid(nY, nX) && level->free(nY, nX);
}

void LevelObject::step() {
    
}

void LevelObject::accept(LevelObjectVisitor& v) {
    v.visit(*this);
}
