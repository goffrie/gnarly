#include "attributes.h"

using namespace std;

Attributes::Attributes(int hp, int mp, int a, int d, int x, char t, const string& r) : 
  _startingHP(hp), 
  _startingMP(mp),
  _atk(a), 
  _def(d),
  _xp(x), 
  _tile(t), 
  _name(r) {
}

Attributes Attributes::get(Attributes::Race c) {
    switch (c) {
        case Human:
            return Attributes(140, 20, 20, 20, 0, '@', "human");
        case Dwarf:
            return Attributes(100, 20, 20, 30, 0, '@', "dwarf");
        case Elf:
            return Attributes(140, 20, 30, 10, 0, '@', "elf");
        case Orc:
            return Attributes(180, 20, 30, 25, 0, '@', "orc");
        case Vampire:
            return Attributes(50, 0, 25, 25, 20, 'V', "vampire");
        case Werewolf:
            return Attributes(120, 0, 30, 5, 30, 'W', "werewolf");
        case Troll:
            return Attributes(120, 0, 25, 15, 30, 'T', "troll");
        case Goblin:
            return Attributes(70, 0, 5, 10, 10, 'N', "goblin");
        case Merchant:
            return Attributes(30, 0, 70, 5, 10, 'M', "merchant");
        case Dragon:
            return Attributes(150, 0, 20, 20, 20, 'D', "dragon");
        case Phoenix:
            return Attributes(50, 0, 35, 20, 20, 'X', "phoenix");
        default:
            terminate();
    }
}