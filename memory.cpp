#include "memory.h"

#include "ui.h"

using namespace std;

Memory::Memory(int height, int width) : grid(height, string(width, ' ')) {
}

void Memory::set(int y, int x, char c) {
    grid[y][x] = c;
}

void Memory::draw(UI& ui) const {
    ui.setDim();
    for (unsigned int y = 0; y < grid.size(); ++y) {
        ui.draw(y, 0, grid[y]);
    }
    ui.unsetDim();
}