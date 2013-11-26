#ifndef __PALADIN_H__
#define __PALADIN_H__

#include "class.h"

class Paladin : public Class {
public:
    Paladin();
    virtual std::string name() { return "paladin"; }
    // Modifiers used when creating class
    virtual AttributeProvider* getClassBuff(AttributeProvider* a) const;
    virtual AttributeProvider* getLevelBuff(AttributeProvider* a) const;
};

#endif
