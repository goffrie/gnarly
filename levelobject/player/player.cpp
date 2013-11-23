#include "player.h"
#include "game.h"

#include "ui.h"
#include "level.h"
#include "levelobjectvisitor.h"
#include "potionbuff.h"
#include "direction.h"
#include <sstream>

using namespace std;

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
        ostringstream msg;
        msg << "You moved " << d.name() << " and see ";
        vector<LevelObject*> neighbours = getLevel()->neighbours(getY(), getX());
        if (neighbours.empty()) {
            msg << "nothing";
        } else {
            msg << "a " <<neighbours[0]->name();
            for (unsigned int i = 1; i < neighbours.size(); i++) {
                if (i == neighbours.size() - 1) {
                    msg << " and a " << neighbours[i]->name();
                } else {
                    msg << ", a " << neighbours[i]->name();
                }
            }
        }
        msg << ".";
        UI::instance()->say(msg.str());
        return true;
    }
    return false;
}

void Player::attack(Character* other) {
    ostringstream msg;
    int damage = other->takeDamage(atk());
    msg << "You did " << damage << " damage to the " << other->name() << " (" << other->currentHP() << " HP).";
    UI::instance()->say(msg.str());
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
