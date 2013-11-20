#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "character.h"

class Player : public Character {
protected:
    virtual void reduceHp(int amt) override;
public:
    Player(CharAttr c);

    virtual ~Player();

    virtual bool canMove(int nY, int nX) override;
    virtual void attack(Character* other) override;

    // Potion effect: restore (or remove) HP.
    // Calls into `addHp`.
    virtual void restoreHp(int amt);
    // Potion effect: change attack/defense.
    virtual void applyBuff(int atk, int def);

    virtual void accept(LevelObjectVisitor& v) override;
};

#endif
