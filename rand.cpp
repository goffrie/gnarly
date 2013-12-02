#include "rand.h"

#include <ctime>
#include <cassert>
#include <iostream>

Rand rnd;


// Implements the Xorshift RNG as decribed by George Marsaglia.

Rand::Rand() : state(88172645463325252ull) {
    state ^= time(0);
}

uint64_t Rand::operator()() {
    state ^= state << 13;
    state ^= state >> 7;
    state ^= state << 17;
    return state;
}

int Rand::operator()(int a, int b) {
    assert(b > a);
    return static_cast<int>((*this)() % ((uint64_t) (b - a))) + a;
}

double Rand::dbl(double a, double b) {
    const double r = (*this)() / 18446744073709551616.0;
    return r * (b - a) + a;
}
