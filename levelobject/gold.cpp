#include "gold.h"
#include "player.h"
#include "levelobjectvisitor.h"

#include <sstream>

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
        case DragonH:
            _amount = 6;
            break;
        default:
            terminate();
    }
}

void Gold::use(Player* target) {
    target->addGold(_amount);
}

string Gold::name() const {
    ostringstream line;
    line << amount() << " gold";
    return line.str();
}

void Gold::accept(LevelObjectVisitor& v) {
    v.visit(*this);
}
