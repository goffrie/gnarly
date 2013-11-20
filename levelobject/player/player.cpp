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
        Game::instance()->playerDied();
    }
}

bool Player::canMove(int nY, int nX) {
    struct IsPassableVisitor : public LevelObjectVisitor {
        bool ans;
        // TODO: when gold is implemented, check for it
        // also staircases
        virtual void visit(Gold& o) {
            ans = true;
        }
    };
    IsPassableVisitor v;
    v.ans = false;
    // Check if there's an object there.
    LevelObject* target = getLevel()->objectAt(nY, nX);
    if (target) {
        target->accept(v);
        if (!v.ans) {
            // It's an impassable object.
            return false;
        }
    }
    // Otherwise, there has to be no terrain in the way.
    Tile t = getLevel()->tileAt(nY, nX);
    return (t == Floor || t == Passage || t == Door);
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

void Player::accept(LevelObjectVisitor& v) {
    v.visit(*this);
}
