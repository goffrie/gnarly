#include "elfplayer.h"
#include <stdlib.h>
#include "potionbuff.h"

ElfPlayer::ElfPlayer() : Player(Attributes::Elf) {
}

void ElfPlayer::applyBuff(int a, int d) {
    Player::applyBuff(abs(a), abs(d));
}

void ElfPlayer::potionChangeHP(int amt) {
    Player::potionChangeHP(abs(amt));
}
