#ifndef __DISPLAYABLE_H__
#define __DISPLAYABLE_H__

#include "grid.h"

class Display;

class Displayable {
    friend class Display;

    // The parent display. May be null, which indicates that this item is not being displayed.
    Display* disp;
    // This item's z-index. Used by Display.
    int zIndex;

    void unregister();
    void registerDisplay(Display* disp, int z);

protected:
    // protected dtor: should never delete a Displayable through that pointer!
    ~Displayable();
public:
    Displayable();

    // Draw this item on the grid provided.
    virtual void draw(Grid& grid) = 0;
};

#endif
