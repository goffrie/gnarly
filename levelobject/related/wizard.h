#ifndef __WIZARD_H__
#define __WIZARD_H__

#include "class.h"

class Wizard : public Class {
public:
    Wizard();
    virtual std::string name() { return "wizard"; }
    // Modifiers used when creating class
    virtual AttributeProvider* getClassBuff(AttributeProvider* a) const;
    virtual AttributeProvider* getLevelBuff(AttributeProvider* a) const;
};

#endif
