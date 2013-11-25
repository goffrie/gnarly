#include "team.h"

using namespace std;

vector<Team*> Team::teams;

Team::Team(TeamName i) : _index(i) {
    for (int j = 0; j < NumTeams; j++) {
        if (i == j) {
            alliances.push_back(Status::Ally);
        } else {
            alliances.push_back(Status::Enemy);
        }
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

std::vector<Team::Status> Team::Team::getAlliances() const {
    return alliances;
}

void Team::setAlliances(std::vector<Team::Status> a) {
    for (int i = 0; i < NumTeams; i++) {
        if (a[i] == Status::Ally) {
            ally(Team::instance(static_cast<TeamName>(i)));
        } else if (a[i] == Status::Enemy) {
            unally(Team::instance(static_cast<TeamName>(i)));
        }
    }
}

TeamName Team::index() const{
    return _index;
}

void Team::init() {
    for (int i = Players; i < NumTeams; i++) {
        teams.push_back(new Team(static_cast<TeamName>(i)));
    }
    teams[Merchants]->ally(teams[Players]);
    teams[Merchants]->ally(teams[Monsters]);
}

void Team::cleanup() {
    for (unsigned int i = 0; i < teams.size(); i++) {
        delete teams[i];
    }
}

Team* Team::instance(TeamName n) {
    if (teams.empty()) {
        init();
        atexit(cleanup);
    }
    return teams[n];
}

void Team::resetAlliances() {
    teams[Merchants]->ally(teams[Players]);
}
