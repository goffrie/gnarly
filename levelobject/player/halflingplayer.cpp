#include "halflingplayer.h"
#include "ui.h"
#include <cstdlib>

HalflingPlayer::HalflingPlayer() : Player(Attributes::Halfling) {
}

int HalflingPlayer::takeDamage(int attack) {
    if (rand() % 5 == 0) {
        UI::instance()->say("You avoided the attack!");
        return 0;
    }
    return Player::takeDamage(attack);
}
