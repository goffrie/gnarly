#include "player.h"
#include "game.h"

#include "ui.h"
#include "level.h"
#include "levelobjectvisitor.h"
#include "potionbuff.h"
#include "direction.h"

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

bool Player::moveRelative(Direction d) {
    if (LevelObject::moveRelative(d)) {
        UI::instance()->say("You moved ");
        return true;
    }
    return false;
}

void Player::attack(Character* other) {
    UI::instance()->say("You hit the " + other->name() + ".");
    other->takeDamage(atk());
    if (other->dead()) {
        addGold(other->droppedGold());
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

bool Player::canMove(int nY, int nX) {
    return getLevel()->valid(nY, nX) && getLevel()->free(nY, nX, true);
}

void Player::accept(LevelObjectVisitor& v) {
    v.visit(*this);
}
