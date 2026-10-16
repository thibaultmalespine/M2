#ifndef seedRandom
#define seedRandom

#include "stdlib.h"
#include "stdio.h"
#include "gmp.h"

void seed_gmp_from_urandom(gmp_randstate_t prng, size_t bytes);

#endif