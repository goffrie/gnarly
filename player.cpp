#include "player.h"

#include "ui.h"
#include "level.h"

Player::~Player() {
}

void Player::reduceHp(int amt) {
    hp -= amt;
    // TODO: notify
}

bool Player::canMove(int nY, int nX) {
    struct IsPassableVisitor : public LevelObjectVisitor {
        bool ans;
        // TODO: when gold is implemented, check for it
        // also staircases
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
}
