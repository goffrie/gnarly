#include "monster.h"

#include "player.h"
#include "ui.h"
#include "level.h"

#include <sstream>
#include <vector>

using namespace std;

void Monster::step() {
    struct IsPlayerVisitor : public LevelObjectVisitor {
        Monster* m;
        void visit(Player& p) {
            // XXX: check hostile
            m->attack(&p);
        }
    };
    IsPlayerVisitor v;
    v.m = this;
    vector<LevelObject*> adj = getLevel()->neighbours(getY(), getX());
    for (unsigned int i = 0; i < adj.size(); ++i) {
        adj[i]->accept(v);
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
