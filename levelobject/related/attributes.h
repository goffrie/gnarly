#ifndef __ATTRIBUTES_H__
#define __ATTRIBUTES_H__

#include <string>
#include "attributeprovider.h"

enum CharAttr {
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

class Attributes : public AttributeProvider {
    const int startingHP_, atk_, def_;
    const char tile_;
    const std::string race_;

    Attributes(int hp, int a, int d, char t, const std::string& r);
public:
    virtual ~Attributes() { }
    virtual int startingHP() const { return startingHP_; }
    virtual int atk() const { return atk_; }
    virtual int def() const { return def_; }
    virtual char tile() const { return tile_; }
    virtual std::string race() const { return race_; }

    static Attributes get(CharAttr c);
};

#endif
