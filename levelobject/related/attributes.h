#ifndef __ATTRIBUTES_H__
#define __ATTRIBUTES_H__

#include <string>
#include "attributeprovider.h"

class Attributes : public AttributeProvider {
public:
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
        Quetzalcoatl
    };

private:
    const int _startingHP, _startingMP, _atk, _def, _xp;
    const char _tile;
    const std::string _name;

    Attributes(int hp, int mp, int a, int d, int x, char t, const std::string& r);
public:
    virtual ~Attributes() { }
    virtual int startingHP() const override { return _startingHP; }
    virtual int startingMP() const override { return _startingMP; }
    virtual int atk() const override { return _atk; }
    virtual int def() const override { return _def; }
    virtual int xp() const override { return _xp; }
    virtual char tile() const { return _tile; }
    virtual std::string name() const { return _name; }

    static Attributes get(Attributes::Race c);
};

#endif
