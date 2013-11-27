#include "itemadapter.h"
#include "levelobjectvisitor.h"

ItemAdapter::ItemAdapter(Item* i) : item(i) {
}

ItemAdapter::~ItemAdapter() {
    delete item;
}

Item* ItemAdapter::removeItem() {
    Item* i = item;
    item = 0;
    return i;
}

std::string ItemAdapter::basicName() const {
    return item->basicName();
}

std::string ItemAdapter::name(Article a) const {
    return item->name(a);
}

void ItemAdapter::accept(LevelObjectVisitor& v) {
    v.visit(*this);
}
