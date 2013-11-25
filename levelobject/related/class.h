#ifndef __CLASS_H__
#define __CLASS_H__

#include <vector>
#include "skill.h"
#include "displayable.h"

class Player;
class AttributeProvider;

class Class : public Displayable {
protected:
    std::vector<Skill*> skills;
    int _startingMP;

public:
    Class() { }
    virtual ~Class();
    virtual bool useSkill(unsigned int i, Player* p);
    virtual void notifyAttack(Player* p);
    virtual void notifyMove(Player* p);
    virtual void step(Player* p);
    virtual std::vector<Skill*> getSkills();
    virtual std::string name() { return ""; };
    // Modifiers used when creating class
    virtual AttributeProvider* getClassBuff(AttributeProvider* a) const;
    virtual void draw(Surface& target) const override;
};

#endif
