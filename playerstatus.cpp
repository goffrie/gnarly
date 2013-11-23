#include "playerstatus.h"

#include "ui.h"
#include "player.h"
#include <sstream>

using namespace std;

PlayerStatus::PlayerStatus(const Player& p) : Displayable(), player(p) { }

void PlayerStatus::draw(UI& screen) const {
    ostringstream line;

    line << "Race: " << player.name() << " Gold: " << player.gold();
    screen.fillLine(25, line.str());
    line.str("");

    line << "HP: " << player.currentHP();
    screen.fillLine(26, line.str());
    line.str("");

    line << "Atk: " << player.atk();
    screen.fillLine(27, line.str());
    line.str("");

    line << "Def: " << player.def();
    screen.fillLine(28, line.str());
    line.str("");
}
