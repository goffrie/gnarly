#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "character.h"

class Monster : public Character {
public:
    Monster(CharAttr c) : Character(c) { }

    virtual ~Monster() { }

    virtual void attack(Character* target) override;

    virtual void accept(LevelObjectVisitor& v) override { v.visit(*this); }
    virtual void step();
};

#endif
