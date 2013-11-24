#include "skill.h"

int Skill::getSkillNumber(char h) {
    switch (h) {
        case FirstSkill:
            return 0;
        case SecondSkill:
            return 1;
        case ThirdSkill:
            return 2;
        case FourthSkill:
            return 3;
        default:
            std::terminate();
    }
}

SkillHotkeys Skill::getHotkey(int i) {
    switch (i) {
        case 0:
            return FirstSkill;
        case 1:
            return SecondSkill;
        case 2:
            return ThirdSkill;
        case 3:
            return FourthSkill;
        default:
            std::terminate();
    }
}
