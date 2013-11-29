#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "character.h"
#include "inventory.h"

class Class;
class ItemAdapter;

class Player : public Character {
    Class* playerClass;
    Inventory inventory;
    int _gold;
    int _currentXP;
    int _targetXP;
    int _xpLevel;

    static int targetXPForLevel(int l);

protected:
    virtual void reduceHP(int amt) override;
    virtual void levelUp();

public:
    Player(Attributes::Race r);

    virtual ~Player() = 0;

    virtual void addXP(int xp);
    virtual int xpLevel() const { return _xpLevel; }
    virtual int currentXP() const { return _currentXP; }
    virtual int targetXP() const { return _targetXP; }
    virtual int gold() const { return _gold; }
    virtual int score() const { return gold(); }
    virtual bool moveRelative(Direction d) override;
    // Does damage to a character
    virtual void damage(Character* other, int d);
    // Default attack. Calls damage()
    virtual void attack(Character* other) override;

    // Potion effect: restore (or remove) HP.
    // Calls into `addHp`.
    virtual void heal(int amt);
    // Potion effect: change attack/defense.
    virtual void applyBuff(int atk, int def);
    // Adds gold to a player (by picking up or killing baddies)
    virtual void addGold(int amt);
    // Removes all buffs. Usually called when travelling between levels
    virtual void stripBuffs();
    // Players can move on doors and passages
    virtual bool canMove(int nY, int nX);
    virtual void step();
    // Uses a skill, and returns true if it was successful
    virtual bool useSkill(int i);

    virtual void setClass(Class* c);

    virtual bool addToInventory(ItemAdapter* i);
    virtual void viewInventory();

    virtual std::string basicName() const override { return name(NoArticle); }
    virtual std::string name(Article a) const override;
    virtual void drawClass(Surface& target) const;

    virtual void accept(LevelObjectVisitor& v) override;
};

#endif
