#ifndef __GAME_H__
#define __GAME_H__

#include "display.h"
#include "commandhandler.h"
#include "direction.h"

class Player;
class PlayerStatus;
class Level;
class Memory;
class PopUp;

class Game : public CommandHandler {
    // `Game` owns these objects.
    Player* player;
    PlayerStatus* pstatus;
    Level* level;
    Memory* mem;
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
    void skill(int i);
    void quit();
    void restart();
    void confirm();
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
