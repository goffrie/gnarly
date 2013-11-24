#include "thief.h"
#include "stealth.h"

Thief::Thief() : Class() {
    skills.push_back(new Stealth());
}
