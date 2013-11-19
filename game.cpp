#include "game.h"

#include "cursesui.h"
#include "humanplayer.h"

#include <cstring>
#include <iostream>

using namespace std;

Game::Game() : isDone(false) {
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
    while (!isDone) {
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
    if (player->moveRelative(d)) {
        // A player action happened, so step.
        step();
    } else {
        UI::instance()->say("You can't pass that way.");
    }
}

void Game::attack(Direction d) {
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
    UI::instance()->say("There couldn't possibly be anything to use there.");
}

void Game::restart() {
    UI::instance()->say("Nah.");
}

void Game::quit() {
    isDone = true;
}
