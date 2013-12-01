#ifndef __TEAM_H__
#define __TEAM_H__

#include <vector>
#include <string>

// A class that represents the alliances characters will have each other
// It is used for AI to decide what they should attack/move towards
class Team {
public:
    // The status of an alliance
    enum Status {
        Ally,
        Enemy
    };
    // All the teams that any character can be on
    enum Name {
        Players,
        Monsters,
        Merchants,
        Other,
        Num
    };

private:
    // The array of singletons of teams
    static std::vector<Team*> teams;
    // Stores alliance status with every other team. Note: alliances are bidirectional
    std::vector<Status> alliances;
    // Which team this is
    Name _index;

    // Initially enemy with everyone, except self
    Team(Name i);
    ~Team() { }

public:

    // Returns true if two teams are allied
    bool isAllied(Team * t) const;
    // Ally with a team (and have them ally with self)
    void ally(Team *t);
    // Unally with a team (and have the unally with self)
    void unally(Team *t);
    // Get all alliances
    std::vector<Team::Status> getAlliances() const;
    // Set all alliances to the given values
    void setAlliances(std::vector<Team::Status> a);
    Team::Name index() const;


// Multiton:
    // Initializes all teams with default values
    static void init();
private:
    // Delete all teams
    static void cleanup();

public:
    // Get a given team
    static Team* instance(Name n);
};

#endif
