#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "levelobject.h"
#include "attributeprovider.h"
#include "attributes.h"
#include "team.h"
#include <string>
#include <vector>

// An abstract class representing a character with various attributes.
class Character : public LevelObject {
protected:
    // The attributes associated with the character
    AttributeProvider* attributes;
    // The current hp/mp
    int hp, mp;
    // The team a character is on
    Team* team;

    // Low level method for adding and removing hp. Higher level methods
    // (like attacking and using potions) call into these
    virtual void reduceHP(int amt);
    virtual void addHP(int amt);

public:
    // Creates a character with a given race and team
    Character(Attributes::Race c, Team::Name t);
    virtual ~Character() = 0;

    virtual void draw(Surface& target) const override;

    // Basic accessor methods
    int currentHP() const { return hp; }
    int currentMP() const { return mp; }
    virtual Team* getTeam() const { return team; }
    // Decreases MP. Called when a spell is used
    virtual void reduceMP(int amt);

    // Takes damage from an attack and return the amount of damage taken
    virtual int takeDamage(int attack);
    // Attacks another character
    virtual void attack(Character* other);
    // Accessor methods that return things defined in attributes, and so go through attributes
    // Atk and Def cannot be negative
    virtual int atk() const;
    virtual int def() const;
    // Note: returns the exp dropped by this character upon death, not this character's current exp
    virtual int xp() const {return attributes->xp(); }
    virtual int startingHP() const { return attributes->startingHP(); }
    virtual int startingMP() const { return attributes->startingMP(); }
    virtual int droppedGold() const { return attributes->droppedGold(); }
    virtual char tile() const override { return attributes->tile(); }
    virtual std::string basicName() const override { return attributes->name(); }

    // Changes the team a monster is on
    virtual void setTeam(Team* t) { team = t; }
    // Returns true if dead
    virtual bool dead() const override;

    // Returns true if the two teams are unallied
    virtual bool isEnemy(Team* t) const;
    // Chooses a random enemy target from an array of possible targets
    virtual Character* chooseTarget(std::vector<LevelObject*> objs);

    virtual void accept(LevelObjectVisitor& v) override;
};

#endif
