#ifndef __GAME_H__
#define __GAME_H__

#include "player.h"
#include "display.h"
#include "dungeon.h"
#include "playerstatus.h"

class Game {
    Player* player;
    PlayerStatus* pstatus;
    Display display;
    Dungeon dungeon;
public:
    Game();
    ~Game();

    void print() const;
};

#endif
