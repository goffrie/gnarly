#ifndef __ALTAR_H__
#define __ALTAR_H__

#include "monster.h"

class Altar : public Monster {
    static int numAltars;
protected:
    virtual void reduceHP(int amt) override;

public:
    Altar();
    virtual ~Altar();
    virtual void step();
};

#endif
