#ifndef __PLAYERSELECT_H__
#define __PLAYERSELECT_H__

#include "displayable.h"

class Class;
class Player;
class UI;

// Represents and displays a title screen. The titlescreen is also where you select your character
class PlayerSelect : public Displayable {
    // All possible races
    enum Race {
        Human = 'h',
        Elf = 'e',
        Dwarf = 'd',
        Orc = 'o',
        Halfling = 'a',
        SuperElf = 'E'
    };
    // All possible classes
    enum PlayerClass {
        None = 'n',
        ThiefClass = 't',
        PaladinClass = 'p',
        WizardClass = 'w'
    };
    // The currently selected race/class
    Class* playerClass;
    Player* player;
    // Returns a player for the basic version
    Player* getBasicPlayer();
    // Switches the currently selected race
    void swapPlayer(Player* p);
    // Switches the currently selected class
    void swapClass(Class* c);
    PlayerSelect();
    // Notably, PlayerSelect does not have a destructor because it should not usually destroy the player it makes

public:
    // Gets a starting player. Also, displays title screen while user chooses it
    static Player* getPlayer(UI& ui);
    virtual void draw(Surface& target) const;
};

#endif
