#ifndef __INVENTORY_POPUP_H__
#define __INVENTORY_POPUP_H__

#include "popup.h"
#include <string>

class Item;
class Inventory;
class Player;

// A popup specifically for displaying and using items in a inventory
class InventoryPopUp : public PopUp {
protected:
    InventoryPopUp(const std::string& t) : PopUp(t) { }

    // Displays the text for an inventory
    static std::string getText(const Inventory& items);
public:
    // Creates a inventory popup with that displays an inventory and uses items, when corresponding key is pressed
    static void make(Player& p, Inventory& inv);
};

#endif
