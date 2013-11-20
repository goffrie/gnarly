#include "game.h"

#include "cursesui.h"
#include "humanplayer.h"
#include "potion.h"

#include <cstring>
#include <iostream>

using namespace std;

Game* Game::_instance = 0;

Game::Game() : _quit(false), gameOver(false), _shouldRestart(false) {
    cout << "Curses? (y/n)" << endl;
    char c;
    cin >> c;
    if (c == 'y') {
        UI::setInstance(new CursesUI());
    } else {
        UI::setInstance(new BasicUI());
    }
    // TODO: class selection?
    level = new Level();
    player = new HumanPlayer();
    pstatus = new PlayerStatus(*player);
    display.add(pstatus);
    display.add(player, 1);

    level->generate(player);
    level->addAllToDisplay(&display);
}

Game::~Game() {
    UI::setInstance(0);
    delete pstatus;
    delete player;
    delete level;
}

void Game::run() {
    print();
    while (!_quit) {
        readCommand();
        print();
    }
}

void Game::readCommand() {
    UI::instance()->queryCommand(*this);
}

void Game::step() {
    level->stepObjects();
}

void Game::print() {
    UI* ui = UI::instance();
    display.draw(*ui);
    ui->cursor(player->getY(), player->getX());
    ui->redraw();
}

void Game::move(Direction d) {
    if (gameOver) {
        return UI::instance()->say("You died x.x. Restart or quit.");
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
        return UI::instance()->say("You died x.x. Restart or quit.");
    }
    const int ny = player->getY() + directionDy(d),
              nx = player->getX() + directionDx(d);
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
        return UI::instance()->say("You died x.x. Restart or quit.");
    }
    const int ny = player->getY() + directionDy(d),
              nx = player->getX() + directionDx(d);
    if (level->free(ny, nx)) {
        UI::instance()->say("You drink an imaginary potion.");
        return;
    }
    Potion* target = dynamic_cast<Potion*>(level->objectAt(ny, nx));
    if (target) {
        target->use(player);
        delete target;
    } else {
        UI::instance()->say("That doesn't appear to be drinkable.");
    }
}

void Game::restart() {
    _shouldRestart = true;
    _quit = true;
}

void Game::quit() {
    _quit = true;
}

void Game::playerDied() {
    gameOver = true;
    UI::instance()->say("You died x.x");
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
