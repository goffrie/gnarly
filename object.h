#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <string>
#include "language.h"

class ItemAdapter;

// An abstract class representing any physical thing in the game
class Object {
protected:
    friend class ItemAdapter;
    // Returns a basic name
    virtual std::string basicName() const = 0;
public:
    // Return a name for the object with the given parameters.
    // By default, constructs something using basicName.
    virtual std::string name(Article a) const;
};

#endif
