#ifndef __BASICSPAWN_H__
#define __BASICSPAWN_H__

#include "spawn.h"

// Spawning for the basic version of the game, with probabilities and monsters
// described in the requirement
class BasicSpawn : public Spawn {
public:
    // See spawn for descriptions
    virtual Monster* randomMonster() override;
    virtual Potion* randomPotion() override;
    virtual Gold* randomGold() override;
    virtual LevelObject* getFromTile(char t) override;
};

#endif
