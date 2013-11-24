#include "wizard.h"
#include "mindcontrol.h"
#include "fireball.h"

Wizard::Wizard() : Class() {
    skills.push_back(new Fireball());
    skills.push_back(new MindControl());
}
