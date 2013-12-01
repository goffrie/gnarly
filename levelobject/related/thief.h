#ifndef __THIEF_H__
#define __THIEF_H__

#include "class.h"

// A Thief class that a player can be
class Thief : public Class {
public:
    Thief();
    virtual std::string name() { return "thief"; }
    // Modifiers used when creating or leveling class that are applied to the attributes of the player
    virtual AttributeProvider* getClassBuff(AttributeProvider* a) const;
    virtual AttributeProvider* getLevelBuff(AttributeProvider* a) const;
};

#endif
