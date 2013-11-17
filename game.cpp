#include "game.h"

#include "cursesui.h"

#include <ncurses.h>

#include <cstring>
#include <iostream>

using namespace std;

Game::Game() : dungeon(Dungeon::defaultDungeon()) {
    // TODO: class selection?
    display.add(&dungeon);
    player = 0;

    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
}

Game::~Game() {
    endwin();
    delete player;
}

void Game::print() const {
    CursesUI grid;
    display.draw(grid);
    refresh();
    grid.say("Really quit? ");
    grid.readLine();
}
