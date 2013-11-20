#include "team.h"

using namespace std;

vector<Team*> Team::teams;

Team::Team(Name i) : _index(i) {
    for (int i = 0; i < Name::NumTeams; i++) {
        alliances.push_back(Status::Enemy);
    }
}

bool Team::isAllied(Team* t) const {
    return (alliances[t->index()] == Status::Ally);
}

void Team::ally(Team* t) {
    alliances[t->index()] = Status::Ally;
    t->alliances[index()] = Status::Ally;
}

void Team::unally(Team* t) {
    alliances[t->index()] = Status::Enemy;
    t->alliances[index()] = Status::Enemy;
}

Team::Name Team::index() const{
    return _index;
}

void Team::init() {
    for (int i = Player; i < NumTeams; i++) {
        teams.push_back(new Team(static_cast<Name>(i)));
    }
    teams[Merchant]->ally(teams[Player]);
}

void Team::cleanup() {
    for (unsigned int i = 0; i < teams.size(); i++) {
        delete teams[i];
    }
}

Team* Team::instance(Team::Name n) {
    if (teams.empty()) {
        init();
        atexit(cleanup);
    }
    return teams[n];
}
