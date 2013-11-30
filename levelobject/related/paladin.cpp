#include "paladin.h"
#include "divinemight.h"
#include "heal.h"
#include "classbuff.h"

Paladin::Paladin() : Class() {
    skills.push_back(new DivineMight());
    skills.push_back(new Heal());
}

AttributeProvider* Paladin::getClassBuff(AttributeProvider* a) const {
    return new ClassBuff(a, -5, 20, 30);
}

AttributeProvider* Paladin::getLevelBuff(AttributeProvider* a) const {
    return new ClassBuff(a, 5, 20, 30, 10);
}
