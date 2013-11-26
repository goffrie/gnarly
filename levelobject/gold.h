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
        DragonH
    };
private:
    int _amount;
public:
    Gold(Hoard h);
    virtual void draw(Surface& target) const override;

    virtual void use(Player* target);
    virtual bool canPickUp() const { return true; }
    virtual int amount() const { return _amount; }
    virtual std::string basicName() const override;
    virtual std::string name(Article a) const override;

    virtual char tile() const override { return 'G'; }

    virtual void accept(LevelObjectVisitor& v);
};

#endif
