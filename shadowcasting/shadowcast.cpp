#include "shadowcast.h"

#include "intervalset.h"
#include <cmath>
#include <cassert>

using namespace std;

// Implements Mingo's Restrictive Precise Angle Shadowcasting, as described in
// http://roguebasin.roguelikedevelopment.org/index.php?title=Restrictive_Precise_Angle_Shadowcasting

// Index into a 2d vector with bounds checking (returns true by default).
bool ix(const vector<vector<bool> >& a, int y, int x) {
    if (y < 0 || y >= (signed)a.size()) return true;
    if (x < 0 || x >= (signed)a[y].size()) return true;
    return a[y][x];
}
// Set an index in a 2d vector with bounds checking.
void setIx(vector<vector<bool> >& a, int y, int x, bool val) {
    if (y < 0 || y >= (signed)a.size()) return;
    if (x < 0 || x >= (signed)a[y].size()) return;
    a[y][x] = val;
}

// Compute one octant of the field of view.
// The octant is determined by the 2x2 matrix
// [ myy  myx ]
// [ mxy  mxx ].
template<int myy, int myx, int mxy, int mxx>
void shadowcastOctant(int y, int x, int radius,
        const vector<vector<bool> >& opaque,
        vector<vector<bool> >& visible,
        vector<int>& covered) {

    const int r2 = radius * radius;

    IntervalSet shadowed;

    for (int dy = 1; dy <= radius; ++dy) {
        shadowed.resolveIntervals(dy * 2 + 2, covered);
        for (int dx = 0; dx <= dy; ++dx) {
            // Limit vision to a circle, not a square.
            if (dx * dx + dy * dy > r2) break;

            const int ny = y + myy * dy + myx * dx;
            const int nx = x + mxy * dy + mxx * dx;
            // If the previous line didn't have the nearby cells visible,
            // don't allow this cell to be visible either.
            // Avoids strange disconnected lit regions.
            if ((dx == dy || (!ix(visible, ny - myy, nx - mxy) || ix(opaque, ny - myy, nx - mxy)))
                && ((dx == 0 || (!ix(visible, ny - myy - myx, nx - mxy - mxx)
                                || ix(opaque, ny - myy - myx, nx - mxy - mxx))))) {
                continue;
            }
            if (ix(opaque, ny, nx)) {
                bool left  = covered[dx*2]   == 0,
                     mid   = covered[dx*2+1] == 0,
                     right = covered[dx*2+2] == 0;
                // Any of the three points are enough to make it visible.
                if (left || mid || right) {
                    setIx(visible, ny, nx, true);
                    shadowed.add(Interval(dx / double(dy + 1), (dx + 1) / double(dy + 1)));
                }
            } else {
                // The centre point must be visible.
                // Being on the boundary of an interval is good enough.
                bool mid   = covered[dx*2+1] <= 1;
                if (mid) {
                    setIx(visible, ny, nx, true);
                }
            }
        }
    }
}


// Compute the field of view around the point (y, x).
void shadowcast(int y, int x, int radius,
        const vector<vector<bool> >& opaque,
        vector<vector<bool> >& visible) {

    const int height = opaque.size();
    assert(height > 0);
    const int width = opaque[0].size();
    assert(width > 0);

    assert(y >= 0 && y < height);
    assert(x >= 0 && x < width);

    // Initialize `visible` to all false.
    visible.assign(height, vector<bool>(width, false));

    // The origin is visible.
    visible[y][x] = true;

    // Initialize the scratch vector.
    // This is shared between `shadowcastOctant` calls.
    vector<int> covered;
    covered.reserve(radius * 2 + 3);

    // Perform the shadowcast.
    shadowcastOctant< 1,  0,  0,  1>(y, x, radius, opaque, visible, covered);
    shadowcastOctant< 1,  0,  0, -1>(y, x, radius, opaque, visible, covered);
    shadowcastOctant<-1,  0,  0, -1>(y, x, radius, opaque, visible, covered);
    shadowcastOctant<-1,  0,  0,  1>(y, x, radius, opaque, visible, covered);
    shadowcastOctant< 0,  1,  1,  0>(y, x, radius, opaque, visible, covered);
    shadowcastOctant< 0,  1, -1,  0>(y, x, radius, opaque, visible, covered);
    shadowcastOctant< 0, -1, -1,  0>(y, x, radius, opaque, visible, covered);
    shadowcastOctant< 0, -1,  1,  0>(y, x, radius, opaque, visible, covered);
}
