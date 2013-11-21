#ifndef __SHADOWCAST_H__
#define __SHADOWCAST_H__

#include <cmath>
#include <vector>

#include "intervalset.h"

// Implements Mingo's Restrictive Precise Angle Shadowcasting, as described in
// http://roguebasin.roguelikedevelopment.org/index.php?title=Restrictive_Precise_Angle_Shadowcasting

// Compute one octant of the field of view.
// The octant is determined by the 2x2 matrix [[ myy, myx ], [ mxy, mxx ]].
template<int myy, int myx, int mxy, int mxx, typename D, typename F>
void shadowcastOctant(int y, int x, int radius, D isOpaque, F markVisible, std::vector<bool>& covered) {
    const int r2 = radius * radius;

    IntervalSet shadowed;

    for (int dy = 1; dy <= radius; ++dy) {
        shadowed.resolveIntervals(dy * 2 + 2, covered);
        for (int dx = 0; dx <= dy; ++dx) {
            // Limit vision to a circle, not a square.
            if (dx * dx + dy * dy > r2) break;

            const int ny = y + myy * dy + myx * dx;
            const int nx = x + mxy * dy + mxx * dx;
            if (isOpaque(ny, nx)) {
                // Any of the three points are enough to make it visible.
                if (!covered[dx*2] || !covered[dx*2+1] || !covered[dx*2+2]) {
                    markVisible(ny, nx);
                }
                shadowed.add(Interval(dx / double(dy + 1), (dx + 1) / double(dy + 1)));
            } else {
                // The centre point and one corner must be visible.
                if (!covered[dx*2+1] && (!covered[dx*2] || !covered[dx*2+2])) {
                    markVisible(ny, nx);
                }
            }
        }
    }
}

// Compute the field of view around the point (y, x).
// Takes `bool isOpaque(int y, int x)`, `void markVisible(int y, int x)`,
// which may be function objects.
// Beware: `markVisible` may be called multiple times for the same cell.
template<typename D, typename F>
void shadowcast(int y, int x, int radius, D isOpaque, F markVisible) {
    using namespace std;

    markVisible(y, x);

    std::vector<bool> covered;
    covered.reserve(radius * 2 + 3);

    shadowcastOctant<1, 0, 0, 1>(y, x, radius, isOpaque, markVisible, covered);
    shadowcastOctant<1, 0, 0, -1>(y, x, radius, isOpaque, markVisible, covered);
    shadowcastOctant<-1, 0, 0, -1>(y, x, radius, isOpaque, markVisible, covered);
    shadowcastOctant<-1, 0, 0, 1>(y, x, radius, isOpaque, markVisible, covered);
    shadowcastOctant<0, 1, 1, 0>(y, x, radius, isOpaque, markVisible, covered);
    shadowcastOctant<0, 1, -1, 0>(y, x, radius, isOpaque, markVisible, covered);
    shadowcastOctant<0, -1, -1, 0>(y, x, radius, isOpaque, markVisible, covered);
    shadowcastOctant<0, -1, 1, 0>(y, x, radius, isOpaque, markVisible, covered);
}

#endif
