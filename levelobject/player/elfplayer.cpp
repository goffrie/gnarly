#include "elfplayer.h"
#include <stdlib.h>

ElfPlayer::ElfPlayer() : Player(Attributes::Elf) {
}

void ElfPlayer::applyBuff(int a, int d) {
    Player::applyBuff(abs(a), abs(d));
}

void ElfPlayer::heal(int amt) {
    Player::heal(abs(amt));
}
