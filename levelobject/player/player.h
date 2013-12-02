#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "character.h"
#include "inventory.h"

class Class;
class ItemAdapter;

// An abstract class for the player character
class Player : public Character {
    // The character's class and inventory
    Class* playerClass;
    Inventory inventory;
    // The current gold, xp, xp to level, and experience level
    int _gold;
    int _currentXP;
    int _targetXP;
    int _xpLevel;

    // Returns the amount of XP needed to get to a level
    static int targetXPForLevel(int l);

protected:
    // When the player dies, we need to notify the game
    virtual void reduceHP(int amt);
    // Levelup the player, restoring hp, mp, buffing the player from the class
    virtual void levelUp();

public:
    Player(Attributes::Race r);

    virtual ~Player() = 0;

    // Adds experience to the player
    virtual void addXP(int xp);
    // Basic accessor methods for the player
    virtual int xpLevel() const { return _xpLevel; }
    virtual int currentXP() const { return _currentXP; }
    virtual int targetXP() const { return _targetXP; }
    virtual int gold() const { return _gold; }
    virtual int score() const { return gold(); }
    virtual std::string basicName() const { return name(NoArticle); }
    virtual std::string name(Article a) const;

    // Moving the player describes what the player sees
    virtual bool moveRelative(Direction d);
    // Does a given amount of damage to a character
    virtual void damage(Character* other, int d);
    // Default attack. Calls damage()
    virtual void attack(Character* other);

    // Potion/skill effect: restore (or remove) HP.
    // Calls into `addHP` or removeHP
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
    // Changes the player's class. Should only be used during player selection.
    // Note: does not delete the old class since it is still owned by the PlayerSelect
    virtual void setClass(Class* c);

    // If gnarly mode is off, uses an item immediately
    // If it is on, try to add it to your inventory, giving a message if it is full
    virtual bool addToInventory(ItemAdapter* i);
    // Display the inventory window where you can view and use your items
    virtual void viewInventory();

    // Draws the skills associated with the class
    virtual void drawClass(Surface& target) const;

    virtual void accept(LevelObjectVisitor& v);
};

#endif
