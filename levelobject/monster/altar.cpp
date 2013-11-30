#include "altar.h"
#include "attributes.h"
#include "level.h"
#include "ui.h"
#include "rand.h"
#include "game.h"

#include <algorithm>

using namespace std;

int Altar::numAltars = 0;

Altar::Altar() : Monster(Attributes::Altar) {
    numAltars++;
}

Altar::~Altar() {
    numAltars--;
}

void Altar::step() {
}

void Altar::reduceHP(int amt) {
    Monster::reduceHP(amt);
    if (dead()) {
        UI::instance()->say("You destroyed the altar!");
        if (numAltars - 1 <= 0) {
            Game::instance()->makeNewLevel();
        }
    }
}

