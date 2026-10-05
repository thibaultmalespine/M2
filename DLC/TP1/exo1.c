#include "stdlib.h"
#include "stdio.h"
#include "gmp.h"
#include "time.h"

void seed_gmp_from_urandom(gmp_randstate_t prng, size_t bytes) {
    FILE *f = fopen("/dev/urandom", "rb");
    if (!f) {
        perror("fopen /dev/urandom");
        exit(1);
    }

    unsigned char buffer[bytes];
    if (fread(buffer, 1, bytes, f) != bytes) {
        fclose(f);
        exit(1);
    }
    fclose(f);

    mpz_t seed;
    mpz_init(seed);
    // Importe les octets bruts directement en mpz_t
    mpz_import(seed, bytes, 1, sizeof(buffer[0]), 0, 0, buffer);

    gmp_printf("Seed utilisée : %Zd\n", seed);

    gmp_randseed(prng, seed);
    mpz_clear(seed);
}


int main(int argc, char **argv){

    mpz_t a;
    int k = atoi(argv[1]);
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
        //gmp_printf("nombre généré : %Zd\n", a);
        printf("Nombre généré (binaire) : ");
        mpz_out_str(stdout, 2, a);
        printf("\n");
    } while (mpz_fdiv_ui(a,20) != 0);
    
    
    
    mpz_clear(a);
    gmp_randclear(prng);
    return 0;
}