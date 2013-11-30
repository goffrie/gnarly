#ifndef __ITEM_H__
#define __ITEM_H__

#include "object.h"

class Player;

class Item : public Object {
public:
    virtual ~Item() { }
    virtual void use(Player* p) = 0;
    virtual char tile() const = 0;
};

#endif
