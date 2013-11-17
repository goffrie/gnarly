#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "character.h"

class Player : public Character {
protected:
    virtual char tile() const override { return '@'; }

    // To be overridden.
    virtual const char* race() const = 0;
    virtual int startingHp() const = 0;
    // And from Character:
    // virtual int atk() const = 0;
    // virtual int def() const = 0;

    // Since the constructor has no access to virtual methods,
    // we cannot expose the constructor as-is. Instead,
    // derived classes must call the `init` method.
    Player(int y, int x) : Character(0, y, x) { }

    void init();
public:
    virtual ~Player() { }
};

#endif
