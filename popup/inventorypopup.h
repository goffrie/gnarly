#ifndef __INVENTORYPOPUP_H__
#define __INVENTORYPOPUP_H__

#include "popup.h"

class InventoryPopUp : public PopUp {
protected:
    InventoryPopUp(const std::string& t) : PopUp(t) { }

public:
    virtual ~InventoryPopUp() { }
    static void make(Player* p, Inventory* inv);
};

#endif
