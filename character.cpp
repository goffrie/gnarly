#include "character.h"

#include "ui.h"
#include "levelobjectvisitor.h"

#include <cstdlib>

using namespace std;

Character::Character(CharAttr c, TeamName t) : 
  LevelObject(0, 0), 
  attributes(new Attributes(Attributes::get(c))), 
  hp(attributes->startingHP()),
  team(Team::instance(t)) {
}

Character::~Character() {
    delete attributes;
}

void Character::reduceHP(int amt) {
    hp -= amt;
    // TODO: notify
    if (hp <= 0) {
        UI::instance()->say("I (" + race() + ") died.");
        delete this;
    }
}

void Character::addHP(int amt) {
    hp += amt;
    if (hp > startingHP()) {
        hp = startingHP();
    }
}

void Character::takeDamage(int attack) {
    // damage = ceil( attack * 100 / (100 + defense) )
    const int ratio = 100 + def();
    reduceHP((attack * 100 + ratio - 1) / ratio);
}

void Character::attack(Character* other) {
    other->takeDamage(atk());
}

bool Character::isEnemy(Team* t) {
    return !team->isAllied(t);
}

Character* Character::chooseTarget(vector<LevelObject*> objs) {
    vector<Character*> targets;
    for (unsigned i = 0; i < objs.size(); i++) {
        if (objs[i]->isEnemy(team)) {
            targets.push_back(static_cast<Character*>(objs[i]));
        }
    }

    if (!targets.empty()) {
        int i = rand() % targets.size();
        return targets[i];
    } else {
        return 0;
    }
}

void Character::accept(LevelObjectVisitor& v) {
    v.visit(*this);
}
