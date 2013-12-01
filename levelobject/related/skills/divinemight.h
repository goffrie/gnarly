#ifndef __DIVINEMIGHT_H__
#define __DIVINEMIGHT_H__

#include "skill.h"

// A paladin skill that applies a buff to the player. The buff wears off when the level changes
class DivineMight : public Skill {
public:
    // Manacost: 10
    DivineMight() : Skill(10) { }
    // Applies a buff to the player
    virtual bool use(Player* p) override;
    virtual std::string name() const override;
    virtual std::string description() const override;
};

#endif
