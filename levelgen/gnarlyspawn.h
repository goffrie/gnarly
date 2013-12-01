#ifndef __GNARLYSPAWN_H__
#define __GNARLYSPAWN_H__

#include "spawn.h"

// The spawn for gnarly mode. Includes many more monsters
class GnarlySpawn : public Spawn {
    // The level we are currently on
    int level;
    // Whether or not to make spawn truly random (instead of weighting monster selection
    // based on level, just choose a random monster)
    bool reallyRandom;
    // Get a monster from an index
    virtual Monster* getMonster(int i);
public:
    GnarlySpawn(int l, bool r = false);
    // See spawn for descriptions
    virtual Monster* randomMonster() override;
    virtual Potion* randomPotion() override;
    virtual Gold* randomGold() override;
};

#endif
