#ifndef __RANDOMSPAWN_H__
#define __RANDOMSPAWN_H__

#include "attributes.h"
#include "monster.h"
#include <cstdlib>

inline Monster* randomMonster() {
    switch(rand() % 18) {
        case 1 ... 4:
            return new Monster(Werewolf);
        case 5 ... 7:
            return new Monster(Vampire);
        case 8 ... 12:
            return new Monster(Goblin);
        case 13 ... 14:
            return new Monster(Troll);
        case 15 ... 16:
            return new Monster(Phoenix);
        default:
            return new Monster(Merchant);
    }
}

#endif