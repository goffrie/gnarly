#ifndef __DAMAGE_H__
#define __DAMAGE_H__

class Character;
// A class representing damage to be applied to a Character.
class Damage {
    friend class Character;
    int amt;
    Character& target;
    Damage(int a, Character& target) : amt(a), target(target) { }
public:
    int getAmount() { return amt; }
    // Apply this damage. This Damage object should no longer be used.
    void apply();
};

#endif
