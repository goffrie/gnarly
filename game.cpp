#include "game.h"

#include "cursesui.h"
#include "humanplayer.h"
#include "elfplayer.h"
#include "dwarfplayer.h"
#include "orcplayer.h"
#include "potion.h"
#include "gold.h"
#include "staircase.h"

#include <cstring>
#include <iostream>
#include <sstream>

using namespace std;

Game* Game::_instance = 0;

Game::Game() : player(0), pstatus(0), level(0), _quit(false), gameOver(false), _shouldRestart(false) {
    makePlayer();
    if (_quit) {
        return;
    }
    cout << "Curses? (y/n)" << endl;
    char c;
    cin >> c;
    if (c == 'y') {
        UI::setInstance(new CursesUI());
    } else {
        UI::setInstance(new BasicUI());
    }
    pstatus = new PlayerStatus(*player);
    display.add(pstatus);
    display.add(player, 1);
    makeNewLevel();
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
    const int ny = player->getY() + directionDy(d),
              nx = player->getX() + directionDx(d);
    // XXX make this more object oriented and elegant
    Staircase* stair = dynamic_cast<Staircase*>(level->objectAt(ny, nx));
    if (stair) {
        stair->descend();
        UI::instance()->say("New level. Aren't you proud?");
    }
    Gold* target = dynamic_cast<Gold*>(level->objectAt(ny, nx));
    if (target) {
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
        step();
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

void Game::makeNewLevel() {
    if (level) {
        level->remove(player);
        delete level;
    }
    level = new Level(&display);

    level->generate(player);
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

void Game::makePlayer() {
    cout << "Choose your race: " << endl;
    cout << "(Easy - Elf (e), Easy - Orc(o), Normal - Human (h), Hard - Dwarf (d))" << endl;
    char c;
    cin >> c;
    switch (c) {
        case 'e':
            player = new ElfPlayer();
            break;
        case 'o':
            player = new OrcPlayer();
            break;
        case 'h':
            player = new HumanPlayer();
            break;
        case 'd':
            player = new DwarfPlayer();
            break;
        default:
            cout << "Quitting...";
            // XXX: this crashes
            _quit = true;
    }
}

void Game::cleanup() {
    delete _instance;
}
