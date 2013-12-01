#ifndef __WIZARD_H__
#define __WIZARD_H__

#include "class.h"

// A wizard class with wizard skills
class Wizard : public Class {
public:
    Wizard();
    virtual std::string name() { return "wizard"; }
    // Modifiers used when creating or leveling class that are applied to the attributes of the player
    virtual AttributeProvider* getClassBuff(AttributeProvider* a) const;
    virtual AttributeProvider* getLevelBuff(AttributeProvider* a) const;
};

#endif
