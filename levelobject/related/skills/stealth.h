#ifndef __STEALTH_H__
#define __STEALTH_H__

#include "team.h"
#include "skill.h"

// A thief skill that stops monsters from attacking the player for a set duration
class Stealth : public Skill {
    // The alliance status representing a team allied with everyone
    static std::vector<Team::Status> allAlly;
    // The previous alliances before stealth
    std::vector<Team::Status> storedAlliances;
    // How long it lasts
    enum { duration = 12 };
    int currentDuration;

    // Resets the alliance status of the team to before stealth was used
    void removeStealth(Player* p);

public:
    Stealth();
    // Uses stealth. Stealth works by storing the previous alliance status
    // of the player's team and changing it to being allied with everyone
    virtual bool use(Player* p) override;
    // When the player attacks, remove stealth
    virtual void notifyAttack(Player* p) override;
    // Decreases the currentDuration
    virtual void step(Player* p) override;
    virtual std::string name() const override;
    virtual std::string description() const override;
    virtual std::string display() const override;
};

#endif
