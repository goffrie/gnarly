#ifndef __ORC_PLAYER_H__
#define __ORC_PLAYER_H__

#include "player.h"

class OrcPlayer : public Player {
    int goldRemainder;
public:
    OrcPlayer();
    virtual void addGold(int amt);
};

#endif
