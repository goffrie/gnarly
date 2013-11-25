#include "attributedecorator.h"

AttributeProvider* AttributeDecorator::strip(bool force) {
    // This is a decorator, so delete myself
    AttributeProvider* ret = base->strip(force);
    // Have to avoid deleting `base` itself.
    base = 0;
    delete this;

    return ret;
}

