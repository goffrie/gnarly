#include "monster.h"

#include "player.h"
#include "ui.h"
#include "level.h"
#include "levelobjectvisitor.h"

#include <sstream>
#include <vector>

using namespace std;

Monster::Monster(CharAttr c) : Character(c, Team::instance(Team::Name::Monster)) {
}

void Monster::step() {
    Level* level = getLevel();
    // Attack random enemy.
    Character* toAttack = chooseTarget(level->neighbours(getY(), getX()));
    // Decide what to do.
    if (toAttack) {
        attack(toAttack);
    } else {
        // Wander.

        // Look for a free location.
        vector<pair<int, int> > locations;
        for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {
                if (dy == 0 && dx == 0) continue;
                const int ny = getY() + dy,
                          nx = getX() + dx;
                if (level->free(ny, nx)) {
                    locations.push_back(make_pair(ny, nx));
                }
            }
        }

        // Pick one at random.
        if (locations.size() > 0) {
            pair<int, int> newLocation = locations[rand() % locations.size()];
            moveTo(newLocation.first, newLocation.second);
        }
    }
}

void Monster::attack(Character* target) {
    ostringstream msg;
    if (rand() % 2 == 0) {
        msg << "The " << race() << " misses.";
        UI::instance()->say(msg.str());
    } else {
        msg << "The " << race() << " hits!";
        UI::instance()->say(msg.str());
        target->takeDamage(atk());
    }
}

void Monster::accept(LevelObjectVisitor& v) {
    v.visit(*this);
}
