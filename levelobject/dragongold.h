#ifndef __DRAGONGOLD_H__
#define __DRAGONGOLD_H__

#include "gold.h"

class DragonGold : public Gold {
private:
    bool dragonLives;
public:
    DragonGold();

    // Adds a dragon attached to the gold. Returns true if sucessfull
    virtual bool addDragon();
    virtual bool canPickUp() const;
    virtual void notifyDragonDied();
    virtual std::string basicName() const override;
    virtual std::string name(Article a) const override;
};

#endif
