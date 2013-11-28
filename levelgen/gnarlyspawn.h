#ifndef __GNARLYSPAWN_H__
#define __GNARLYSPAWN_H__

#include "spawn.h"

class GnarlySpawn : public Spawn {
    enum { numMonsters = 20 };
    int level;
    virtual Monster* getMonster(int i);
public:
    GnarlySpawn(int l);
    virtual Monster* randomMonster() override;
    virtual PotionAdapter* randomPotion() override;
    virtual Gold* randomGold() override;
};

#endif
