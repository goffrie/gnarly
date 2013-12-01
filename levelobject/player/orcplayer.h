#ifndef __ORC_PLAYER_H__
#define __ORC_PLAYER_H__

#include "player.h"

// An orc player class
class OrcPlayer : public Player {
    // The amount of gold added to the orc mod 2
    int goldRemainder;
public:
    // Created using orc stats
    OrcPlayer();
    // Orcs get half gold, so we use gold remainder to avoid floats
    virtual void addGold(int amt);
};

#endif
