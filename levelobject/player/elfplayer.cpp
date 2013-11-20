#include "elfplayer.h"
#include <stdlib.h>
#include "potionbuff.h"

ElfPlayer::ElfPlayer() : Player(Elf) {
}

void ElfPlayer::applyBuff(int a, int d) {
    attributes = new PotionBuff(attributes, abs(a), abs(d));
}
