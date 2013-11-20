#ifndef __GOLD_H__
#define __GOLD_H__

#include "levelobject.h"
#include <string>

class Player;

// XXX: Should this and potion share a object class?
class Gold : public LevelObject {
public:
    enum Hoard {
        Normal,
        Small,
        Merchant,
        Dragon
    };
private:
    int _amount;
public:
    Gold(Hoard h);

    virtual void use(Player* target);
    virtual bool canPickUp() { return true; }
    virtual int amount() { return _amount; }

    // TODO: change to P after dev
    virtual char tile() const override { return 'G'; }

    virtual void accept(LevelObjectVisitor& v);
};

#endif
