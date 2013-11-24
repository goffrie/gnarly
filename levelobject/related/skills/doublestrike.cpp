#include "doublestrike.h"
#include "game.h"
#include "ui.h"
#include "player.h"

bool DoubleStrike::use(Player* p) {
    Character* target = dynamic_cast<Character*>(Game::instance()->getTarget(1));
    if (!target) {
        UI::instance()->say("Invalid target for " + name() + ".");
        return false;
    }
    UI::instance()->say("You used " + name() + ".");
    p->attack(target);
    p->attack(target);
    return true;
}

std::string DoubleStrike::name() const{
    return "Double Strike";
}

std::string DoubleStrike::description() const {
    return "Attack twice";
}
