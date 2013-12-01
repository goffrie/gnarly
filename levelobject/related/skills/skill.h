#ifndef __SKILL_H__
#define __SKILL_H__

#include <string>

class Player;

// The hotkeys for a skill
enum SkillHotkeys {
    FirstSkill = '!',
    SecondSkill = '@',
    ThirdSkill = '#',
    FourthSkill = '$'
};

class Skill {
protected:
    int _mpCost;

public:
    Skill(int mp = 0) : _mpCost(mp) { }
    virtual ~Skill () { }
    virtual bool use(Player* p);
    virtual void notifyAttack(Player* p) { }
    virtual void notifyMove(Player* p) { }
    virtual void notifyUse(Player* p) { }
    virtual void step(Player* p) { };
    virtual std::string name() const = 0;
    virtual std::string description() const = 0;
    virtual std::string display() const { return ""; }
    virtual int mpCost() { return _mpCost; }
    static int getSkillNumber(char h);
    static SkillHotkeys getHotkey(int i);
};

#endif
