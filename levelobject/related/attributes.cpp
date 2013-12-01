#include "attributes.h"

using namespace std;

Attributes::Attributes(int hp, int mp, int a, int d, int x, int dg, char t, const string& r) : 
  _startingHP(hp), 
  _startingMP(mp),
  _atk(a), 
  _def(d),
  _xp(x),
  _droppedGold(dg),
  _tile(t), 
  _name(r) {
}

Attributes Attributes::get(Attributes::Race c) {
    switch (c) {
        case Human:
            return Attributes(140, 20, 20, 20, 0, 0, '@', "human");
        case Dwarf:
            return Attributes(100, 20, 20, 30, 0, 0, '@', "dwarf");
        case Elf:
            return Attributes(140, 20, 30, 10, 0, 0, '@', "elf");
        case Orc:
            return Attributes(180, 20, 30, 25, 0, 0, '@', "orc");
        case Halfling:
            return Attributes(100, 20, 30, 20, 0, 0, '@', "halfling");
        case Merchant:
            return Attributes(30, 0, 70, 5, 10, 0, 'M', "merchant");
        case Dragon:
            return Attributes(150, 0, 20, 20, 20, 0, 'D', "dragon");
        case Goblin:
            return Attributes(70, 0, 5, 10, 10, 1, 'N', "goblin");
        case Vampire:
            return Attributes(50, 0, 25, 25, 20, 1, 'V', "vampire");
        case Phoenix:
            return Attributes(50, 0, 35, 20, 20, 1, 'X', "phoenix");
        case Unicorn:
            return Attributes(80, 0, 30, 15, 30, 1, 'U', "unicorn");
        case Zombie:
            return Attributes(180, 0, 15, 0, 30, 1, 'Z', "zombie");
        case Kelpie:
            return Attributes(100, 0, 20, 5, 30, 1, 'K', "kelpie");
        case Werewolf:
            return Attributes(120, 0, 30, 5, 40, 1, 'W', "werewolf");
        case Troll:
            return Attributes(120, 0, 25, 15, 40, 1, 'T', "troll");
        case Roc:
            return Attributes(160, 0, 30, 30, 50, 1, 'R', "roc");
        case Yukionna:
            return Attributes(100, 0, 60, 20, 60, 1, 'Y', "yuki-onna");
        case Justicator:
            return Attributes(100, 0, 40, 70, 60, 1, 'J', "justicator");
        case Lich:
            return Attributes(120, 0, 90, 0, 80, 1, 'L', "lich");
        case Cyclops:
            return Attributes(200, 0, 45, 50, 90, 1, 'C', "cyclops");
        case Ent:
            return Attributes(220, 0, 50, 100, 100, 1, 'E', "ent");
        case Basilisk:
            return Attributes(160, 0, 90, 60, 120, 1, 'B', "basilisk");
        case Archon:
            return Attributes(200, 0, 80, 80, 150, 1, 'A', "archon");
        case Felldrake:
            return Attributes(200, 0, 85, 140, 180, 1, 'F', "felldrake");
        case Shoggoth:
            return Attributes(300, 0, 50, 200, 220, 1, 'S', "shoggoth");
        case Quetzalcoatl:
            return Attributes(300, 0, 100, 100, 300, 1, 'Q', "quetzalcoatl");
        case Altar:
            return Attributes(300, 0, 0, 0, 0, 0, '&', "altar");
        default:
            terminate();
    }
}
