#ifndef __TRIPLESTRIKE_H__
#define __TRIPLESTRIKE_H__

#include "skill.h"

// A Thief skill that attacks a target 3 times in a single round
class TripleStrike : public Skill {
    // The range of the skill
    enum { range = 1 };
public:
    // Manacost: 5
    TripleStrike() : Skill(5) { }
    virtual bool use(Player* p);
    virtual std::string name() const;
    virtual std::string description() const;
};

#endif
