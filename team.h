#ifndef __TEAM_H__
#define __TEAM_H__

#include <vector>
#include <string>

enum TeamName {
    Players,
    Monsters,
    Merchants,
    Other,
    NumTeams
};

// I think team could be implemented nicer than this probably
class Team {
private:
    enum Status {
        Ally,
        Enemy
    };
    // The array of singletons of teams
    static std::vector<Team*> teams;
    // Stores alliance status with every other team. Note: alliances are bidirectional
    std::vector<Status> alliances;
    TeamName _index;

    Team(TeamName i);
    ~Team() { }

public:

    bool isAllied(Team * t) const;
    void ally(Team *t);
    void unally(Team *t);
    TeamName index() const;

private:
    // Initializes all teams with default values
    static void init();
    static void cleanup();

public:
    static Team* instance(TeamName n);
};

#endif