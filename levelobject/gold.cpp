#include "gold.h"
#include "player.h"
#include "levelobjectvisitor.h"
#include "surface.h"

#include <sstream>
#include <ncurses.h>

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

void Gold::draw(Surface& target) const {
    target.setColor(COLOR_YELLOW, COLOR_BLACK);
    LevelObject::draw(target);
    target.unsetColor(COLOR_YELLOW, COLOR_BLACK);
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
