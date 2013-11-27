#ifndef __GAME_H__
#define __GAME_H__

#include "display.h"
#include "commandhandler.h"
#include "direction.h"

class Player;
class PlayerStatus;
class Level;
class Memory;
class LevelObject;

class Game : public CommandHandler {
    // `Game` owns these objects.
    Player* player;
    PlayerStatus* pstatus;
    Level* level;
    Memory* mem;

    Display display;

    bool _quit;
    bool gameOver;
    bool _shouldRestart;

    // The current dungeon level.
    int dlvl;

public:
    void run();
    void readCommand();
    void step();
    void print();
    void move(Direction d) override;
    void attack(Direction d) override;
    void use(Direction d) override;
    void skill(int i) override;
    void quit() override;
    void restart() override;
    void confirm() override;
    // Called when the player has died
    void notifyPlayerDeath();
    // Returns if the game should be restarted after it ends
    bool shouldRestart() { return _shouldRestart; }
    void makeNewLevel();
    LevelObject* getTarget(int range);


    int dungeonLevel() const { return dlvl; }

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
