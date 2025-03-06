#ifndef MERSENNE_RNG
#define MERSENNE_RNG

#include <random>
#include <ctime>

using namespace std;

class Mersenne_rng {
private:
    mt19937 mt_rand;

public:
    Mersenne_rng();

    void seed(int seed);

    unsigned int next32();

    int next31();

    int next(int bound);

    double nextClosed();

    double nextHalfOpen();

    double nextOpen();
};

#endif
