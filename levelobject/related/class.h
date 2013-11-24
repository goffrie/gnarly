#ifndef __CLASS_H__
#define __CLASS_H__

#include <vector>
#include "skill.h"
#include "displayable.h"

class Player;

class Class : public Displayable {
protected:
    std::vector<Skill*> skills;

public:
    Class() { }
    virtual ~Class();
    virtual bool useSkill(unsigned int i, Player* p);
    virtual void notifyAttack(Player* p);
    virtual void notifyMove(Player* p);
    virtual void step(Player* p);
    virtual std::vector<Skill*> getSkills();
    virtual std::string name() { return ""; };
    virtual void draw(Surface& target) const override;
};

#endif
