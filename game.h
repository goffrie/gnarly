#ifndef __GAME_H__
#define __GAME_H__

#include "player.h"
#include "display.h"
#include "dungeon.h"
#include "playerstatus.h"
#include "cursesui.h"

class Game {
    // Has ownership of `player` and `pstatus`.
    Player* player;
    PlayerStatus* pstatus;

    Display display;
    Dungeon dungeon;
    CursesUI ui;
public:
    Game();
    ~Game();

    void print();
};

#endif
