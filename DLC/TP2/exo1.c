#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#include "seedRandom.h"

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        printf("Veuillez entrer k et e\nk = nombres de bits de la clé RSA générée\ne = exposant public du module\n");
        exit(EXIT_FAILURE);
    }
    

    int k = atoi(argv[1]);

    mpz_t n, phi_n, p, q, e, d;
    mpz_inits(n,phi_n,p,q,e,d, NULL);
    mpz_set_ui(e, atoi(argv[2]));
    // Création d'un prng
    gmp_randstate_t prng;
    gmp_randinit_default(prng); // Choix de l'algo aléatoire 
    seed_gmp_from_urandom(prng, 32); 


    // Génération de p, premier de taille k/2 bits
    size_t nbBits = 0;
    mpz_t gcd;
    mpz_init_set_ui(gcd, 0);
    do {
        mpz_urandomb(p, prng, k/2);
        mpz_nextprime(p, p);
        nbBits = mpz_sizeinbase(p,2);
        mpz_gcd(gcd, p, e);
    } while ((nbBits != k/2) || (mpz_cmp_ui(gcd, 1) != 0));


    // Génération de q, premier de taille k/2 bits
    nbBits = 0;
    mpz_set_ui(gcd, 0);
    do {
        mpz_urandomb(q, prng, k/2);
        mpz_nextprime(q, q);
        nbBits = mpz_sizeinbase(q,2);
        mpz_gcd(gcd, q, e);
    } while ((nbBits != k/2) || (mpz_cmp_ui(gcd, 1) != 0));
    
    mpz_clear(gcd);

    // Calcul n = pq
    mpz_mul(n, p, q);

    // Calcul phi(n)
    mpz_t p_moins_1, q_moins_1;
    mpz_inits(p_moins_1, q_moins_1, NULL);
    mpz_sub_ui(p_moins_1, p, 1);
    mpz_sub_ui(q_moins_1, q, 1);
    mpz_mul(phi_n, p_moins_1, q_moins_1);

    mpz_clears(p_moins_1, q_moins_1, NULL);

    // Calcul d
    mpz_invert(d, e, n);

    // Affichage 
    gmp_printf("e = 0x%Zx\n\n", e);
    gmp_printf("n = 0x%Zx\n\n", n);
    gmp_printf("d = 0x%Zx\n\n", d);


    mpz_clears(n,phi_n,p,q,e,d,NULL);

    return EXIT_SUCCESS;
}
