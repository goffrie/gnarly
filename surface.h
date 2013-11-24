#ifndef __SURFACE_H__
#define __SURFACE_H__

#include <string>

// An abstract class representing a drawing surface.
class Surface {
public:
    virtual ~Surface() { }

    virtual void setColor(int foreground, int background) { }
    virtual void unsetColor(int foreground, int background) { }
    virtual void setDim() { }
    virtual void unsetDim() { }
    // Draw a tile at the given location.
    virtual void draw(int y, int x, char c) = 0;
    // Or a string.
    virtual void draw(int y, int x, const std::string& c) = 0;
    // Fill a whole line with a string.
    // This clears the rest of the line.
    virtual void fillLine(int y, const std::string& str) = 0;

    // Move the cursor here, if possible.
    virtual void cursor(int y, int x) { }

    // Refreshes the display (by reprinting or curses)
    virtual void redraw() = 0;
};

#endif
