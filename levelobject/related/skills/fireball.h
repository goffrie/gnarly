#ifndef __FIREBALL_H__
#define __FIREBALL_H__

#include "skill.h"

// A wizard skill that attacks an enemy at range with a fireball
class Fireball : public Skill {
    enum { range = 5 };
public:
    // Manacost: 5
    Fireball() : Skill(5) { }
    // Gets a target and attacks it
    virtual bool use(Player* p);
    virtual std::string name() const;
    virtual std::string description() const;
};

#endif
