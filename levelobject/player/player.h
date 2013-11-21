#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "character.h"

class Player : public Character {
    int _gold;

protected:
    virtual void reduceHP(int amt) override;
public:
    Player(Attributes::Race c);

    virtual ~Player();

    virtual int gold() const { return _gold; }

    virtual bool canMove(int nY, int nX) override;
    virtual void attack(Character* other) override;

    // Potion effect: restore (or remove) HP.
    // Calls into `addHp`.
    virtual void potionChangeHP(int amt);
    // Potion effect: change attack/defense.
    virtual void applyBuff(int atk, int def);
    // Adds gold to a player (by picking up or killing baddies)
    virtual void addGold(int amt);
    // Removes all buffs. Usually called when travelling between levels
    virtual void stripBuffs();

    virtual void accept(LevelObjectVisitor& v) override;
};

#endif
