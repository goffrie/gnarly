#ifndef __FIREBALL_H__
#define __FIREBALL_H__

#include "skill.h"

class Fireball : public Skill {
    enum { range = 5 };
public:
    Fireball() : Skill(5) { }
    virtual bool use(Player* p) override;
    virtual std::string name() const override;
    virtual std::string description() const override;
};

#endif
