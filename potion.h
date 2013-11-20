#ifndef __POTION_H__
#define __POTION_H__

#include "levelobject.h"
#include <string>

class Player;

// XXX: Maybe have a UsableObject class, if we want more usables?
class Potion : public LevelObject {
public:
    enum Type {
        RH = 0,
        PH,
        BA,
        WA,
        BD,
        WD
    };
    enum { numTypes = 6 };
private:
    Type type;
public:
    Potion(Type t) : type(t) { }

    virtual void use(Player* target);

    Type getType() const { return type; }
    // TODO: change to P after dev
    virtual char tile() const override { return '!'; }

    virtual void accept(LevelObjectVisitor& v);

    static std::string name(Type t);
};

#endif
