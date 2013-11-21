#include "intervalset.h"

#include <algorithm>

using namespace std;

// Merge two overlapping intervals.
inline Interval merge(Interval a, Interval b) {
    return Interval(min(a.first, b.first), max(a.second, b.second));
}

void IntervalSet::add(Interval i) {
    typedef ISet::iterator It;
    // Add the interval.
    It p = intervals.insert(i).first;
    // Merge the interval with overlapping (adjacent) intervals, if necessary.
    bool merged;
    do {
        merged = false;
        // merge left
        while (p != intervals.begin()) {
            It q = p;
            --q;
            if (q->second >= p->first) {
                merged = true;
                Interval m = merge(*p, *q);
                intervals.erase(p);
                intervals.erase(q);
                p = intervals.insert(m).first;
            } else break;
        }
        // merge right
        while (1) {
            It q = p;
            ++q;
            if (q == intervals.end()) break;
            if (q->first <= p->second) {
                merged = true;
                Interval m = merge(*p, *q);
                intervals.erase(p);
                intervals.erase(q);
                p = intervals.insert(m).first;
            } else break;
        }
    } while (merged);
}

// Queries whether the points (0/n, 1/n, ..., n/n) are in the set,
// returning them in a vector<bool>.
void IntervalSet::resolveIntervals(int n, vector<bool>& v) const {
    v.assign(n + 1, false);
    for (ISet::const_iterator p = intervals.begin(); p != intervals.end(); ++p) {
        // Mark the points overlapping this interval.
        int begin = ceil(p->first * n);
        int end = floor(p->second * n);
        // Clamp values to be within the vector's range.
        if (begin < 0) begin = 0;
        if (end > n) end = n;
        fill(v.begin() + begin, v.begin() + end + 1, true);
    }
}
