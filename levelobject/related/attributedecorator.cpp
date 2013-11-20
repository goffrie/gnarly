#include "attributedecorator.h"

AttributeProvider* AttributeDecorator::strip() {
    // This is a decorator, so delete myself
    AttributeProvider* ret = base->strip();
    // Have to avoid deleting `base` itself.
    base = 0;
    delete this;

    return ret;
}

