#include "basicbuff.h"

BasicBuff::BasicBuff(AttributeProvider* base, int atk, int def)
: AttributeDecorator(base), atkDelta(atk), defDelta(def) {
}

int BasicBuff::atk() const {
    return base->atk() + atkDelta;
}

int BasicBuff::def() const {
    return base->def() + defDelta;
}
