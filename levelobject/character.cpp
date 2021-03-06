#include "character.h"

#include "levelobjectvisitor.h"
#include "level.h"
#include "surface.h"
#include "rand.h"

#include <cctype>
#include <ncurses.h>

using namespace std;

Character::Character(Attributes::Race c, Team::Name t)
 : attributes(new Attributes(Attributes::get(c))),
   hp(attributes->startingHP()),
   mp(attributes->startingMP()),
   team(Team::instance(t)) {
}

Character::~Character() {
    delete attributes;
}

void Character::draw(Surface& target) const {
    // The color of the character depends on how much HP they have relative to their total
    // Green = a lot of hp, Yellow = medium, Red = low
    int color;
    if (hp * 100 / startingHP() >= 67) {
        color = COLOR_GREEN;
    } else if (hp * 100 / startingHP() >= 33) {
        color = COLOR_YELLOW;
    } else {
        color = COLOR_RED;
    }
    target.setColor(color, COLOR_BLACK);
    LevelObject::draw(target);
    target.unsetColor(color, COLOR_BLACK);
}

void Character::reduceHP(int amt) {
    hp -= amt;
    if (hp <= 0) {
        // HP cannot go below 0
        hp = 0;
        getLevel()->notifyDeath(this);
    }
}

void Character::addHP(int amt) {
    hp += amt;
    if (hp > startingHP()) {
        hp = startingHP();
    }
}

void Character::reduceMP(int amt) {
    mp -= amt;
}

bool Character::dead() const {
    return hp <= 0;
}

Damage Character::computeDamage(int attack) {
    const int ratio = 100 + def();
    // damage = ceil( attack * 100 / (100 + defense) )
    const int damage = (attack * 100 + ratio - 1) / ratio;
    return createDamage(damage);
}

void Character::attack(Character* other) {
    other->computeDamage(atk()).apply();
}

int Character::atk() const {
    int _atk = attributes->atk();
    return _atk < 0 ? 0 : _atk;
}

int Character::def() const {
    int _def = attributes->def();
    return _def < 0 ? 0 : _def;
}

bool Character::isEnemy(Team* t) const {
    return !team->isAllied(t);
}

Character* Character::chooseTarget(vector<LevelObject*> objs) {
    // Gets all enemy targets
    vector<Character*> targets;
    for (unsigned i = 0; i < objs.size(); i++) {
        if (objs[i]->isEnemy(team)) {
            targets.push_back(static_cast<Character*>(objs[i]));
        }
    }

    // Return a random one
    if (!targets.empty()) {
        int i = rnd(0, targets.size());
        return targets[i];
    } else {
        return 0;
    }
}

void Character::accept(LevelObjectVisitor& v) {
    v.visit(*this);
}
