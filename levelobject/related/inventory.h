#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include <map>
#include <stack>

class Player;
class Item;

// A class representing an inventory with items. Belongs to the player
class Inventory final {
    typedef std::map<char, Item*> invMap;
    // The items in the inventory, indexed by chars
    invMap items;
    // The possible chars to put index by
    std::stack<char> slots;
public:
    typedef invMap::iterator iterator;
    typedef invMap::const_iterator const_iterator;

    Inventory();
    ~Inventory();

    // Returns true if the inventory is full
    bool full() const;

    // Add an item to the inventory. Returns 0 if it failed
    // (i.e. the inventory is full).
    // Otherwise, takes ownership of the item, and returns its slot.
    char addItem(Item* i);

    // Uses an item on a player
    bool useItem(Player& p, char i);
    // Views the inventory, creating a popup window
    void view(Player& p);

    // Returns the iterators for the items in the inventory
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
};

#endif
