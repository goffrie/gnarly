#ifndef __SURFACE_H__
#define __SURFACE_H__

#include <string>

// An abstract class representing a drawing surface.
class Surface {
public:
    virtual ~Surface() { }

    // Sets the color for future drawing, or does nothing if not possible
    virtual void setColor(int foreground, int background) { }
    // Unsets drawing color (note: must be the same as what was set)
    virtual void unsetColor(int foreground, int background) { }
    // Dims future drawing, or does nothing if not possible
    virtual void setDim() { }
    // Undims drawing
    virtual void unsetDim() { }
    // Draw a tile at the given location.
    virtual void draw(int y, int x, char c) = 0;
    // Or a string.
    virtual void draw(int y, int x, const std::string& c);
    // Fill a whole line with a string.
    // This clears the rest of the line.
    virtual void fillLine(int y, const std::string& str);

    // Move the cursor here, if possible.
    virtual void cursor(int y, int x) { }
};

#endif
