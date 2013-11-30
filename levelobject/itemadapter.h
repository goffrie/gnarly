#ifndef __ITEMADAPTER_H__
#define __ITEMADAPTER_H__

#include "levelobject.h"
#include "item.h"

class ItemAdapter : public LevelObject {
    Item* item;
protected:
    virtual std::string basicName() const;

public:
    ItemAdapter(Item* i);
    virtual ~ItemAdapter();
    virtual Item* removeItem();
    virtual std::string name(Article a) const;
    virtual char tile() const override { return item->tile(); }
    virtual void accept(LevelObjectVisitor& v);
};

#endif
