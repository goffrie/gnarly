#ifndef __BASICBUFF_H__
#define __BASICBUFF_H__

#include "attributedecorator.h"
class BasicBuff : public AttributeDecorator {
    // The value of the buff on attack/defense.
    int atkDelta, defDelta;
public:
    BasicBuff(AttributeProvider* base, int atk, int def);

    virtual int atk() const;
    virtual int def() const;
};

#endif
