#ifndef __PLAYER_STATUS_H__
#define __PLAYER_STATUS_H__

#include "displayable.h"


class Player;

// A Displayable showing the player's current status. Drawn at the bottom of the screen
// Should not be subclassed.
class PlayerStatus : public Displayable {
    const Player& player;
public:
    PlayerStatus(const Player& p);
    // no virtual destructor because this class is only used as a PlayerStatus

    // Draws the status of the player. What it draws depends on whether gnarly is on or off
    virtual void draw(Surface& target) const;
};

#endif
