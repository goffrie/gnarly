#include "staircase.h"
#include "levelobjectvisitor.h"

void Staircase::accept(LevelObjectVisitor& v) {
    v.visit(*this);
}
