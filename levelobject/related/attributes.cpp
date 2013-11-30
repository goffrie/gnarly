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
        case Halfling:
            return Attributes(100, 20, 30, 20, 0, '@', "halfling");
        case Merchant:
            return Attributes(30, 0, 70, 5, 10, 'M', "merchant");
        case Dragon:
            return Attributes(150, 0, 20, 20, 20, 'D', "dragon");
        case Goblin:
            return Attributes(70, 0, 5, 10, 10, 'N', "goblin");
        case Vampire:
            return Attributes(50, 0, 25, 25, 20, 'V', "vampire");
        case Phoenix:
            return Attributes(50, 0, 35, 20, 20, 'X', "phoenix");
        case Unicorn:
            return Attributes(80, 0, 30, 15, 30, 'U', "unicorn");
        case Zombie:
            return Attributes(180, 0, 15, 0, 30, 'Z', "zombie");
        case Kelpie:
            return Attributes(100, 0, 20, 5, 30, 'K', "kelpie");
        case Werewolf:
            return Attributes(120, 0, 30, 5, 40, 'W', "werewolf");
        case Troll:
            return Attributes(120, 0, 25, 15, 40, 'T', "troll");
        case Roc:
            return Attributes(160, 0, 30, 30, 50, 'R', "roc");
        case Yukionna:
            return Attributes(100, 0, 60, 20, 60, 'Y', "yuki-onna");
        case Justicator:
            return Attributes(100, 0, 40, 70, 60, 'J', "justicator");
        case Lich:
            return Attributes(120, 0, 90, 0, 80, 'L', "lich");
        case Cyclops:
            return Attributes(200, 0, 45, 50, 90, 'C', "cyclops");
        case Ent:
            return Attributes(220, 0, 50, 100, 100, 'E', "ent");
        case Basilisk:
            return Attributes(160, 0, 90, 60, 120, 'B', "basilisk");
        case Archon:
            return Attributes(200, 0, 80, 80, 150, 'A', "archon");
        case Felldrake:
            return Attributes(200, 0, 85, 140, 180, 'F', "felldrake");
        case Shoggoth:
            return Attributes(300, 0, 50, 200, 220, 'S', "shoggoth");
        case Quetzalcoatl:
            return Attributes(300, 0, 100, 100, 300, 'Q', "quetzalcoatl");
        case Altar:
            return Attributes(300, 0, 0, 0, 0, '&', "altar");
        default:
            terminate();
    }
}
