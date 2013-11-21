#include "dragon.h"
#include "attributes.h"
#include "dragongold.h"

Dragon::Dragon(DragonGold* h) : Monster(Attributes::Dragon), hoard(h) {
}

void Dragon::wander() {
}

void Dragon::reduceHP(int amt) {
    Monster::reduceHP(amt);
    if (dead()) {
        hoard->notifyDragonDied();
    }
}
