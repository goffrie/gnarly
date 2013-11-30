#include "thief.h"
#include "stealth.h"
#include "triplestrike.h"
#include "classbuff.h"

Thief::Thief() : Class() {
    skills.push_back(new Stealth());
    skills.push_back(new TripleStrike());
}

AttributeProvider* Thief::getClassBuff(AttributeProvider* a) const {
    return new ClassBuff(a, 20, -10, -20);
}

AttributeProvider* Thief::getLevelBuff(AttributeProvider* a) const {
    return new ClassBuff(a, 20, 5, 15, 15);
}
