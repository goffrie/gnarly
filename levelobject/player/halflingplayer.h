#ifndef __HALFLINGPLAYER_H__
#define __HALFLINGPLAYER_H__

#include "player.h"

class HalflingPlayer : public Player {
public:
    HalflingPlayer();
    virtual int takeDamage(int attack) override;
};

#endif
