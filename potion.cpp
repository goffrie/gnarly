#include "potion.h"

#include "levelobjectvisitor.h"
#include "player.h"
#include "ui.h"

void Potion::use(Player* target) {
    UI::instance()->say("You drink a potion of " + name(type) + ".");
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

std::string Potion::name(Type t) {
    switch (t) {
        case RH: return "restore health";
        case PH: return "poison health";
        case BA: return "boost attack";
        case WA: return "wound attack";
        case BD: return "boost defense";
        case WD: return "wound defense";
        default: std::terminate();
    }
}
