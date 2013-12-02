#ifndef __MINDCONTROL_H__
#define __MINDCONTROL_H__

#include "skill.h"

// A wizard skill that mind controls an enemy
class MindControl : public Skill {
    // The range of the skill
    enum { range = 5 };
public:
    // Manacost: 20
    MindControl() : Skill(20) { }
    // Uses Mind Control. It works by changing the team of the enemy to be on the same team as the player
    virtual bool use(Player* p);
    virtual std::string name() const;
    virtual std::string description() const;
};

#endif
