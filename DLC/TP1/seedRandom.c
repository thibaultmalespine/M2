#include "seedRandom.h"
/**
 * @brief Génère une seed de taille variable pour un prng
 * @param[in, out] prng : le prng qui va être seedé
 * @param[in] bytes : le nombre d'octets de la seed
 */
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