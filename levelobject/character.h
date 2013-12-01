#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "levelobject.h"
#include "attributeprovider.h"
#include "attributes.h"
#include "team.h"
#include <string>
#include <vector>

// An abstract class representing a character with HP, attack, and defense.
class Character : public LevelObject {
protected:
    AttributeProvider* attributes;
    int hp, mp;
    // The team a character is on
    Team* team;

    virtual void reduceHP(int amt);
    virtual void addHP(int amt);

public:
    Character(Attributes::Race c, Team::Name t);
    virtual ~Character() = 0;

    virtual void draw(Surface& target) const override;

    int currentHP() const { return hp; }
    int currentMP() const { return mp; }
    virtual void reduceMP(int amt);

    virtual int takeDamage(int attack);
    virtual void attack(Character* other);
    virtual int atk() const;
    virtual int def() const;
    virtual int xp() const {return attributes->xp(); }
    virtual int startingHP() const { return attributes->startingHP(); }
    virtual int startingMP() const { return attributes->startingMP(); }
    virtual char tile() const override { return attributes->tile(); }
    virtual std::string basicName() const override { return attributes->name(); }
    virtual Team* getTeam() const { return team; }
    virtual void setTeam(Team* t) { team = t; }
    virtual int droppedGold() const { return 0; }
    virtual bool dead() const override;

    virtual bool isEnemy(Team* t) const;
    virtual Character* chooseTarget(std::vector<LevelObject*> objs);

    virtual void accept(LevelObjectVisitor& v) override;
};

#endif
