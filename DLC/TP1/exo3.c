#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

 
void Square_and_multiply_left_to_right(mpz_t res,mpz_t d, mpz_t n, mpz_t c);

/**
 * @brief Décrypte un message chiffré c avec une clé rsa à l'aide de l'algo square and multiply (gauche --> droite)
*/
int main(int argc, char **argv){

    mpz_t n,d,c,m,res;
    mpz_inits(n,d,c,m,res,NULL);

    mpz_set_str(n, "ae828886a1990cde8d02955ba7ca8ee6f572d6030f947aa26d4643e5f00e824bbc7b962904f04ab5bb4682f661c2b8b86bd2c0c04b4de86aac8b9f5086e253e5d1297ece80a4d5b5b3d5f82d8ba878dc031e1a19b6af1aa3ac29c5a8df46cb3743f866311e1df3be3d62d6395633c900c7ac5138d34c825b8f37fbf70842879d", 16);
    mpz_set_str(d, "4c2500d55de59e4bed5357406af263703b612428a9bfabd2fbc351151fadf5047ef59e0bbfefe9696a91d5cb13d5172cc13f708377584335689c73a37b777e0b6c524c4a9ab7e4b78e67ee9ffd3acdb1d6dfda7c42db40eebb0901a74cf2508e5316d9227b1c09dd798f52fd335185e0958fb36271c13260a2650e3b074a5e31", 16);
    mpz_set_str(c, "96794d4b033ad45cd2b27e199aa27de76801ab04dff67cd1afd79ebd349744ff2a0b0afa2b4fb8f556a8e52d5d0c53536481bc4daf8453c9adcd473e8d9f1a74afdc6901dbce1c7b123d41e6eaf23125ccfe07da3aa69ef25794ad8779f21d605af85571f8e0dcd7b9c43d0b9033fd2c8aa01b7846010ca6985f7491db2ee9db", 16);
    mpz_set_str(m, "4548a949e5207233e8b1fc88e896d9da2bbf5d8948338db6dd332c0ebf01ad1d34d61d6f148ea87e8e1d7f3d97645739db6489ef22272312f155255939d92e25a9da580a16109ecc4c69d0442f68394dc9a37fe8186c574859a3048970299e12db743025802c46b8a583b8f5b9c9dd5db95c8b583cf039c34e89f206abc82775", 16);
    
    /* Rappel RSA m = c^d mod(n) */
    Square_and_multiply_left_to_right(res, d, n, c);

    // Comparer le déchiffré res avec le message initial m
    if(mpz_cmp(res, m) == 0){
        printf("L'algo de déchiffrement fonctionne !\n");
    }

    mpz_clears(n,d,c,m,res,NULL);
    return 0;
}

void Square_and_multiply_left_to_right(mpz_t res,mpz_t d, mpz_t n, mpz_t c ){
    
    mpz_set_ui(res, 1);
    char *d_binaire = mpz_get_str(NULL, 2, d); 
    
    while (*d_binaire != '\0')
    {
        mpz_powm_ui(res, res, 2, n);
        if (*d_binaire == '1')
        {
            mpz_mul(res, res, c);
            mpz_mod(res, res, n);
        }
        
        d_binaire++;
    }
}
