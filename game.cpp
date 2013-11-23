#include "game.h"

#include "cursesui.h"
#include "player.h"
#include "potion.h"
#include "gold.h"
#include "staircase.h"
#include "commandargs.h"
#include "playerselect.h"

#include <cstring>
#include <iostream>
#include <sstream>

using namespace std;

Game* Game::_instance = 0;

Game::Game() : player(0), pstatus(0), level(0), mem(25, 79), popup(0), _quit(false), gameOver(false), _shouldRestart(false) {
    PlayerSelect ps;
    if (gnarly) {
        UI::setInstance(new CursesUI());
    } else {
        UI::setInstance(new BasicUI());
    }
    player = ps.getPlayer(*UI::instance());
    if (!player) {
        _quit = true;
        return;
    }
    pstatus = new PlayerStatus(*player);
    display.add(pstatus);
    display.add(player, 1);
    Level::resetLevelCount();
    makeNewLevel();
}

Game::~Game() {
    UI::setInstance(0);
    delete pstatus;
    delete player;
    delete level;
    delete popup;
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
    level->stepObjects();
}

void Game::print() {
    UI& ui = *UI::instance();
    display.draw(ui);
    mem.draw(ui);
    level->drawPOV(player->getY(), player->getX(), 20, ui, mem);
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

        line << "YAY!!! " << target->amount() << " GOLD!!!";
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

void Game::restart() {
    Potion::resetUsed();
    _shouldRestart = true;
    _quit = true;
}

void Game::quit() {
    _quit = true;
}

void Game::notifyPlayerDeath() {
    gameOver = true;
    UI::instance()->say("Game Over");
    ostringstream line;

    line << "You Died x.x After failing to stop the monsters, they escaped to the surface. "
         "Nations fell before the neverending stream of monsters, and after countless years "
         "of struggle the entire world was devoured. Nothing ever lived ever again. The end.\n\n"
         "On the upside, you got " << player->gold() << " gold!";
    popup = new PopUp(line.str(), 5, 5, 17, 69);
    display.add(popup, 2);
}

void Game::makeNewLevel() {
    if (level->isLastLevel()) {
        gameOver = true;
        UI::instance()->say("Game Over");
        ostringstream line;

        line << "You Win \\(^o^)/ You saved the world! As soon as you succeed, people start reconsidering their lives. "
             "War ceases to exist and people learn to empathize with each other, and scarcity is solved.  "
             "Everyone lives happily ever after. The end.\n\n"
             "Score: " << player->score();
        popup = new PopUp(line.str(), 5, 5, 17, 69);
        display.add(popup, 2);
        return;
    }
    if (level) {
        UI::instance()->say("You descended a level.");
        level->remove(player);
        delete level;
    }
    level = new Level(&display);
    mem = Memory(25, 79);

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
