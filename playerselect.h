#ifndef __PLAYERSELECT_H__
#define __PLAYERSELECT_H__

#include "displayable.h"

class Class;
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
    enum PlayerClass {
        None = 'n',
        ThiefClass = 't',
        PaladinClass = 'p'
    };
    Class* playerClass;
    Player* player;
    Player* getBasicPlayer();
    void swapPlayer(Player* p);
    void swapClass(Class* c);

public:
    PlayerSelect();
    Player* getPlayer(UI& ui);
    virtual void draw(Surface& target) const;
};

#endif
