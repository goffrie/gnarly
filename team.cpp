#include "team.h"

#include <cstdlib>

using namespace std;

vector<Team*> Team::teams;

Team::Team(Name i) : _index(i) {
    for (int j = 0; j < Num; j++) {
        if (i == j) {
            alliances.push_back(Ally);
        } else {
            alliances.push_back(Enemy);
        }
    }
}

bool Team::isAllied(Team* t) const {
    return (alliances[t->index()] == Ally);
}

void Team::ally(Team* t) {
    alliances[t->index()] = Ally;
    t->alliances[index()] = Ally;
}

void Team::unally(Team* t) {
    if (t == this) {
        // A team can't be unallied with itself.
        return;
    }
    alliances[t->index()] = Enemy;
    t->alliances[index()] = Enemy;
}

std::vector<Team::Status> Team::Team::getAlliances() const {
    return alliances;
}

void Team::setAlliances(std::vector<Team::Status> a) {
    for (int i = 0; i < Num; i++) {
        if (a[i] == Ally) {
            ally(Team::instance(static_cast<Name>(i)));
        } else if (a[i] == Enemy) {
            unally(Team::instance(static_cast<Name>(i)));
        }
    }
}

Team::Name Team::index() const{
    return _index;
}

void Team::init() {
    if (teams.empty()) {
        atexit(cleanup);
    }
    cleanup();

    for (int i = Players; i < Num; i++) {
        teams.push_back(new Team(static_cast<Name>(i)));
    }
    teams[Merchants]->ally(teams[Players]);
    teams[Merchants]->ally(teams[Monsters]);
}

void Team::cleanup() {
    for (unsigned int i = 0; i < teams.size(); i++) {
        delete teams[i];
    }
    teams.clear();
}

Team* Team::instance(Name n) {
    if (teams.empty()) {
        init();
    }
    return teams[n];
}
