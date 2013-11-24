#ifndef __DOUBLESTRIKE_H__
#define __DOUBLESTRIKE_H__

#include "skill.h"

class DoubleStrike : public Skill {
public:
    virtual bool use(Player* p) override;
    virtual std::string name() const override;
    virtual std::string description() const override;
};

#endif
