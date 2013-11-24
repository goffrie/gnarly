#include "fireball.h"
#include "ui.h"
#include "player.h"
#include "game.h"

#include <sstream>

bool Fireball::use(Player* p) {
    Character* target = dynamic_cast<Character*>(Game::instance()->getTarget(range));
    if (!target) {
        UI::instance()->say("Invalid target for " + name() + ".");
        return false;
    }
    Skill::use(p);
    p->damage(target, damage);
    return true;
}

std::string Fireball::name() const{
    return "Fireball";
}

std::string Fireball::description() const {
    std::ostringstream line;
    line << "Deals " << damage << " damage, with range " << range; 
    return line.str();
}
