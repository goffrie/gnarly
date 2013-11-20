#ifndef __ELF_PLAYER_H__
#define __ELF_PLAYER_H__

#include "player.h"

class ElfPlayer : public Player {
public:
    ElfPlayer();
    virtual void applyBuff(int atk, int def) override;
};

#endif
