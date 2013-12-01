#ifndef __ATTRIBUTE_PROVIDER_H__
#define __ATTRIBUTE_PROVIDER_H__

#include <string>

// An abstract class representing a set of attributes.
class AttributeProvider {
public:
    virtual ~AttributeProvider() { }
    virtual int startingHP() const = 0;
    virtual int startingMP() const = 0;
    virtual int atk() const = 0;
    virtual int def() const = 0;
    virtual int xp() const = 0;
    virtual int droppedGold() const = 0;
    virtual char tile() const = 0;
    virtual std::string name() const = 0;
    // Return the concrete (non-decorator) AttributeProvider
    // underlying this object, and delete all the decorators.
    virtual AttributeProvider* strip(bool force) { return this; }
};

#endif
