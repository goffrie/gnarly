#ifndef __CLASS_H__
#define __CLASS_H__

#include <vector>
#include "skill.h"
#include "displayable.h"

class Player;
class AttributeProvider;

// A class that can be assigned to a player at player creation
// A class is essentially a collection of skills a player can use and buffs at creation and when levelling
class Class : public Displayable {
protected:
    // The skills that can be used
    std::vector<Skill*> skills;

public:
    Class() { }
    virtual ~Class();
    // A player uses a skill
    virtual bool useSkill(unsigned int i, Player* p);
    // Called when the player attacks, to let skills know the player attacked
    virtual void notifyAttack(Player* p);
    // Called when the game steps, to let skills know the player attacked
    virtual void step(Player* p);
    // Returns the skills
    virtual std::vector<Skill*> getSkills();
    virtual std::string name() { return ""; };
    // Modifiers used when creating or leveling class that are applied to the attributes of the player
    virtual AttributeProvider* getClassBuff(AttributeProvider* a) const;
    virtual AttributeProvider* getLevelBuff(AttributeProvider* a) const;
    // Draws the skills and their manacosts on the bottom of the screen.
    virtual void draw(Surface& target) const override;
};

#endif
