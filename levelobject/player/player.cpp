#include "player.h"
#include "game.h"

#include "ui.h"
#include "level.h"
#include "levelobjectvisitor.h"
#include "basicbuff.h"
#include "direction.h"
#include "class.h"
#include "commandargs.h"
#include "itemadapter.h"
#include "inventory.h"
#include <sstream>

using namespace std;

Player::Player(Attributes::Race r) : 
Character(r, Players), playerClass(0), _gold(0), _currentXP(0), _targetXP(targetXPForLevel(2)), _xpLevel(1) {
}

Player::~Player() {
    delete playerClass;
}

void Player::reduceHP(int amt) {
    hp -= amt;
    if (hp <= 0) {
        hp = 0;
        Game::instance()->notifyPlayerDeath();
    }
}

bool Player::moveRelative(Direction d) {
    if (LevelObject::moveRelative(d)) {
        playerClass->notifyMove(this);
        ostringstream msg;
        msg << "You move " << d.name();
        vector<LevelObject*> neighbours = getLevel()->neighbours(getY(), getX());
        if (!neighbours.empty()) {
            msg << " and see " << neighbours[0]->name(Indefinite);
            if (neighbours.size() == 2) {
                // You see A and B.
                msg << " and " << neighbours[1]->name(Indefinite);
            } else {
                // You see A, B, and C.
                for (unsigned int i = 1; i < neighbours.size(); i++) {
                    if (i == neighbours.size() - 1) {
                        msg << ", and " << neighbours[i]->name(Indefinite);
                    } else {
                        msg << ", " << neighbours[i]->name(Indefinite);
                    }
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
    msg << "You did " << dmg << " dmg to " << other->name(Definite) << " (" << other->currentHP() << " HP).";
    UI::instance()->say(msg.str());
    if (other->dead()) {
        addGold(other->droppedGold());
        msg.str("");
        msg << "You gained " << other->xp() << " xp!";
        UI::instance()->say(msg.str());
        addXP(other->xp());
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

bool Player::addToInventory(ItemAdapter* i) {
    if (!gnarly) {
        i->removeItem()->use(this);
        delete i;
        return true;
    }
    if (inventory.full()) {
        UI::instance()->say("Your inventory is full.");
        return false;
    }
    Item* item = i->removeItem();
    char r = inventory.addItem(item);
    UI::instance()->say("You pick up " + item->name(Indefinite) + " <" + r + ">.");
    delete i;
    return true;
}

void Player::viewInventory() {
    inventory.view(*this);
}

std::string Player::name(Article a) const {
    switch (a) {
        case Definite:
        case Indefinite:
            return "you";
        default:
            if (playerClass->name() != "") {
                return Character::basicName() + " " + playerClass->name();
            }
            return Character::basicName();
    }
}

void Player::accept(LevelObjectVisitor& v) {
    v.visit(*this);
}

void Player::addXP(int xp) {
    _currentXP += xp;
    if (_currentXP >= _targetXP && gnarly) {
        levelUp();
    }
}

int Player::targetXPForLevel(int l) {
    return (l - 1) * 200;
}

void Player::levelUp() {
    UI::instance()->say("You Leveled Up!");
    attributes = playerClass->getLevelBuff(attributes);
    hp = attributes->startingHP();
    mp = attributes->startingMP();
    _currentXP = 0;
    _xpLevel++;
    _targetXP = targetXPForLevel(_xpLevel + 1);
}
