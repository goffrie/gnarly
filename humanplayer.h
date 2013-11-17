#ifndef __HUMAN_PLAYER_H__
#define __HUMAN_PLAYER_H__

#include "player.h"

class HumanPlayer : public Player {
protected:
    virtual const char* race() const { return "Human"; }
    virtual int startingHp() const { return 140; }
    virtual int atk() const { return 20; }
    virtual int def() const { return 20; }

public:
    HumanPlayer(int y, int x);
};

#endif
