#include "damage.h"
#include "character.h"

void Damage::apply() {
    target.reduceHP(amt);
}
