#include "orcplayer.h"

OrcPlayer::OrcPlayer() : Player(Attributes::Orc), goldRemainder(0) {
}

void OrcPlayer::addGold(int amt) {
    if ((goldRemainder + amt) % 2 == 0) {
        Player::addGold((goldRemainder + amt) / 2);
        goldRemainder = 0;
    } else {
        Player::addGold(amt / 2);
        goldRemainder += amt % 2;
    }
}