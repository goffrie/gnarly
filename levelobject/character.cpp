#include "character.h"

#include "levelobjectvisitor.h"
#include "level.h"
#include "ui.h"

#include <cstdlib>
#include <cctype>
#include <ncurses.h>

using namespace std;

Character::Character(Attributes::Race c, TeamName t) : 
  LevelObject(0, 0), 
  attributes(new Attributes(Attributes::get(c))), 
  hp(attributes->startingHP()),
  team(Team::instance(t)) {
}

Character::~Character() {
    delete attributes;
}

void Character::draw(UI& ui) const {
    int color;
    if (hp * 100 / startingHP() >= 67) {
        color = COLOR_GREEN;
    } else if (hp * 100 / startingHP() >= 33) {
        color = COLOR_YELLOW;
    } else {
        color = COLOR_RED;
    }
    ui.setColor(color, COLOR_BLACK);
    LevelObject::draw(ui);
    ui.unsetColor(color, COLOR_BLACK);
}

void Character::reduceHP(int amt) {
    hp -= amt;
    if (hp <= 0) {
        getLevel()->notifyDeath(this);
    }
}

void Character::addHP(int amt) {
    hp += amt;
    if (hp > startingHP()) {
        hp = startingHP();
    }
}

bool Character::dead() const {
    return hp <= 0;
}

int Character::takeDamage(int attack) {
    // damage = ceil( attack * 100 / (100 + defense) )
    const int ratio = 100 + def();
    int damage = (attack * 100 + ratio - 1) / ratio;
    reduceHP(damage);
    return damage;
}

void Character::attack(Character* other) {
    other->takeDamage(atk());
}

bool Character::isEnemy(Team* t) const {
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
