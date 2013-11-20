#ifndef __ATTRIBUTE_DECORATOR_H__
#define __ATTRIBUTE_DECORATOR_H__

#include "attributeprovider.h"

// A base class for decorators on top of
// AttributeProvider.
//
class AttributeDecorator : public AttributeProvider {
protected:
    AttributeProvider* base;
public:
    AttributeDecorator(AttributeProvider* b) : base(b) {}
    ~AttributeDecorator() { delete base; }

    // Default to passing everything through as-is.
    virtual int startingHP() const { return base->startingHP(); }
    virtual int atk() const { return base->atk(); }
    virtual int def() const { return base->def(); }
    virtual char tile() const { return base->tile(); }
    virtual std::string race() const { return base->race(); }

    virtual AttributeProvider* strip() override;
};

#endif
