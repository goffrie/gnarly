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
    static bool used[6];
private:
    Type type;
public:
    Potion(Type t) : type(t) { }

    virtual void use(Player* target);

    Type getType() const { return type; }
    virtual char tile() const override { return 'P'; }
    virtual std::string basicName() const override;

    virtual void accept(LevelObjectVisitor& v);

    static void resetUsed();
};

#endif
