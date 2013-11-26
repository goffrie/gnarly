#include "divinemight.h"
#include "player.h"

bool DivineMight::use(Player* p) {
    p->applyBuff(10, 20);
    Skill::use(p);
    return true;
}

std::string DivineMight::name() const{
    return "Divine Might";
}

std::string DivineMight::description() const {
    return "Gain 10 atk and 20 def";
}
