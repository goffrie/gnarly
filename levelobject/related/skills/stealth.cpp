#include "stealth.h"
#include "player.h"

#include "ui.h"
#include <sstream>

std::vector<Team::Status> Stealth::allAlly;

Stealth::Stealth() : currentDuration(-1) {
    if (allAlly.empty()) {
        for (int i = 0; i < NumTeams; i++) {
            allAlly.push_back(Team::Ally);
        }
    }
}

bool Stealth::use(Player* p) {
    Team* t = p->getTeam();
    storedAlliances = t->getAlliances();
    t->setAlliances(allAlly);
    currentDuration = duration;
    UI::instance()->say("You used " + name() + ".");
    return true;
}

void Stealth::removeStealth(Player* p) {
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

std::string Stealth::name() const{
    return "Stealth";
}

std::string Stealth::description() const {
    return "Turns you (and all your allies) invisible";
}

std::string Stealth::display() const {
    std::ostringstream line;
    line << ": " << (currentDuration > 0 ? currentDuration : 0) << " turns remaining";
    return line.str();
}
