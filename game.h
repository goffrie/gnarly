#ifndef __GAME_H__
#define __GAME_H__

#include "player.h"
#include "display.h"
#include "dungeon.h"
#include "playerstatus.h"
#include "cursesui.h"
#include "commandhandler.h"
#include "level.h"

class Game : public CommandHandler {
    // Has ownership of `player`, `pstatus`, and 'level'.
    Player* player;
    PlayerStatus* pstatus;
    Level* level;

    Display display;
    CursesUI ui;

    bool isDone;
public:
    Game();
    ~Game();

    void run();
    void readCommand();
    void step();
    void print();
    void move(Direction d);
    void attack(Direction d);
    void use(Direction d);
    void quit();
    void restart();
};

#endif
