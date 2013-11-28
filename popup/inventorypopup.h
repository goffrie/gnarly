#ifndef __INVENTORYPOPUP_H__
#define __INVENTORYPOPUP_H__

#include "popup.h"
#include <vector>
#include <string>

class Item;

class InventoryPopUp : public PopUp {
protected:
    InventoryPopUp(const std::string& t) : PopUp(t) { }

    static std::string getText(std::vector<Item*> items);
public:
    virtual ~InventoryPopUp() { }
    static void make(Player* p, Inventory* inv);
};

#endif
