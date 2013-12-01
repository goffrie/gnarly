#include "triplestrike.h"
#include "game.h"
#include "player.h"

bool TripleStrike::use(Player* p) {
    // Get a target for the spell
    Character* target = dynamic_cast<Character*>(Game::instance()->getTarget(range));
    if (!target) {
        return false;
    }
    Skill::use(p);
    p->attack(target);
    p->attack(target);
    p->attack(target);
    return true;
}

std::string TripleStrike::name() const{
    return "Triple Strike";
}

std::string TripleStrike::description() const {
    return "Attack three times";
}
