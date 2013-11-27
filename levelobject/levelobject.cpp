#include "levelobject.h"

#include "surface.h"
#include "level.h"
#include "levelobjectvisitor.h"
#include "util.h"
#include <cassert>
#include <utility>

using namespace std;

LevelObject::~LevelObject() {
    if (level) {
        level->remove(this);
    }
}

void LevelObject::draw(Surface& target) const {
    target.draw(y, x, tile());
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
    return moveTo(y + d.dy(), x + d.dx());
}

bool LevelObject::canMove(int nY, int nX) {
    return level->valid(nY, nX) && level->free(nY, nX);
}

void LevelObject::step() {
    
}

bool LevelObject::isEnemy(Team* t) const {
    return false;
}

void LevelObject::accept(LevelObjectVisitor& v) {
    v.visit(*this);
}

vector<pair<int, int> > LevelObject::getFreeAdjacent() {
    // Look for a free location.
    vector<pair<int, int> > locations;
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dy == 0 && dx == 0) continue;
            const int ny = getY() + dy,
                      nx = getX() + dx;
            if (level->free(ny, nx)) {
                locations.push_back(make_pair(ny, nx));
            }
        }
    }
    return locations;
}

void LevelObject::setPos(int y, int x) {
    assert(!level);
    this->y = y;
    this->x = x;
}
