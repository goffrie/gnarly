#ifndef __POTION_BUFF__
#define __POTION_BUFF__

#include "attributedecorator.h"
class PotionBuff : public AttributeDecorator {
    // The value of the buff on attack/defense.
    int atkDelta, defDelta;
public:
    PotionBuff(AttributeProvider* base, int atk, int def);

    virtual int atk() const;
    virtual int def() const;
};

#endif
