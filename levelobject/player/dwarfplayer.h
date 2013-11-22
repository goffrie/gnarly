#ifndef __DWARF_PLAYER_H__
#define __DWARF_PLAYER_H__

#include "player.h"

class DwarfPlayer : public Player {
public:
    DwarfPlayer();
    virtual void addGold(int amt);
};

#endif
