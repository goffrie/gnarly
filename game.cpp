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
        step();
        print();
    }
}

void Game::readCommand() {
    ui->queryCommand(*this);
}

void Game::step() {
    level->stepObjects();
}

void Game::print() {
    display.draw(*ui);
    ui->redraw();
}

void Game::move(Direction d) {
    player->moveRelative(d);
}

void Game::attack(Direction d) {

}

void Game::use(Direction d) {
    
}

void Game::restart() {
    
}

void Game::quit() {
    isDone = true;
}
