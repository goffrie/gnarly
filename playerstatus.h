#ifndef __PLAYER_STATUS_H__
#define __PLAYER_STATUS_H__

#include "displayable.h"


class Player;

// A Displayable showing the player's current status. Drawn at the bottom of the screen
class PlayerStatus final : public Displayable {
    const Player& player;
public:
    PlayerStatus(const Player& p);
    // Draws the status of the player. What it draws depends on whether gnarly is on or off
    virtual void draw(Surface& target) const override;
};

#endif
