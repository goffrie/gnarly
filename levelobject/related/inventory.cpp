#include "inventory.h"
#include "item.h"
#include "ui.h"
#include "inventorypopup.h"

Inventory::~Inventory() {
    for (unsigned int i = 0; i < items.size(); i++) {
        delete items[i];
    }
}

bool Inventory::useItem(Player* p, unsigned int i) {
    if (i >= items.size()) {
        return false;
    }
    items[i]->use(p);
    delete items[i];
    items.erase(items.begin() + i);
    return true;
}

void Inventory::addItem(Item* i) {
    items.push_back(i);
}

void Inventory::view(Player* p) {
    InventoryPopUp::make(p, this);
}

std::vector<Item*> Inventory::getItems() {
    return items;
}
