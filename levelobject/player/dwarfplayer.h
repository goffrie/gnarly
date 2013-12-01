#ifndef __DWARF_PLAYER_H__
#define __DWARF_PLAYER_H__

#include "player.h"

// A class representing a dwarf player
class DwarfPlayer : public Player {
public:
    // Created using dwarf stats
    DwarfPlayer();
    // Dwarves get double gold
    virtual void addGold(int amt);
};

#endif
