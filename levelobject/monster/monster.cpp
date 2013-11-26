#include "monster.h"

#include "player.h"
#include "ui.h"
#include "level.h"
#include "levelobjectvisitor.h"
#include "util.h"

#include <sstream>
#include <vector>
#include <cstdlib>

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
        vector<LevelObject*> visible = level->getVisible(getY(), getX(), 5);
        Character* toFollow = chooseTarget(visible);
        if (toFollow) {
            moveToward(toFollow);
        } else {
            wander();
        }
    }
}

void Monster::moveToward(Character* c) {
    const int cY = c->getY(), cX = c->getX();

    vector<pair<int, int> > locations = getFreeAdjacent();
    pair<int, int> best = make_pair(getY(), getX());
    int bestDist = abs(cY - best.first) + abs(cX - best.second);

    for (int i = 0; i < locations.size(); ++i) {
        int dist = abs(cY - locations[i].first) + abs(cX - locations[i].second);
        if (dist < bestDist) {
            best = locations[i];
            bestDist = dist;
        }
    }

    moveTo(best.first, best.second);
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
        msg << capitalize(name(Definite)) << " misses " << target->name(Definite) << ".";
        UI::instance()->say(msg.str());
    } else {
        int damage = target->takeDamage(atk());
        msg << capitalize(name(Definite)) << " hits " << target->name(Definite) << " for " << damage << " dmg!";
        UI::instance()->say(msg.str());
    }
}

void Monster::accept(LevelObjectVisitor& v) {
    v.visit(*this);
}
