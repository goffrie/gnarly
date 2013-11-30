#include "dragon.h"
#include "attributes.h"
#include "dragongold.h"
#include "level.h"
#include "rand.h"

#include <algorithm>

using namespace std;

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

Character* Dragon::chooseTarget(vector<LevelObject*> objs) {
    // Only looks at enemies adjacent to my gold
    vector<LevelObject*> goldAdjacent = getLevel()->neighbours(hoard->getY(), hoard->getX());
    vector<Character*> targets;
    for (unsigned i = 0; i < objs.size(); i++) {
        if (objs[i]->isEnemy(team) && find(goldAdjacent.begin(), goldAdjacent.end(), objs[i]) != goldAdjacent.end()) {
            targets.push_back(static_cast<Character*>(objs[i]));
        }
    }

    if (!targets.empty()) {
        return targets[rnd(0, targets.size())];
    } else {
        return 0;
    }
}
