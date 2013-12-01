#ifndef __PALADIN_H__
#define __PALADIN_H__

#include "class.h"

// A paladin class that a player can be
class Paladin : public Class {
public:
    Paladin();
    virtual std::string name() { return "paladin"; }
    // Modifiers used when creating or leveling class that are applied to the attributes of the player
    virtual AttributeProvider* getClassBuff(AttributeProvider* a) const;
    virtual AttributeProvider* getLevelBuff(AttributeProvider* a) const;
};

#endif
