#ifndef __CLASSBUFF_H__
#define __CLASSBUFF_H__

#include "attributedecorator.h"

// A buff applied by a class, either at creation, or by levelling up
class ClassBuff : public AttributeDecorator {
    // The value of the buff on attack/defense/hp/mp.
    int atkDelta, defDelta, hpDelta, mpDelta;
public:
    ClassBuff(AttributeProvider* base, int atk = 0, int def = 0, int hp = 0, int mp = 0);

    virtual int atk() const override;
    virtual int def() const override;
    virtual int startingHP() const override;
    virtual int startingMP() const override;
    // Unless forced, stripping odes not remove ClassBuff. This means it is not removed between floors
    virtual AttributeProvider* strip(bool force) override;
};

#endif
