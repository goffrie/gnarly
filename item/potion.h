#ifndef __POTION_H__
#define __POTION_H__

#include "item.h"
#include <string>
class Potion : public Item {
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
    virtual std::string basicName() const override;

    virtual char tile() const override { return 'P'; }

    static void resetUsed();
};

#endif
