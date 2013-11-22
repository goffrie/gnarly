#include "dwarfplayer.h"

DwarfPlayer::DwarfPlayer() : Player(Attributes::Dwarf) {
}

void DwarfPlayer::addGold(int amt) {
    Player::addGold(amt * 2);
}