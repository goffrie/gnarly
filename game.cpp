#include "game.h"

#include "cursesui.h"
#include "humanplayer.h"

#include <ncurses.h>

#include <cstring>
#include <iostream>

using namespace std;

Game::Game() : dungeon(Dungeon::defaultDungeon()), isDone(FALSE) {
    // TODO: class selection?
    display.add(&dungeon);
    player = new HumanPlayer(5, 5);
    pstatus = new PlayerStatus(*player);
    display.add(player, 1);
    display.add(pstatus);

    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

}

Game::~Game() {
    endwin();
    delete pstatus;
    delete player;
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
    ui.queryCommand(*this);
}

void Game::step() {

}

void Game::print() {
    display.draw(ui);
    refresh();
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
    isDone = TRUE;
}