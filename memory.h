#ifndef __MEMORY_H__
#define __MEMORY_H__

#include "displayable.h"
#include <vector>
#include <string>

// A class representing the player's "memory": how the grid looked, the last time it was seen.
class Memory : public Displayable {
    std::vector<std::string> grid;
public:
    Memory(int height, int width);
    void set(int y, int x, char c);
    virtual void draw(Surface& target) const override;
};

#endif
