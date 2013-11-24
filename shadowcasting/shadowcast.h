#ifndef __SHADOWCAST_H__
#define __SHADOWCAST_H__

#include <vector>

// Compute the field of view around the point (y, x).
// Requires that `opaque` be rectangular, and nonempty in both dimensions.
// Returns (through the `visible` parameter) which squares are visible.
void shadowcast(int y, int x, int radius,
        const std::vector<std::vector<bool> >& opaque,
        std::vector<std::vector<bool> >& visible);

#endif
