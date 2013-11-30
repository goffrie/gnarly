#include "attributes.h"
#include "monster.h"
#include "potion.h"
#include "gold.h"
#include "dragongold.h"
#include "merchant.h"
#include "dragon.h"
#include "gnarlyspawn.h"

#include "rand.h"
using namespace std;

GnarlySpawn::GnarlySpawn(int l, bool r) : level(l), reallyRandom(r) { }

Monster* GnarlySpawn::getMonster(int i) {
    switch(i) {
        case 0: return new Merchant();
        case 1: return new Monster(Attributes::Goblin);
        case 2: return new Monster(Attributes::Vampire);
        case 3: return new Monster(Attributes::Phoenix);
        case 4: return new Monster(Attributes::Unicorn);
        case 5: return new Monster(Attributes::Zombie);
        case 6: return new Monster(Attributes::Kelpie);
        case 7: return new Monster(Attributes::Werewolf);
        case 8: return new Monster(Attributes::Troll);
        case 9: return new Monster(Attributes::Roc);
        case 10: return new Monster(Attributes::Yukionna);
        case 11: return new Monster(Attributes::Justicator);
        case 12: return new Monster(Attributes::Lich);
        case 13: return new Monster(Attributes::Cyclops);
        case 14: return new Monster(Attributes::Ent);
        case 15: return new Monster(Attributes::Basilisk);
        case 16: return new Monster(Attributes::Archon);
        case 17: return new Monster(Attributes::Felldrake);
        case 18: return new Monster(Attributes::Shoggoth);
        default: return new Monster(Attributes::Quetzalcoatl);
    }
}

Monster* GnarlySpawn::randomMonster() {
    if (reallyRandom) {
        return getMonster(rnd(0,20));
    }
    int monsterIndex = level * 4;
    switch(rnd(0, 100)) {
        case 0 ... 4: monsterIndex = 0; break;
        case 5 ... 14: monsterIndex -= 3; break;
        case 15 ... 24: monsterIndex -= 2; break;
        case 25 ... 39: monsterIndex -= 1; break;
        case 40 ... 59: monsterIndex = 0; break;
        case 60 ... 74: monsterIndex += 1; break;
        case 75 ... 84: monsterIndex += 2; break;
        case 85 ... 94: monsterIndex += 3; break;
        case 95 ... 99: monsterIndex += 4; break;
    }
    return getMonster(monsterIndex);
}

Potion* GnarlySpawn::randomPotion() {
    return new Potion(static_cast<Potion::Type>(rnd(0, Potion::numTypes)));
}

Gold* GnarlySpawn::randomGold() {
    switch(rnd(0, 8)) {
        case 0 ... 4:
            return new Gold(Gold::Normal);
        case 5 ... 6:
            return new Gold(Gold::Small);
        default:
            return new DragonGold();
    }
}
