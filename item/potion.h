#ifndef __POTION_H__
#define __POTION_H__

#include "item.h"
#include <string>

// A potion that can be used by the player. Potions increase/decrease atk/def/hp
class Potion : public Item {
public:
    // The possible types of potions
    enum Type {
        RH = 0,
        PH,
        BA,
        WA,
        BD,
        WD
    };
    enum { numTypes = 6 };
    // Whether or not a player has used a certain type of potion
    static bool used[6];
private:
    Type type;
public:
    Potion(Type t) : type(t) { }

    // Uses the potion, applying a buff or modifying hp or the player
    virtual void use(Player* target);
    virtual std::string basicName() const;

    virtual char tile() const { return 'P'; }

    // Reset the used states of all types to player has not yet used them
    static void resetUsed();
};

#endif
