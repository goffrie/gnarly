#ifndef __DRAGON_H__
#define __DRAGON_H__

#include "monster.h"
#include <vector>

class DragonGold;

// A dragon monster
class Dragon : public Monster {
    // The hoard associated with a dragon
    DragonGold* hoard;

protected:
    // When a dragon dies, it notifies its hoard
    // to allow that hoard to be picked up
    virtual void reduceHP(int amt);

public:
    // Creates a dragon with its hoard
    Dragon(DragonGold* hoard);
    // Dragons do not wander to stay near their horde
    virtual void wander();
    // Dragons will only attack things next to their horde
    virtual Character* chooseTarget(std::vector<LevelObject*> objs);
};

#endif
