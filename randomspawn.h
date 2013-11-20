#ifndef __RANDOMSPAWN_H__
#define __RANDOMSPAWN_H__

#include "attributes.h"
#include "monster.h"
#include "potion.h"
#include "gold.h"

inline Monster* randomMonster() {
    switch(rand() % 18) {
        case 1 ... 4:
            return new Monster(Attributes::Werewolf);
        case 5 ... 7:
            return new Monster(Attributes::Vampire);
        case 8 ... 12:
            return new Monster(Attributes::Goblin);
        case 13 ... 14:
            return new Monster(Attributes::Troll);
        case 15 ... 16:
            return new Monster(Attributes::Phoenix);
        default:
            return new Monster(Attributes::Merchant);
    }
}

inline Potion* randomPotion() {
    return new Potion(static_cast<Potion::Type>(rand() % Potion::numTypes));
}

inline Gold* randomGold() {
    switch(rand() % 8) {
        case 0 ... 4:
            return new Gold(Gold::Normal);
        case 5 ... 6:
            return new Gold(Gold::Small);
        default:
            return new Gold(Gold::Dragon);
    }
}

#endif
