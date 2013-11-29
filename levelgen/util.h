#ifndef __LEVELGEN_UTIL_H__
#define __LEVELGEN_UTIL_H__

#include <vector>

template<typename T>
void rect(std::vector<std::vector<T> >& map, int y0, int x0, int h, int w, T fill) {
    for (int y = y0; y < y0 + h; ++y) {
        for (int x = x0; x < x0 + w; ++x) {
            map[y][x] = fill;
        }
    }
}

#endif
