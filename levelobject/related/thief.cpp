#include "thief.h"
#include "stealth.h"
#include "doublestrike.h"
#include "classbuff.h"

Thief::Thief() : Class() {
    skills.push_back(new Stealth());
    skills.push_back(new DoubleStrike());
}

AttributeProvider* Thief::getClassBuff(AttributeProvider* a) const {
    return new ClassBuff(a, 20, -10, -20);
}
