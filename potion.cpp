#include "potion.h"

#include "levelobjectvisitor.h"
#include "player.h"

void Potion::use(Player* target) {
    switch (type) {
        case RH: target->restoreHp(10); break;
        case PH: target->restoreHp(-10); break;
        case BA: target->applyBuff(10, 0); break;
        case WA: target->applyBuff(-10, 0); break;
        case BD: target->applyBuff(0, 10); break;
        case WD: target->applyBuff(0, -10); break;
    }
}

void Potion::accept(LevelObjectVisitor& v) {
    v.visit(*this);
}
