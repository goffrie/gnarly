#ifndef __ALTAR_H__
#define __ALTAR_H__

#include "monster.h"

// An altar (not really a monster in that it doesn't move)
class Altar : public Monster {
    // The number of altars remaining
    static int numAltars;
protected:
    // When an altar is destroyed, and there are no other altars alive,
    // The game descends to the next level or ends the game if there is no
    // next level
    virtual void reduceHP(int amt);

public:
    Altar();
    virtual ~Altar();
    // Altars do not act
    virtual void step();
};

#endif
