#ifndef __MEMORY_H__
#define __MEMORY_H__

#include "displayable.h"
#include "surface.h"
#include <vector>
#include <string>

// A class representing the player's "memory": how the grid looked, the last time it was seen.
class Memory : public Displayable, public Surface {
    std::vector<std::string> grid;
public:
    Memory(int height, int width);

    // Implement `Displayable`.
    virtual void draw(Surface& target) const;

    // Implement `Surface`.
    virtual void draw(int y, int x, char c);
};

#endif
