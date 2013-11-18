#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "levelobject.h"
#include "attributes.h"
#include <string>

// An abstract class representing a character with HP, attack, and defense.
class Character : public LevelObject {
protected:
    Attributes* attributes;
    int hp;

    virtual void reduceHp(int amt);

// Pure virtual methods to be implemented by subclasses.
public:

public:
    Character(int y, int x, CharAttr c);
    virtual ~Character();

    int currentHp() const {
        return hp;
    }

    void takeDamage(int attack);
    virtual int atk() const { return attributes->atk(); }
    virtual int def() const { return attributes->def(); }
    virtual int startingHP() const { return attributes->startingHP(); }
    virtual char tile() const override { return attributes->tile(); }
    virtual std::string race() const { return attributes->race(); }

    virtual void accept(LevelObjectVisitor& v) override { v.visit(*this); }
};

#endif
