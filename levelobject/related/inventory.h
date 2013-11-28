#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include <vector>

class Player;
class Item;

class Inventory {
    enum { maxInventory = 15 };
    std::vector<Item*> items;


public:
    virtual ~Inventory();
    virtual void addItem(Item* i);
    virtual bool useItem(Player* p, unsigned int i);
    virtual std::vector<Item*> getItems();
    virtual void view(Player* p);
};

#endif
