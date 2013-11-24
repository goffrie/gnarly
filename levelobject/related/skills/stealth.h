#ifndef __STEALTH_H__
#define __STEALTH_H__

#include "team.h"
#include "skill.h"

class Stealth : public Skill {
    static std::vector<Team::Status> allAlly;
    std::vector<Team::Status> storedAlliances;
    enum { duration = 8 };
    int currentDuration;

    void removeStealth(Player* p);

public:
    Stealth();
    virtual void use(Player* p) override;
    virtual void notifyAttack(Player* p) override;
    virtual void step(Player* p) override;
    virtual std::string name() const override;
    virtual std::string description() const override;
    virtual std::string display() const override;
};

#endif
