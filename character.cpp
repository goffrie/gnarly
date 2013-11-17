#include "character.h"

#include <iostream>

using namespace std;

Character::Character(int startingHp, int y, int x) : hp(startingHp), y(y), x(x) {
}

Character::~Character() {
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

void Character::draw(Grid& grid) {
    grid.draw(y, x, tile());
}
