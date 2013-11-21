#include "player.h"
#include "game.h"

#include "ui.h"
#include "level.h"
#include "levelobjectvisitor.h"
#include "potionbuff.h"

Player::Player(Attributes::Race c) : Character(c, Players), _gold(0) {
}

Player::~Player() {
}

void Player::reduceHP(int amt) {
    hp -= amt;
    if (hp <= 0) {
        Game::instance()->notifyPlayerDeath();
    }
}

void Player::attack(Character* other) {
    UI::instance()->say("You hit the " + other->race() + ".");
    other->takeDamage(atk());
    if (other->dead()) {
        addGold(1);
    }
}

void Player::potionChangeHP(int amt) {
    if (amt > 0) {
        addHP(amt);
    } else {
        reduceHP(-amt);
    }
}

void Player::applyBuff(int a, int d) {
    attributes = new PotionBuff(attributes, a, d);
}

void Player::addGold(int amt) {
    _gold += amt;
}

void Player::stripBuffs() {
    attributes = attributes->strip();
}

void Player::accept(LevelObjectVisitor& v) {
    v.visit(*this);
}
