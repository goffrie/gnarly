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

    virtual void reduceHP(int amt);
    virtual void addHP(int amt);

public:
    Character(Attributes::Race c, TeamName t);
    virtual ~Character() = 0;

    virtual void draw(Surface& target) const override;

    int currentHP() const {
        return hp;
    }

    int takeDamage(int attack);
    virtual void attack(Character* other);
    virtual int atk() const;
    virtual int def() const;
    virtual int startingHP() const { return attributes->startingHP(); }
    virtual char tile() const override { return attributes->tile(); }
    virtual std::string name() const override { return attributes->name(); }
    virtual Team* getTeam() const { return team; }
    virtual void setTeam(Team* t) { team = t; }
    virtual int droppedGold() const { return 0; }
    virtual bool dead() const override;

    virtual bool isEnemy(Team* t) const;
    virtual Character* chooseTarget(std::vector<LevelObject*> objs);

    virtual void accept(LevelObjectVisitor& v) override;
};

#endif
