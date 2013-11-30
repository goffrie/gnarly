#include "basicspawn.h"
#include "attributes.h"
#include "monster.h"
#include "potion.h"
#include "potionadapter.h"
#include "gold.h"
#include "dragongold.h"
#include "merchant.h"
#include "dragon.h"
#include "staircase.h"

#include "rand.h"

using namespace std;

Monster* BasicSpawn::randomMonster() {
    switch (rnd(0, 18)) {
        case 1 ... 4:
            return new Monster(Attributes::Werewolf);
        case 5 ... 7:
            return new Monster(Attributes::Vampire);
        case 8 ... 12:
            return new Monster(Attributes::Goblin);
        case 13 ... 14:
            return new Monster(Attributes::Troll);
        case 15 ... 16:
            return new Monster(Attributes::Phoenix);
        default:
            return new Merchant();
    }
}

PotionAdapter* BasicSpawn::randomPotion() {
    return new PotionAdapter(new Potion(static_cast<Potion::Type>(rnd(0, Potion::numTypes))));
}

Gold* BasicSpawn::randomGold() {
    switch(rnd(0, 8)) {
        case 0 ... 4:
            return new Gold(Gold::Normal);
        case 5 ... 6:
            return new Gold(Gold::Small);
        default:
            return new DragonGold();
    }
}

LevelObject* BasicSpawn::getFromTile(char t) {
    switch (t) {
        case '0': return new PotionAdapter(new Potion(Potion::RH));
        case '1': return new PotionAdapter(new Potion(Potion::BA));
        case '2': return new PotionAdapter(new Potion(Potion::BD));
        case '3': return new PotionAdapter(new Potion(Potion::PH));
        case '4': return new PotionAdapter(new Potion(Potion::WA));
        case '5': return new PotionAdapter(new Potion(Potion::WD));
        case '6': return new Gold(Gold::Normal);
        case '7': return new Gold(Gold::Small);
        case '8': return new Gold(Gold::Merchant);
        case '9': return new DragonGold();
        case '@': return 0;
        case 'V': return new Monster(Attributes::Vampire);
        case 'W': return new Monster(Attributes::Werewolf);
        case 'N': return new Monster(Attributes::Goblin);
        case 'D': return 0;
        case 'X': return new Monster(Attributes::Phoenix);
        case 'T': return new Monster(Attributes::Troll);
        case 'M': return new Merchant();
        case '\\': return new Staircase();
        default: return 0;
    }
}
