#ifndef __GAME_H__
#define __GAME_H__

#include "display.h"
#include "commandhandler.h"
#include "direction.h"
#include "levelgen/levelplan.h"

class Player;
class PlayerStatus;
class Level;
class Memory;
class LevelObject;

// A central class that reads input from the UI and controls the game flow
class Game : public CommandHandler {
    // `Game` owns these objects.
    Player* player;
    PlayerStatus* pstatus;
    Level* level;
    // What the grid looked like when last seen
    Memory* mem;

    // The order of Level generation methods. In basic, it uses the same plan 8 times
    LevelPlan plan;

    // Most of the objects that need to be drawn, sorted in drawing order
    Display display;

    // The current status of the game
    bool _quit;
    bool gameOver;
    bool _shouldRestart;

    // The current dungeon level.
    int dlvl;

    void print();
    void step();
public:
    void run();
    void move(Direction d) override;
    void attack(Direction d) override;
    void use(Direction d) override;
    void skill(int i) override;
    void inventory() override;
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

public:
    // Gets the game instance, creating and restarting if necessary
    static Game* instance(bool reset = false);
};

#endif
