#ifndef __POTIONADAPTER_H__
#define __POTIONADAPTER_H__

#include "itemadapter.h"
#include "item.h"
#include "potion.h"
#include <string>

class PotionAdapter : public ItemAdapter {
public:
    PotionAdapter(Potion* p) : ItemAdapter(p) { }
    virtual char tile() const override { return 'P'; }
};

#endif
