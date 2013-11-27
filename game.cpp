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
#include "popupcreator.h"
#include "memory.h"
#include "target.h"

#include <cstring>
#include <iostream>
#include <sstream>

using namespace std;

Game* Game::_instance = 0;

Game::Game() : player(0), pstatus(0), level(0), mem(0), _quit(false), gameOver(false), _shouldRestart(false) {
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
    PopUpCreator::defeat(player->score());
}

void Game::makeNewLevel() {
    if (gameOver) return;
    if (level->isLastLevel()) {
        gameOver = true;
        PopUpCreator::victory(player->score());
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
    level = new Level();
    mem = new Memory(level->height(), level->width());
    display.add(mem, 0);
    display.add(level, 1);

    level->generate(player);
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
