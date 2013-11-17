#include "displayable.h"

#include "display.h"

Displayable::Displayable() : disp(0) { }

Displayable::~Displayable() {
    unregister();
}

void Displayable::unregister() {
    if (disp) {
        disp->remove(this);
        disp = 0;
    }
}

void Displayable::registerDisplay(Display* d, int z) {
    unregister();
    disp = d;
    zIndex = z;
}
