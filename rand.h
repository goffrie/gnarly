#ifndef __RAND_H__
#define __RAND_H__

#include <stdint.h>

class Rand {
    uint64_t state;
public:
    Rand();

    // Generate a random unsigned 64-bit integer value.
    uint64_t operator()();
    // Generate a random integer in the half-open interval [a, b).
    int operator()(int a, int b);

    // Generate a random floating-point number in [a, b).
    double dbl(double a = 0, double b = 1);
};

extern Rand rnd;

#endif
