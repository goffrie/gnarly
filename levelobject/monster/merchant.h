#ifndef __MERCHANT_H__
#define __MERCHANT_H__

#include "monster.h"

// A merchant monster
class Merchant : public Monster {
protected:
    // When merchants die, the unally with the player
    virtual void reduceHP(int amt) override;
public:
    // Merchants have a different team from monster
    // that is initially allied with the player
    Merchant();
};

#endif
