#ifndef __TRIPLESTRIKE_H__
#define __TRIPLESTRIKE_H__

#include "skill.h"

class TripleStrike : public Skill {
    enum { range = 1 };
public:
    TripleStrike() : Skill(5) { }
    virtual bool use(Player* p) override;
    virtual std::string name() const override;
    virtual std::string description() const override;
};

#endif
