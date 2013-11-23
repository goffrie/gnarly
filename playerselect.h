#ifndef __PLAYERSELECT_H__
#define __PLAYERSELECT_H__

#include "displayable.h"

class Player;
class UI;

// Represents and displays a title screen. The titlescreen is also where you select your character
class PlayerSelect : public Displayable {
    enum Race {
        Human = 'h',
        Elf = 'e',
        Dwarf = 'd',
        Orc = 'o',
        SuperElf = 'E'
    };
    Player* player;
    Player* getBasicPlayer();

public:
    PlayerSelect();
    Player* getPlayer(UI& ui);
    virtual void draw(UI& ui) const;
};

#endif