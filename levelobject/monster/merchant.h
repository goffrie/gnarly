#ifndef __MERCHANT_H__
#define __MERCHANT_H__

#include "monster.h"

class Merchant : public Monster {
protected:
    virtual void reduceHP(int amt) override;
public:
    Merchant();
};

#endif
