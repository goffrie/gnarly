#ifndef __PLAYER_STATUS_H__
#define __PLAYER_STATUS_H__

#include "displayable.h"

// A Displayable showing the player's current status.

class Player;
class UI;

class PlayerStatus final : public Displayable {
    const Player& player;
public:
    PlayerStatus(const Player& p);
    virtual void draw(UI& screen) const override;
};

#endif
