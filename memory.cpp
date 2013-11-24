#include "memory.h"

#include "surface.h"

using namespace std;

Memory::Memory(int height, int width) : grid(height, string(width, ' ')) {
}

void Memory::draw(Surface& target) const {
    target.setDim();
    for (unsigned int y = 0; y < grid.size(); ++y) {
        target.draw(y, 0, grid[y]);
    }
    target.unsetDim();
}

void Memory::draw(int y, int x, char c) {
    grid[y][x] = c;
}
