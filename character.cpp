#include "character.h"

#include "ui.h"
#include "levelobjectvisitor.h"

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
        UI::instance()->say("I (" + race() + ") died.");
        delete this;
    }
}

void Character::addHp(int amt) {
    hp += amt;
    if (hp > startingHP()) {
        hp = startingHP();
    }
}

void Character::takeDamage(int attack) {
    // damage = ceil( attack * 100 / (100 + defense) )
    const int ratio = 100 + def();
    reduceHp((attack * 100 + ratio - 1) / ratio);
}

void Character::attack(Character* other) {
    other->takeDamage(atk());
}

void Character::accept(LevelObjectVisitor& v) {
    v.visit(*this);
}
