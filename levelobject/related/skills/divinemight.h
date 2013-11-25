#ifndef __DIVINEMIGHT_H__
#define __DIVINEMIGHT_H__

#include "skill.h"

class DivineMight : public Skill {
public:
    DivineMight() : Skill(10) { }
    virtual bool use(Player* p) override;
    virtual std::string name() const override;
    virtual std::string description() const override;
};

#endif
