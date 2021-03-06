#include "monster.h"

#include "ui.h"
#include "level.h"
#include "levelobjectvisitor.h"
#include "util.h"
#include "rand.h"
#include "commandargs.h"

#include <sstream>
#include <vector>
#include <cstdlib>

using namespace std;

Monster::Monster(Attributes::Race c) : Character(c, Team::Monsters) {
}

void Monster::step() {
    Level* level = getLevel();
    // Attack random enemy.
    Character* toAttack = chooseTarget(level->neighbours(getY(), getX()));
    // Decide what to do.
    if (toAttack) {
        attack(toAttack);
    } else {
        Character* toFollow = 0;
        // In basic mode, only wander; don't follow.
        if (gnarly) {
            vector<LevelObject*> visible = level->getVisible(getY(), getX(), 5);
            toFollow = chooseTarget(visible);
        }
        if (toFollow) {
            moveToward(toFollow);
        } else {
            wander();
        }
    }
}

int dist(pair<int, int> a, pair<int, int> b) {
    return max(abs(a.first - b.first), abs(a.second - b.second));
}
int mdist(pair<int, int> a, pair<int, int> b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

void Monster::moveToward(Character* c) {
    const pair<int, int> target(c->getY(), c->getX());

    vector<pair<int, int> > locations = getFreeAdjacent();
    pair<int, int> best(getY(), getX());
    int bestDist = dist(target, best);
    int bestMdist = mdist(target, best);

    // Chooses the closest possible free adjacent location to the character
    // Sorting by manhattan distance if there is a tie, and randomization if there
    // is a further tie
    for (unsigned int i = 0; i < locations.size(); ++i) {
        int d = dist(target, locations[i]);
        int md = mdist(target, locations[i]);
        if (d < bestDist ||
                (d == bestDist && (md < bestMdist ||
                    (md == bestMdist && rnd(0, 2))))) {
            best = locations[i];
            bestDist = d;
            bestMdist = md;
        }
    }

    moveTo(best.first, best.second);
}

void Monster::wander() {
    vector<pair<int, int> > locations = getFreeAdjacent();

    // Pick free adjacent location at random.
    if (locations.size() > 0) {
        pair<int, int> newLocation = locations[rnd(0, locations.size())];
        moveTo(newLocation.first, newLocation.second);
    }
}

void Monster::attack(Character* target) {
    ostringstream msg;
    // Monsters miss half the time
    if (rnd(0, 2) == 0) {
        msg << capitalize(name(Definite)) << " misses " << target->name(Definite) << ".";
        UI::instance()->say(msg.str());
    } else {
        Damage damage = target->computeDamage(atk());
        msg << capitalize(name(Definite)) << " hits " << target->name(Definite) << " for " << damage.getAmount() << " dmg!";
        UI::instance()->say(msg.str());
        damage.apply();
    }
}

void Monster::accept(LevelObjectVisitor& v) {
    v.visit(*this);
}
