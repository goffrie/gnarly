#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "character.h"

class Player : public Character {
public:
    Player(CharAttr c) : Character(c) { }

    virtual ~Player() { }

    virtual void accept(LevelObjectVisitor& v) override { v.visit(*this); }
};

#endif
