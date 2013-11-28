#ifndef __BASICSPAWN_H__
#define __BASICSPAWN_H__

#include "spawn.h"

class BasicSpawn : public Spawn {
public:
    virtual Monster* randomMonster() override;
    virtual PotionAdapter* randomPotion() override;
    virtual Gold* randomGold() override;
    virtual LevelObject* getFromTile(char t) override;
};

#endif
