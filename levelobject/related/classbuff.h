#ifndef __CLASSBUFF_H__
#define __CLASSBUFF_H__

#include "attributedecorator.h"

// A buff applied by a class, either at creation, or by levelling up
class ClassBuff : public AttributeDecorator {
    // The value of the buff on attack/defense/hp/mp.
    int atkDelta, defDelta, hpDelta, mpDelta;
public:
    ClassBuff(AttributeProvider* base, int atk = 0, int def = 0, int hp = 0, int mp = 0);

    virtual int atk() const;
    virtual int def() const;
    virtual int startingHP() const;
    virtual int startingMP() const;
    // Unless forced, stripping odes not remove ClassBuff. This means it is not removed between floors
    virtual AttributeProvider* strip(bool force);
};

#endif
