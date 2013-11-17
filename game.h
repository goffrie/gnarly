#ifndef __GAME_H__
#define __GAME_H__

#include "player.h"
#include "display.h"
#include "dungeon.h"

class Game {
    Player* player;
    Display display;
    Dungeon dungeon;
public:
    Game();
    ~Game();

    void print() const;
};

#endif
