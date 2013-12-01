#include "halflingplayer.h"
#include "ui.h"
#include "rand.h"

HalflingPlayer::HalflingPlayer() : Player(Attributes::Halfling) {
}

Damage HalflingPlayer::computeDamage(int attack) {
    if (rnd(0, 5) == 0 /* 20% chance */) {
        UI::instance()->say("You avoided the attack!");
        return createDamage(0);
    }
    return Player::computeDamage(attack);
}
