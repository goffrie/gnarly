#ifndef __INTERVAL_SET_H__
#define __INTERVAL_SET_H__

#include <utility>
#include <vector>
#include <set>

typedef std::pair<double, double> Interval;

// Holds onto a union of closed intervals,
// e.g. [0, 1/3] u [2/3, 1].
class IntervalSet {
private:
    typedef std::set<Interval> ISet;
    ISet intervals;
public:
    void add(Interval i);

    // Queries whether the points (0/n, 1/n, ..., n/n) are in the set,
    // returning them in a vector<int>, where 0 means not in any interval,
    // 1 means on the boundary of an interval,
    // and 2 means within an interval.
    void resolveIntervals(int n, std::vector<int>& v) const;
};

#endif
