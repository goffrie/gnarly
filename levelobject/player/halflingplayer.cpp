#include "halflingplayer.h"
#include "ui.h"
#include "rand.h"

HalflingPlayer::HalflingPlayer() : Player(Attributes::Halfling) {
}

int HalflingPlayer::takeDamage(int attack) {
    if (rnd(0, 5) == 0 /* 20% chance */) {
        UI::instance()->say("You avoided the attack!");
        return 0;
    }
    return Player::takeDamage(attack);
}
