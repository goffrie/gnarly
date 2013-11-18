#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "levelobject.h"

// An abstract class representing a character with HP, attack, and defense.
class Character : public LevelObject {
protected:
    int hp;

    virtual void reduceHp(int amt);

// Pure virtual methods to be implemented by subclasses.
public:
    virtual int atk() const = 0;
    virtual int def() const = 0;

public:
    Character(int y, int x);
    virtual ~Character();

    int currentHp() const {
        return hp;
    }

    void takeDamage(int attack);

    virtual void accept(LevelObjectVisitor& v) override { v.visit(*this); }
};

#endif
