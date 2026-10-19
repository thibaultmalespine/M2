#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>
#include <string.h>

#include "seedRandom.h"


void Egal_to_k_bits(mpz_t n, gmp_randstate_t prng,int k);
void Less_or_egal_to_k_decimals(mpz_t n, gmp_randstate_t prng,int k, int isPrint);
void Strictly_egal_to_k_decimals(mpz_t n, gmp_randstate_t prng, int k);

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
    
    // Création d'un générateur aléatoire
    gmp_randstate_t prng;
    gmp_randinit_default(prng); // Choisit un algorithme de génération
    seed_gmp_from_urandom(prng, 32); 


    // Le nombre généré doit être un multiple de 20 pour que le programme s'arrête
    do
    {
        //Egal_to_k_bits(n, prng, k);
        //Less_or_egal_to_k_decimals(n, prng, k,1);
        Strictly_egal_to_k_decimals(n, prng, k);
    } while (mpz_fdiv_ui(n,20));
    

    mpz_clear(n);

    return 0;
}

void Egal_to_k_bits(mpz_t n, gmp_randstate_t prng,int k){

        // La taille du nombre doit être comprise entre 2^(k-1) et (2^k)-1
        unsigned long nbBits = mpz_sizeinbase(n,2);
        nbBits = mpz_sizeinbase(n, 2);

        do {
            mpz_urandomb(n, prng, k);
            nbBits = mpz_sizeinbase(n,2);
        } while (nbBits != k);
        
        mpz_out_str(stdout, 2, n);
        printf("\n");
    
}

void Less_or_egal_to_k_decimals(mpz_t n, gmp_randstate_t prng, int k, int isPrint){
    // Calcul d'un seuil égal à 10^k
    mpz_t seuil, base;
    mpz_inits(seuil, base, NULL);
    mpz_set_ui(base, 10);
    mpz_pow_ui(seuil, base, k);

    // Génère un random entre 0 et le seuil
    mpz_urandomm(n, prng, seuil);

    if (isPrint)
    {
        mpz_out_str(stdout, 10, n);
        printf("\n");
    }
    

    mpz_clears(seuil, base, NULL);
}

void Strictly_egal_to_k_decimals(mpz_t n, gmp_randstate_t prng, int k){
    
    mpz_t nbChiffres;
    mpz_init(nbChiffres);

    char *str;
    do
    {
        Less_or_egal_to_k_decimals(n, prng, k,0);
        str = mpz_get_str(NULL, 10, n);
    } while ( strlen(str) != k);
    
    mpz_out_str(stdout, 10, n); 
    printf("\n");

    mpz_clear(nbChiffres);
}