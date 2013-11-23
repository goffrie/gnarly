#include "monster.h"

#include "player.h"
#include "ui.h"
#include "level.h"
#include "levelobjectvisitor.h"

#include <sstream>
#include <vector>

using namespace std;

Monster::Monster(Attributes::Race c) : Character(c, Monsters) {
}

void Monster::step() {
    Level* level = getLevel();
    // Attack random enemy.
    Character* toAttack = chooseTarget(level->neighbours(getY(), getX()));
    // Decide what to do.
    if (toAttack) {
        attack(toAttack);
    } else {
        wander();
    }
}

void Monster::wander() {
    vector<pair<int, int> > locations = getFreeAdjacent();

    // Pick one at random.
    if (locations.size() > 0) {
        pair<int, int> newLocation = locations[rand() % locations.size()];
        moveTo(newLocation.first, newLocation.second);
    }

}

void Monster::attack(Character* target) {
    ostringstream msg;
    if (rand() % 2 == 0) {
        msg << "The " << name() << " misses.";
        UI::instance()->say(msg.str());
    } else {
        msg << "The " << name() << " hits!";
        UI::instance()->say(msg.str());
        target->takeDamage(atk());
    }
}

void Monster::accept(LevelObjectVisitor& v) {
    v.visit(*this);
}
