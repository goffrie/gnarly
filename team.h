#ifndef __TEAM_H__
#define __TEAM_H__

#include <vector>
#include <string>


class Team {
public:
    enum Name {
        Player,
        Monster,
        Merchant,
        NumTeams
    };

private:
    enum Status {
        Ally,
        Enemy
    };
    // The array of singletons of teams
    static std::vector<Team*> teams;
    // Stores alliance status with every other team. Note: alliances are not necessarily bidirectional
    std::vector<Status> alliances;
    Team::Name _index;

    Team(Team::Name i);


public:

    bool isAllied(Team * t) const;
    void ally(Team *t);
    void unally(Team *t);
    Team::Name index();

private:
    // Initializes all teams with default values
    static void init();
    static void cleanup();

public:
    static Team* instance(Team::Name n);
};

#endif