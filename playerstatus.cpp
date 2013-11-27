#include "playerstatus.h"

#include "surface.h"
#include "player.h"
#include "commandargs.h"
#include "util.h"
#include "game.h"
#include <sstream>
#include <cctype>

using namespace std;

PlayerStatus::PlayerStatus(const Player& p) : Displayable(), player(p) { }

void PlayerStatus::draw(Surface& target) const {
    ostringstream line;
    line << "Race: " << titleCase(player.name(NoArticle)) << "   Gold: " << player.gold();
    if (gnarly) {
        line << "   Level: " << player.xpLevel() << "   XP: " << player.currentXP() << "/" << player.targetXP();
    }
    target.fillLine(25, line.str());
    line.str("");

    line << "HP: " << player.currentHP();
    if (gnarly) {
        line << "/" << player.startingHP() << " MP: " << player.currentMP() << "/" << player.startingMP();
    }
    target.fillLine(26, line.str());
    line.str("");

    line << "Atk: " << player.atk();
    target.fillLine(27, line.str());
    line.str("");

    line << "Def: " << player.def();
    target.fillLine(28, line.str());
    line.str("");

    line << "Floor " << Game::instance()->dungeonLevel();
    target.draw(25, 69, line.str());
    line.str("");

    player.drawClass(target);
}
