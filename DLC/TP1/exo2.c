#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>

#include "seedRandom.h"

/**
 * @brief Génère des nombres pseudo aléatoire de taille k bits.
 * @param[in] k : nombre de bits (argv[1]) 
*/
int main(int argc, char **argv){
    mpz_t n;
    mpz_init(n);
    
    // Nombre de bits du nombre généré
    int k;
    if (argc < 2) {
        printf("Veuillez entrer une valeur pour k.\n");
        exit(0);
    } else {
        k = atoi(argv[1]);
    }

    

    gmp_randstate_t prng;
    gmp_randinit_default(prng); // Choisit un algorithme de génération
    seed_gmp_from_urandom(prng, 32);

    mpz_urandomb(n, prng, k);

    mpz_t a, b;
    mpz_init_set_ui(a, 512);
    mpz_init_set_ui(b, 1023);

    mpz_out_str(stdout, 2, a);
    printf("\n");
    mpz_out_str(stdout, 2, b);
    printf("\n");
    mpz_out_str(stdout, 2, n);
    printf("\n");

    mpz_clear(n);
    mpz_clear(a);
    return 0;
}