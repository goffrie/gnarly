#include "paladin.h"
#include "divinemight.h"
#include "heal.h"

Paladin::Paladin() : Class() {
    skills.push_back(new DivineMight());
    skills.push_back(new Heal());
}
