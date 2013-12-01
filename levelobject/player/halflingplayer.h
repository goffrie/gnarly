#ifndef __HALFLINGPLAYER_H__
#define __HALFLINGPLAYER_H__

#include "player.h"

// A class representing a halfling player
class HalflingPlayer : public Player {
public:
    // Created using halfling stats
    HalflingPlayer();
    // Halflings occasionally evade attacks
    virtual int takeDamage(int attack) override;
};

#endif
