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
        Vampire,
        Werewolf,
        Troll,
        Goblin,
        Merchant,
        Dragon,
        Phoenix
    };

private:
    const int _startingHP, _atk, _def;
    const char _tile;
    const std::string _name;

    Attributes(int hp, int a, int d, char t, const std::string& r);
public:
    virtual ~Attributes() { }
    virtual int startingHP() const { return _startingHP; }
    virtual int atk() const { return _atk; }
    virtual int def() const { return _def; }
    virtual char tile() const { return _tile; }
    virtual std::string name() const { return _name; }

    static Attributes get(Attributes::Race c);
};

#endif
