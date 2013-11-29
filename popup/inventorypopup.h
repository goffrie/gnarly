#ifndef __INVENTORY_POPUP_H__
#define __INVENTORY_POPUP_H__

#include "popup.h"
#include <string>

class Item;
class Inventory;
class Player;

class InventoryPopUp : public PopUp {
protected:
    InventoryPopUp(const std::string& t) : PopUp(t) { }

    static std::string getText(const Inventory& items);
public:
    static void make(Player& p, Inventory& inv);
};

#endif
