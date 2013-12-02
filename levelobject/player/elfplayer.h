#ifndef __ELF_PLAYER_H__
#define __ELF_PLAYER_H__

#include "player.h"

// A class representing a elf player
class ElfPlayer : public Player {
public:
    // Created using elf stats
    ElfPlayer();
    // Elves only have positive heals and buffs
    virtual void heal(int amt);
    virtual void applyBuff(int atk, int def);
};

#endif
