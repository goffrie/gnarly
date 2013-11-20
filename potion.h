#ifndef __POTION_H__
#define __POTION_H__

#include "levelobject.h"

class Player;

// XXX: Maybe have a UsableObject class, if we want more usables?
class Potion : public LevelObject {
public:
    enum Type {
        RH,
        PH,
        BA,
        WA,
        BD,
        WD
    };
    Type type;

    Potion(Type t) : type(t) { }

    virtual void use(Player* target);

    virtual void accept(LevelObjectVisitor& v);
};

#endif
