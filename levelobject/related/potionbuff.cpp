#include "potionbuff.h"

PotionBuff::PotionBuff(AttributeProvider* base, int atk, int def)
: AttributeDecorator(base), atkDelta(atk), defDelta(def) {
}

int PotionBuff::atk() const {
    return base->atk() + atkDelta;
}

int PotionBuff::def() const {
    return base->def() + defDelta;
}
