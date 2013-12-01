#ifndef __SKILL_H__
#define __SKILL_H__

#include <string>

class Player;

// The hotkeys for skills
enum SkillHotkeys {
    FirstSkill = '!',
    SecondSkill = '@',
    ThirdSkill = '#',
    FourthSkill = '$'
};

// An abstract class representing a skill. Skills are associated with a class
class Skill {
protected:
    // The mana cost of the skill
    int _mpCost;

public:
    Skill(int mp = 0) : _mpCost(mp) { }
    virtual ~Skill () { }
    // A player uses this skill
    virtual bool use(Player* p);
    // Called by a class when the player attacks
    virtual void notifyAttack(Player* p) { }
    // Called by a class when the game steps
    virtual void step(Player* p) { };
    // The name of the skill
    virtual std::string name() const = 0;
    // THe description of the skill
    virtual std::string description() const = 0;
    // Anything that needs to be displayed with the skill
    virtual std::string display() const { return ""; }
    // Returns the skill's mana cost
    virtual int mpCost() { return _mpCost; }
    // Gets the index of a skill from the hotkey, or vice versa
    static int getSkillNumber(char h);
    static SkillHotkeys getHotkey(int i);
};

#endif
