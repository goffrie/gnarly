#include "stealth.h"
#include "player.h"

#include "ui.h"
#include <sstream>
#include <algorithm>

using namespace std;

vector<Team::Status> Stealth::allAlly;

Stealth::Stealth() : Skill(4), currentDuration(-1) {
    if (allAlly.empty()) {
        for (int i = 0; i < Team::Num; i++) {
            allAlly.push_back(Team::Ally);
        }
    }
}

bool Stealth::use(Player* p) {
    if (currentDuration > 0) {
        currentDuration = duration;
        Skill::use(p);
        return true;
    }
    currentDuration = duration;
    // Change alliances to allied with everyone
    Team* t = p->getTeam();
    storedAlliances = t->getAlliances();
    t->setAlliances(allAlly);
    Skill::use(p);
    return true;
}

void Stealth::removeStealth(Player* p) {
    // Make alliances to what they were before
    Team* t = p->getTeam();
    t->setAlliances(storedAlliances);
    UI::instance()->say("Stealth deactivated.");
}

void Stealth::notifyAttack(Player* p) {
    if (currentDuration > 0) {
        removeStealth(p);
        currentDuration = -1;
    }
}

void Stealth::step(Player* p) {
    if (currentDuration >= 0) {
        currentDuration--;
    }
    if (currentDuration == 0) {
        removeStealth(p);
    }
}

string Stealth::name() const{
    return "Stealth";
}

string Stealth::description() const {
    return "Turns you (and all your allies) invisible";
}

string Stealth::display() const {
    ostringstream line;
    int remaining = max(0, currentDuration);
    line << ": " << remaining << " " << (remaining == 1 ? "turn" : "turns") << " remaining";
    return line.str();
}
