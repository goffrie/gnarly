#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "character.h"

class Player : public Character {
protected:
    // Since the constructor has no access to virtual methods,
    // we cannot expose the constructor as-is. Instead,
    // derived classes must call the `init` method.
    Player() : Character(0, 0) { }

    void init();
public:
    virtual char tile() const override { return '@'; }

    // To be overridden.
    virtual const char* race() const = 0;
    virtual int startingHp() const = 0;
    // And from Character:
    // virtual int atk() const = 0;
    // virtual int def() const = 0;

    virtual ~Player() { }

    virtual void accept(LevelObjectVisitor& v) override { v.visit(*this); }
};

#endif
