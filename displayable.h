#ifndef __DISPLAYABLE_H__
#define __DISPLAYABLE_H__

class Display;
class Surface;

// Represents something that is displayable
class Displayable {
    friend class Display;

    // The parent display. May be null, which indicates that this item is not being displayed.
    Display* disp;
    // This item's z-index. Used by Display.
    int zIndex;

    // Unregisters self from display
    void unregister();
    // Registers self to a display
    void registerDisplay(Display* disp, int z);

protected:
    // protected dtor: should never delete a Displayable through that pointer!
    ~Displayable();
public:
    Displayable();

    // Draw this item on the screen.
    virtual void draw(Surface& target) const = 0;
};

#endif
