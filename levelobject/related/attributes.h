#ifndef __ATTRIBUTES_H__
#define __ATTRIBUTES_H__

#include <string>
#include "attributeprovider.h"

// Starting stats (HP, atk, def, etc) associated with a character at creation depending on the race
class Attributes : public AttributeProvider {
public:
    // Every possible race
    enum Race {
        Human,
        Dwarf,
        Elf,
        Orc,
        Halfling,
        Vampire,
        Werewolf,
        Troll,
        Goblin,
        Merchant,
        Dragon,
        Phoenix,
        Unicorn,
        Zombie,
        Kelpie,
        Roc,
        Yukionna,
        Justicator,
        Lich,
        Cyclops,
        Ent,
        Basilisk,
        Archon,
        Felldrake,
        Shoggoth,
        Quetzalcoatl,
        Altar
    };

private:
    // Various stats associated with a given race
    const int _startingHP, _startingMP, _atk, _def, _xp, _droppedGold;
    const char _tile;
    const std::string _name;

    Attributes(int hp, int mp, int a, int d, int x, int dg, char t, const std::string& r);
public:
    virtual ~Attributes() { }
    // Accessor methods for stats associated with an attribute set
    virtual int startingHP() const { return _startingHP; }
    virtual int startingMP() const { return _startingMP; }
    virtual int atk() const { return _atk; }
    virtual int def() const { return _def; }
    virtual int xp() const { return _xp; }
    virtual int droppedGold() const { return _droppedGold; }
    virtual char tile() const { return _tile; }
    virtual std::string name() const { return _name; }

    // Returns the attributes associated with a race
    static Attributes get(Attributes::Race c);
};

#endif
