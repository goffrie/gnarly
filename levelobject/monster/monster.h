#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "character.h"

class Monster : public Character {
public:
    Monster(Attributes::Race c);

    virtual ~Monster() { }

    virtual void attack(Character* target) override;

    virtual void accept(LevelObjectVisitor& v) override;
    virtual void step();
    virtual void moveToward(Character* c);
    virtual void wander();
    virtual int droppedGold() const { return 1; }
};

#endif
