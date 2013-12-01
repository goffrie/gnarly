#ifndef __ATTRIBUTE_DECORATOR_H__
#define __ATTRIBUTE_DECORATOR_H__

#include "attributeprovider.h"

// A base class for decorators on top of
// AttributeProvider.
class AttributeDecorator : public AttributeProvider {
protected:
    AttributeProvider* base;
public:
    AttributeDecorator(AttributeProvider* b) : base(b) {}
    ~AttributeDecorator() { delete base; }

    // Default is passing everything through as-is.
    virtual int startingHP() const { return base->startingHP(); }
    virtual int startingMP() const { return base->startingMP(); }
    virtual int atk() const { return base->atk(); }
    virtual int def() const { return base->def(); }
    virtual int xp() const { return base->xp(); }
    virtual int droppedGold() const { return base->droppedGold(); }
    virtual char tile() const { return base->tile(); }
    virtual std::string name() const { return base->name(); }

    // Default is remove self
    virtual AttributeProvider* strip(bool force) override;
};

#endif
