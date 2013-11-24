#ifndef __THIEF_H__
#define __THIEF_H__

#include "class.h"

class Thief : public Class {
public:
    Thief();
    virtual std::string name() { return "thief"; }
};

#endif
