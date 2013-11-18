#include "character.h"

#include <iostream>

using namespace std;

Character::Character(CharAttr c) : LevelObject(0, 0), attributes(new Attributes(Attributes::get(c))), hp(attributes->startingHP()) {
}

Character::~Character() {
    delete attributes;
}

void Character::reduceHp(int amt) {
    hp -= amt;
    // TODO: notify
    if (hp <= 0) {
        cerr << "I died." << endl;
    }
}

void Character::takeDamage(int attack) {
    // damage = ceil( attack * 100 / (100 + defense) )
    const int ratio = 100 + def();
    reduceHp((attack * 100 + ratio - 1) / ratio);
}
