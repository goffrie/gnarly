#include "staircase.h"
#include "game.h"
#include "levelobjectvisitor.h"

void Staircase::descend() {
    Game::instance()->makeNewLevel();
}

void Staircase::accept(LevelObjectVisitor& v) {
    v.visit(*this);
}
