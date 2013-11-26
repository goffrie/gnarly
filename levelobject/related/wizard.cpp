#include "wizard.h"
#include "mindcontrol.h"
#include "fireball.h"
#include "classbuff.h"

Wizard::Wizard() : Class() {
    skills.push_back(new Fireball());
    skills.push_back(new MindControl());
}

AttributeProvider* Wizard::getClassBuff(AttributeProvider* a) const {
    return new ClassBuff(a, -5, -5, -20, 60);
}

AttributeProvider* Wizard::getLevelBuff(AttributeProvider* a) const {
    return new ClassBuff(a, 10, 5, 10, 40);
}
