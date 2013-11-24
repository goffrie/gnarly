#include "divinemight.h"
#include "ui.h"
#include "player.h"

void DivineMight::use(Player* p) {
    p->applyBuff(20, 30);
    UI::instance()->say("You used " + name() + ".");
}

std::string DivineMight::name() const{
    return "Divine Might";
}

std::string DivineMight::description() const {
    return "Gain 20 atk and 30 def";
}
