#ifndef __HUMAN_PLAYER_H__
#define __HUMAN_PLAYER_H__

#include "player.h"

class HumanPlayer : public Player {
public:
    HumanPlayer();
    virtual int score() const override;
};

#endif
