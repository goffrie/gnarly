#include "monster.h"

#include "player.h"
#include "ui.h"
#include "level.h"

#include <sstream>
#include <vector>

using namespace std;

void Monster::step() {
    Level* level = getLevel();

    // Look for an adjacent player.
    struct IsPlayerVisitor : public LevelObjectVisitor {
        Player* player;
        void visit(Player& p) {
            player = &p;
        }
    };
    IsPlayerVisitor v;
    v.player = 0;
    vector<LevelObject*> adj = level->neighbours(getY(), getX());
    for (unsigned int i = 0; i < adj.size(); ++i) {
        adj[i]->accept(v);
    }
    // Decide what to do.
    if (v.player) {
        // Attack the player.
        // XXX: check hostile
        attack(v.player);
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
        UI::instance()->say(msg.str().c_str());
    } else {
        msg << "The " << race() << " hits!";
        UI::instance()->say(msg.str().c_str());
        target->takeDamage(atk());
    }
}
