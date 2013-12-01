#ifndef __HUMAN_PLAYER_H__
#define __HUMAN_PLAYER_H__

#include "player.h"

// A class representing a human player
class HumanPlayer : public Player {
public:
    // Created using human stats
    HumanPlayer();
    // Humans get 150% score
    virtual int score() const override;
};

#endif
