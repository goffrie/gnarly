#include "humanplayer.h"

HumanPlayer::HumanPlayer() : Player(Attributes::Human) {
}

int HumanPlayer::score() const {
    return Player::score() * 3 / 2;
}
