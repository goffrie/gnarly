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
#include "popup.h"

class Game : public CommandHandler {
    // Has ownership of `player`, `pstatus`, and 'level'.
    Player* player;
    PlayerStatus* pstatus;
    Level* level;
    PopUp* popup;

    Display display;

    bool _quit;
    bool gameOver;
    bool _shouldRestart;

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
    // Called when the player has died
    void notifyPlayerDeath();
    // Returns if the game should be restarted after it ends
    bool shouldRestart() { return _shouldRestart; }
    void makeNewLevel();

private:
    static Game* _instance;

    Game();
    virtual ~Game();
    static void cleanup();

    void makePlayer();

public:
    // Gets the game instance, creating and restarting if necessary
    static Game* instance(bool reset = false);
};

#endif
