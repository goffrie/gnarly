#include "altar.h"

#include "attributes.h"
#include "ui.h"
#include "game.h"

using namespace std;

int Altar::numAltars = 0;

Altar::Altar() : Monster(Attributes::Altar) {
    numAltars++;
}

Altar::~Altar() {
    numAltars--;
}

void Altar::step() {
    // Altars don't do anything
}

void Altar::reduceHP(int amt) {
    Monster::reduceHP(amt);
    if (dead()) {
        UI::instance()->say("You destroyed the altar!");
        if (numAltars - 1 <= 0) {
            // There are no more altars remaining on the level
            Game::instance()->makeNewLevel();
        }
    }
}

