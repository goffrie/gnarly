#include "merchant.h"
#include "attributes.h"
#include "level.h"
#include "gold.h"

Merchant::Merchant() : Monster(Attributes::Merchant) {
    team = Team::instance(Merchants);
}

void Merchant::reduceHP(int amt) {
    Monster::reduceHP(amt);
    if (dead()) {
        team->unally(Team::instance(Players));
        Gold* g = new Gold(Gold::Merchant);
        g->setPos(this->getY(), this->getX());
        getLevel()->add(g);
    }
}
