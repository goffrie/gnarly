#ifndef __CLASSBUFF_H__
#define __CLASSBUFF_H__

#include "attributedecorator.h"
class ClassBuff : public AttributeDecorator {
    // The value of the buff on attack/defense/hp.
    int atkDelta, defDelta, hpDelta, mpDelta;
public:
    ClassBuff(AttributeProvider* base, int atk = 0, int def = 0, int hp = 0, int mp = 0);

    virtual int atk() const override;
    virtual int def() const override;
    virtual int startingHP() const override;
    virtual int startingMP() const override;
    virtual AttributeProvider* strip(bool force) override;
};

#endif
