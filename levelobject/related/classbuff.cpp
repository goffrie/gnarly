#include "classbuff.h"

ClassBuff::ClassBuff(AttributeProvider* base, int atk, int def, int hp, int mp)
: AttributeDecorator(base), atkDelta(atk), defDelta(def), hpDelta(hp), mpDelta(mp) {
}

int ClassBuff::atk() const {
    return base->atk() + atkDelta;
}

int ClassBuff::def() const {
    return base->def() + defDelta;
}

int ClassBuff::startingHP() const {
    return base->startingHP() + hpDelta;
}

int ClassBuff::startingMP() const {
    return base->startingMP() + mpDelta;
}

AttributeProvider* ClassBuff::strip(bool force) {
    // This is semi-permenant, so keep it unless forced
    if (force) {
        return AttributeDecorator::strip(force);
    }
    // Otherwise, delete all decorators from base
    AttributeProvider* newBase = base->strip(force);
    // And assign that as the new base
    base = newBase;

    return this;
}
