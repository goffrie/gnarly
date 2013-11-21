#ifndef __SUPERELFPLAYER_H__
#define __SUPERELFPLAYER_H__

#include "elfplayer.h"

// XXX Remove this class
class SuperElfPlayer : public ElfPlayer {
public:
    SuperElfPlayer() : ElfPlayer() { }
    virtual void reduceHP(int amount) override { }
};

#endif
