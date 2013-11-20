#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "levelobject.h"
#include "attributeprovider.h"
#include "attributes.h"
#include <string>
#include <vector>

// An abstract class representing a character with HP, attack, and defense.
class Character : public LevelObject {
protected:
    AttributeProvider* attributes;
    int hp;
    // The team a character is on
    Team* team;

    virtual void reduceHp(int amt);
    virtual void addHp(int amt);

public:
    Character(CharAttr c, Team* t);
    virtual ~Character() = 0;

    int currentHp() const {
        return hp;
    }

    void takeDamage(int attack);
    virtual void attack(Character* other);
    virtual int atk() const { return attributes->atk(); }
    virtual int def() const { return attributes->def(); }
    virtual int startingHP() const { return attributes->startingHP(); }
    virtual char tile() const override { return attributes->tile(); }
    virtual std::string race() const { return attributes->race(); }

    virtual bool isEnemy(Team* t);
    virtual Character* chooseTarget(std::vector<LevelObject*> objs);

    virtual void accept(LevelObjectVisitor& v) override;
};

#endif
