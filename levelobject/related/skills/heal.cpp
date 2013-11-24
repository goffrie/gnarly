#include "heal.h"
#include "player.h"
#include "ui.h"

bool Heal::use(Player* p) {
    p->heal(50);
    Skill::use(p);
    return true;
}

std::string Heal::name() const{
    return "Heal";
}

std::string Heal::description() const {
    return "Gain 50 hp";
}
