#include "thief.h"
#include "stealth.h"
#include "doublestrike.h"

Thief::Thief() : Class() {
    skills.push_back(new Stealth());
    skills.push_back(new DoubleStrike());
}
