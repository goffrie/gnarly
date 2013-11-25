#include "player.h"
#include "game.h"

#include "ui.h"
#include "level.h"
#include "levelobjectvisitor.h"
#include "basicbuff.h"
#include "direction.h"
#include "class.h"
#include <sstream>

using namespace std;

Player::Player(Attributes::Race r) : Character(r, Players), playerClass(0), _gold(0) {
}

Player::~Player() {
    delete playerClass;
}

void Player::reduceHP(int amt) {
    hp -= amt;
    if (hp <= 0) {
        Game::instance()->notifyPlayerDeath();
    }
}

bool Player::moveRelative(Direction d) {
    if (LevelObject::moveRelative(d)) {
        playerClass->notifyMove(this);
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

void Player::damage(Character* other, int d) {
    if (other->dead()) {
        return UI::instance()->say("Target is already dead.");
    }
    playerClass->notifyAttack(this);
    ostringstream msg;
    int dmg = other->takeDamage(d);
    msg << "You did " << dmg << " dmg to the " << other->name() << " (" << other->currentHP() << " HP).";
    UI::instance()->say(msg.str());
    if (other->dead()) {
        addGold(other->droppedGold());
    }
}

void Player::attack(Character* other) {
    Player::damage(other, atk());
}

void Player::heal(int amt) {
    if (amt > 0) {
        addHP(amt);
    } else {
        reduceHP(-amt);
    }
}

void Player::applyBuff(int a, int d) {
    attributes = new BasicBuff(attributes, a, d);
}

void Player::addGold(int amt) {
    _gold += amt;
}

void Player::stripBuffs() {
    attributes = attributes->strip(false);
}

bool Player::canMove(int nY, int nX) {
    return getLevel()->valid(nY, nX) && getLevel()->free(nY, nX, true);
}

void Player::step() {
    Character::step();
    playerClass->step(this);
}

bool Player::useSkill(int i) {
    return playerClass->useSkill(i, this);
    return false;
}

void Player::setClass(Class* c) {
    attributes = attributes->strip(true);
    playerClass = c;
    if (playerClass) {
        attributes = playerClass->getClassBuff(attributes);
        hp = attributes->startingHP();
        mp = attributes->startingMP();
    }
}

void Player::drawClass(Surface& target) const {
    playerClass->draw(target);
}

std::string Player::name() const {
    if (playerClass->name() != "") {
        return Character::name() + " " + playerClass->name();
    }
    return Character::name();
}

void Player::accept(LevelObjectVisitor& v) {
    v.visit(*this);
}
