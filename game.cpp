#include "game.h"

#include "cursesui.h"
#include "humanplayer.h"

#include <ncurses.h>

#include <cstring>
#include <iostream>

using namespace std;

Game::Game() : dungeon(Dungeon::defaultDungeon()) {
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

void Game::print() const {
    CursesUI grid;
    display.draw(grid);
    refresh();
    grid.say("Really quit? ");
    grid.readLine();
}
