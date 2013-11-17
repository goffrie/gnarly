#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "displayable.h"

class Character : public Displayable {
protected:
    int hp;

    // The character's current position.
    int y, x;

// Pure virtual methods to be implemented by subclasses.
    virtual void reduceHp(int amt);
public:
    // The ASCII char that represents this character.
    virtual char tile() const = 0;

    virtual int atk() const = 0;
    virtual int def() const = 0;

public:
    Character(int startingHp, int y, int x);
    virtual ~Character();

    int currentHp() const {
        return hp;
    }

    void takeDamage(int attack);

    virtual void draw(UI& grid) const override;
};

#endif
