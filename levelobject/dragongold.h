#ifndef __DRAGONGOLD_H__
#define __DRAGONGOLD_H__

#include "gold.h"

// A pile of gold associated with a dragon. When the dragon dies, notifyDragonDied
// is called and the gold can be picked up
class DragonGold : public Gold {
private:
    // True if the associated dragon is still alive
    bool dragonLives;
public:
    DragonGold();

    // Adds a dragon attached to the gold directly to the level. Returns true if sucessfull
    virtual bool addDragon();
    // True if the associated dragon is dead
    virtual bool canPickUp() const;
    // Called when the associated dragon dies
    virtual void notifyDragonDied();
    virtual std::string basicName() const;
    virtual std::string name(Article a) const;
};

#endif
