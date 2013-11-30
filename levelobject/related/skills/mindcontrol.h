#ifndef __MINDCONTROL_H__
#define __MINDCONTROL_H__

#include "skill.h"

class MindControl : public Skill {
    enum { range = 5 };
public:
    MindControl() : Skill(20) { }
    virtual bool use(Player* p) override;
    virtual std::string name() const override;
    virtual std::string description() const override;
};

#endif
