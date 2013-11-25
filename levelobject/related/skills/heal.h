#ifndef __HEAL_H__
#define __HEAL_H__

#include "skill.h"

class Heal : public Skill {
public:
    Heal() : Skill(10) { }
    virtual bool use(Player* p) override;
    virtual std::string name() const override;
    virtual std::string description() const override;
};

#endif
