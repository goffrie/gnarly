#ifndef __GAME_H__
#define __GAME_H__

#include "player.h"
#include "display.h"
#include "dungeon.h"
#include "playerstatus.h"
#include "cursesui.h"
#include "basicui.h"
#include "commandhandler.h"
#include "level.h"

class Game : public CommandHandler {
    // Has ownership of `player`, `pstatus`, and 'level'.
    Player* player;
    PlayerStatus* pstatus;
    Level* level;

    Display display;

    bool isDone;

public:
    void run();
    void readCommand();
    void step();
    void print();
    void move(Direction d);
    void attack(Direction d);
    void use(Direction d);
    void quit();
    void restart();

private:
    static Game* _instance;

    Game();
    virtual ~Game();
    static void cleanup();

public:
    // Gets the game instance, creating if necessary
    static Game* instance();
};

#endif
