#include "game.h"

#include "potion.h"
#include "gold.h"
#include "staircase.h"
#include "commandargs.h"
#include "playerselect.h"
#include "dungeon.h"
#include "playerstatus.h"
#include "cursesui.h"
#include "basicui.h"
#include "level.h"
#include "popup.h"
#include "memory.h"
#include "target.h"


#include "dungeongen/aggregationgen.h"

#include <cstring>
#include <iostream>
#include <sstream>

using namespace std;

Game* Game::_instance = 0;

Game::Game() : player(0), pstatus(0), level(0), mem(0), popup(0), _quit(false), gameOver(false), _shouldRestart(false) {
    // Initialize the UI.
    if (gnarly) {
        UI::setInstance(new CursesUI());
    } else {
        UI::setInstance(new BasicUI());
    }

    // Do per-game initialization.
    Team::init();
    Potion::resetUsed();

    // Ask the user to select their player.
    PlayerSelect ps;
    player = ps.getPlayer(*UI::instance());
    if (!player) {
        _quit = true;
        return;
    }

    // Initialize the display.
    pstatus = new PlayerStatus(*player);
    display.add(pstatus);
    display.add(player, 2);

    // Set up the first dungeon level.
    Level::resetLevelCount();
    Team::resetAlliances();
    makeNewLevel();
}

Game::~Game() {
    UI::setInstance(0);
    delete pstatus;
    delete player;
    delete level;
    delete popup;
    delete mem;
}

void Game::run() {
    while (!_quit) {
        print();
        readCommand();
    }
}

void Game::readCommand() {
    UI::instance()->queryCommand(*this);
}

void Game::step() {
    player->step();
    level->stepObjects();
}

void Game::print() {
    UI& ui = *UI::instance();
    if (gnarly) {
        // Don't compute FOV in basic mode.
        level->computeFOV(player->getY(), player->getX(), 20);
    }
    display.draw(ui);
    level->draw(*mem);
    ui.cursor(player->getY(), player->getX());
    ui.redraw();
}

void Game::move(Direction d) {
    if (gameOver) {
        return UI::instance()->say("Game Over. Restart or quit.");
    }
    const int ny = player->getY() + d.dy(),
              nx = player->getX() + d.dx();
    // XXX make this more object oriented and elegant
    Staircase* stair = dynamic_cast<Staircase*>(level->objectAt(ny, nx));
    if (stair) {
        stair->descend();
        return;
    }
    Gold* target = dynamic_cast<Gold*>(level->objectAt(ny, nx));
    if (target && target->canPickUp()) {
        target->use(player);
        ostringstream line;

        line << target->amount() << " gold.";
        UI::instance()->say(line.str());
        delete target;
    }
    if (player->moveRelative(d)) {
        // A player action happened, so step.
        step();
    } else {
        UI::instance()->say("You can't pass that way.");
    }
}

void Game::attack(Direction d) {
    if (gameOver) {
        return UI::instance()->say("Game Over. Restart or quit.");
    }
    const int ny = player->getY() + d.dy(),
              nx = player->getX() + d.dx();
    if (level->free(ny, nx)) {
        UI::instance()->say("You swing at open space.");
        return;
    }
    // XXX ?
    Character* target = dynamic_cast<Character*>(level->objectAt(ny, nx));
    if (target) {
        player->attack(target);
        step();
    } else {
        UI::instance()->say("You can't attack that.");
    }
}

void Game::use(Direction d) {
    if (gameOver) {
        return UI::instance()->say("Game Over. Restart or quit.");
    }
    const int ny = player->getY() + d.dy(),
              nx = player->getX() + d.dx();
    if (level->free(ny, nx)) {
        UI::instance()->say("You drink an imaginary potion.");
        return;
    }
    Potion* target = dynamic_cast<Potion*>(level->objectAt(ny, nx));
    if (target) {
        target->use(player);
        delete target;
        step();
    } else {
        UI::instance()->say("That doesn't appear to be drinkable.");
    }
}

void Game::skill(int i) {
    if (gameOver) {
        return UI::instance()->say("Game Over. Restart or quit.");
    }
    if (player->useSkill(i)) {
        step();
    } else {
        UI::instance()->say(" Skill failed.");
    }
}

void Game::restart() {
    Potion::resetUsed();
    _shouldRestart = true;
    _quit = true;
}

void Game::quit() {
    _quit = true;
}

void Game::confirm() {
    delete popup;
    popup = 0;
}

LevelObject* Game::getTarget(int range) {
    Target t(player->getY(), player->getX(), range);
    pair<int,int> tar = t.getTarget();
    if (Target::validTarget(tar)) {
        print();
        return level->objectAt(tar.first, tar.second);
    } else {
        print();
        return 0;
    }
}

void Game::notifyPlayerDeath() {
    if (gameOver) return;
    gameOver = true;
    ostringstream line;

    line << "You Died x.x After failing to stop the monsters, they escaped to the surface. "
         "Nations fell before the neverending stream of monsters, and after countless years "
         "of struggle the entire world was devoured. Nothing ever lived ever again. The end.\n\n"
         "On the upside, you got " << player->gold() << " gold!";
    PopUp::make(line.str());
}

void Game::makeNewLevel() {
    if (gameOver) return;
    if (level->isLastLevel()) {
        gameOver = true;
        ostringstream line;

        line << "You Win \\(^o^)/ You saved the world! As soon as you succeed, people start reconsidering their lives. "
             "War ceases to exist and people learn to empathize with each other, and scarcity is solved.  "
             "Everyone lives happily ever after. The end.\n\n"
             "Score: " << player->score();
        PopUp::make(line.str());
        return;
    }
    if (level) {
        UI::instance()->say("You descended a level.");
        level->remove(player);
        delete level;
    }
    if (mem) {
        delete mem;
    }
    if (!layoutFile.empty()) {
        level = new Level(Dungeon::defaultDungeon());
        level->loadLayout(player);
    } else {
        level = AggregationGen(25, 79).generateLevel(player);
    }
    mem = new Memory(level->height(), level->width());
    display.add(mem, 0);
    display.add(level, 1);

    player->stripBuffs();
}

Game* Game::instance(bool reset) {
    if (_instance == 0 || reset) {
        if (_instance != 0) {
            delete _instance;
        } else {
            atexit(cleanup);
        }
        _instance = new Game;
    }
    return _instance;
}

void Game::cleanup() {
    delete _instance;
}
