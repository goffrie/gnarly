#ifndef __ITEM_H__
#define __ITEM_H__

#include "object.h"

class Player;

// An abstract class representing an item. Items can go inside an inventory
class Item : public Object {
public:
    virtual ~Item() { }
    // Use the item
    virtual void use(Player* p) = 0;
    // The tile associated with the item
    virtual char tile() const = 0;
};

#endif
