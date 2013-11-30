#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include <map>
#include <stack>

class Player;
class Item;

class Inventory final {
    typedef std::map<char, Item*> invMap;
    invMap items;
    std::stack<char> slots;
public:
    typedef invMap::iterator iterator;
    typedef invMap::const_iterator const_iterator;

    Inventory();
    ~Inventory();

    bool full() const;

    // Add an item to the inventory. Returns 0 if it failed
    // (i.e. the inventory is full).
    // Otherwise, takes ownership of the item, and returns its slot.
    char addItem(Item* i);

    bool useItem(Player& p, char i);
    void view(Player& p);

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
};

#endif
