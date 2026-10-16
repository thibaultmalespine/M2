#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>
#include <time.h>

#include "seedRandom.h"

int main(int argc, char **argv){

    mpz_t a;
    int k;

    if (argc < 2)
    {
        printf("Veuillez choisir un entier k.\n");
        exit(0);
    } else {
        k = atoi(argv[1]);
    }
    
    gmp_randstate_t prng;
    gmp_randinit_default(prng);
    // gmp_randseed_ui(prng, time(NULL));
    if (argv[2] == NULL)
    {
        // Améliore l'aléatoire
        seed_gmp_from_urandom(prng, 32);
    }
    else{
        mpz_t seed;
        mpz_init(seed);
        mpz_set_ui(seed, atoi(argv[2]));
        gmp_randseed(prng, seed);
        gmp_printf("Seed utilisée : %Zd\n", seed);
        mpz_clear(seed);
    }
    
    mpz_init(a);
    
    do
    {
        mpz_urandomb(a, prng, k);
        gmp_printf("nombre généré : %Zd\n", a);
    } while (mpz_fdiv_ui(a,20) != 0);
    
    
    mpz_clear(a);
    gmp_randclear(prng);
    return 0;
}