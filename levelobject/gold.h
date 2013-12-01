#ifndef __GOLD_H__
#define __GOLD_H__

#include "levelobject.h"

class Player;

// Gold to be placed on a level
class Gold : public LevelObject {
public:
    // The different possible kinds of gold
    enum Hoard {
        Normal,
        Small,
        Merchant,
        DragonH
    };
private:
    // How much gold is in the pile
    int _amount;
public:
    Gold(Hoard h);
    virtual void draw(Surface& target) const override;

    // Adds gold to a player
    virtual void use(Player* target);
    // Basic accessor methods
    virtual bool canPickUp() const { return true; }
    virtual int amount() const { return _amount; }
    virtual std::string basicName() const override;
    virtual std::string name(Article a) const override;

    virtual char tile() const override { return 'G'; }

    virtual void accept(LevelObjectVisitor& v);
};

#endif
