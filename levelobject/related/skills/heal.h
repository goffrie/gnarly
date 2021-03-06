#ifndef __HEAL_H__
#define __HEAL_H__

#include "skill.h"

// A paladin skill that heals the paladin by a fixed amount
class Heal : public Skill {
public:
    // Manacost: 10
    Heal() : Skill(10) { }
    // Heals the player
    virtual bool use(Player* p) override;
    virtual std::string name() const override;
    virtual std::string description() const override;
};

#endif
