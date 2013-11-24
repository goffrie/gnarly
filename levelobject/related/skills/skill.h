#ifndef __SKILL_H__
#define __SKILL_H__

#include <string>

class Player;

enum SkillHotkeys {
    FirstSkill = '!',
    SecondSkill = '@',
    ThirdSkill = '#',
    FourthSkill = '$'
};

class Skill {
public:
    Skill() { }
    virtual ~Skill () { }
    virtual void use(Player* p) = 0;
    virtual void notifyAttack(Player* p) { }
    virtual void notifyMove(Player* p) { }
    virtual void notifyUse(Player* p) { }
    virtual void step(Player* p) { };
    virtual std::string name() const = 0;
    virtual std::string description() const = 0;
    virtual std::string display() const { return ""; }
    static int getSkillNumber(char h);
    static SkillHotkeys getHotkey(int i);
};

#endif
