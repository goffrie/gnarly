#include "mindcontrol.h"
#include "ui.h"
#include "player.h"
#include "game.h"

#include <sstream>

bool MindControl::use(Player* p) {
    Character* target = dynamic_cast<Character*>(Game::instance()->getTarget(range));
    if (!target) {
        return false;
    }
    Skill::use(p);
    target->setTeam(p->getTeam());
    return true;
}

std::string MindControl::name() const{
    return "Mind Control";
}

std::string MindControl::description() const {
    std::ostringstream line;
    line << "Mind controls an enemy with range " << range; 
    return line.str();
}
