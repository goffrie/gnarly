#ifndef __ITEMADAPTER_H__
#define __ITEMADAPTER_H__

#include "levelobject.h"
#include "item.h"

// Provides an adapter for an item so it can be placed on a level
class ItemAdapter : public LevelObject {
    Item* item;
protected:
    // Uses item's basicName
    virtual std::string basicName() const;

public:
    ItemAdapter(Item* i);
    virtual ~ItemAdapter();
    // Removes the item from self so is not deleted, and returns it
    virtual Item* removeItem();
    // Uses item's name and tile
    virtual std::string name(Article a) const;
    virtual char tile() const override { return item->tile(); }
    virtual void accept(LevelObjectVisitor& v);
};

#endif
