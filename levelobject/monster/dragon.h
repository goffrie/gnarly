#ifndef __DRAGON_H__
#define __DRAGON_H__

#include "monster.h"
#include <vector>

class DragonGold;

class Dragon : public Monster {
    DragonGold* hoard;

protected:
    virtual void reduceHP(int amt) override;

public:
    Dragon(DragonGold* hoard);
    virtual void wander() override;
    virtual Character* chooseTarget(std::vector<LevelObject*> objs);
};

#endif
