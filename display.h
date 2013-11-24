#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <set>
#include "displayable.h"

// Groups Displayables into a single Displayable.
class Display : public Displayable {
    std::set<std::pair<int, Displayable*> > items;
public:
    Display() { }
    ~Display();

    // Add or remove items from the display.
    // Items are sorted by z-index, so those with a higher z-index
    // are displayed on top of those with a lower index.
    void add(Displayable* item, int z = 0);
    void remove(Displayable* item);

    // Draw the display on the given surface.
    void draw(Surface& target) const override;
};

#endif
