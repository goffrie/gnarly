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
        ui = new CursesUI();
    } else {
        ui = new BasicUI();
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
    delete ui;
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
    ui->queryCommand(*this);
}

void Game::step() {
    ui->say("Nothing happens.");
    level->stepObjects();
}

void Game::print() {
    display.draw(*ui);
    ui->cursor(player->getY(), player->getX());
    ui->redraw();
}

void Game::move(Direction d) {
    if (player->moveRelative(d)) {
        // A player action happened, so step.
        step();
    } else {
        ui->say("You can't pass that way.");
    }
}

void Game::attack(Direction d) {
    ui->say("Give peace a chance.");
}

void Game::use(Direction d) {
    ui->say("There couldn't possibly be anything to use there.");
}

void Game::restart() {
    ui->say("Nah.");
}

void Game::quit() {
    isDone = true;
}
