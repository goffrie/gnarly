#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "character.h"

// A generic class for a monster with no special abilities
class Monster : public Character {
public:
    // Creates a monster given a race
    Monster(Attributes::Race c);

    virtual ~Monster() { }

    // Attacks a target, missing half of the time
    virtual void attack(Character* target) override;

    virtual void accept(LevelObjectVisitor& v) override;
    // Either attacks an adjacent enemy, moves towards a visible enemy (if gnarly mode is enabled),
    // or wanders randomly
    virtual void step();
    // Move towards a character
    virtual void moveToward(Character* c);
    // Wanders to random adjacent spot
    virtual void wander();
};

#endif
