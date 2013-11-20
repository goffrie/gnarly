#include "gold.h"
#include "player.h"
#include "levelobjectvisitor.h"

using namespace std;

Gold::Gold(Hoard h) {
    switch (h) {
        case Normal:
            _amount = 1;
            break;
        case Small:
            _amount = 2;
            break;
        case Merchant:
            _amount = 4;
            break;
        case Dragon:
            _amount = 6;
            break;
        default:
            terminate();
    }
}

void Gold::use(Player* target) {
    target->addGold(_amount);
}

void Gold::accept(LevelObjectVisitor& v) {
    v.visit(*this);
}
