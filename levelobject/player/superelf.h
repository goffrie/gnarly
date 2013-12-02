#ifndef __SUPERELFPLAYER_H__
#define __SUPERELFPLAYER_H__

#include "elfplayer.h"

// A race used for testing purposes that does not take any damage, and recieves 10x exp
class SuperElfPlayer : public ElfPlayer {
public:
    SuperElfPlayer() : ElfPlayer() { }
    // Doesn't reduce HP
    virtual void reduceHP(int amount) { }
    // Gets 10x xp
    virtual void addXP(int xp) { ElfPlayer::addXP(xp * 10); }
};

#endif
