#include "playerstatus.h"

#include "ui.h"
#include "player.h"
#include <sstream>

using namespace std;

PlayerStatus::PlayerStatus(const Player& p) : player(p) { }

void PlayerStatus::draw(UI& screen) const {
    ostringstream line;

    line << "Race: " << player.race() << " Gold: " << /* XXX */ 0;
    screen.draw(25, 0, line.str());
    line.str("");

    line << "HP: " << player.currentHp();
    screen.draw(26, 0, line.str());
    line.str("");

    line << "Atk: " << player.atk();
    screen.draw(27, 0, line.str());
    line.str("");

    line << "Def: " << player.def();
    screen.draw(28, 0, line.str());
    line.str("");
}
