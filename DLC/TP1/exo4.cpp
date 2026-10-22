#include <iostream>
#include <random>
#include <chrono>

#include <stdlib.h>
#include <stdint.h>

#include <NTL/GF2X.h>
#include <NTL/GF2E.h>

using namespace NTL;
using namespace std;

typedef uint8_t gf256_t;

#define NB_ELEMENT 200000

// Implémentation manuelle
gf256_t generateElement(void);
gf256_t addition(gf256_t a, gf256_t b);
gf256_t multiplication(gf256_t a, gf256_t b);
gf256_t inverse(gf256_t a);
gf256_t square(gf256_t a);    
//NTL
void Generate_GF256();
GF2E fromByte(uint8_t b);
gf256_t GF2E_to_gf256(GF2E a);


int main(int argc, char **argv){
    cout << "Nombre d'éléments : " << NB_ELEMENT << endl;

    /********************** Initilisation **********************/
    Generate_GF256();   

    gf256_t gf256[NB_ELEMENT] = {0};
    GF2E gf2e[NB_ELEMENT];
    gf256_t addition_manuelle[NB_ELEMENT-1] = {0};
    GF2E addition_ntl[NB_ELEMENT-1];
    gf256_t multiplication_manuelle[NB_ELEMENT-1] = {0};
    GF2E multiplication_ntl[NB_ELEMENT-1];
    gf256_t inverse_manuelle[NB_ELEMENT] = {0};
    GF2E inverse_ntl[NB_ELEMENT];

    for (int i = 0; i < NB_ELEMENT; i++)
    {
        gf256[i] = generateElement();
        gf2e[i] = fromByte(gf256[i]);
    }
    

    /********************** Addition **********************/

    // manuelle
    
    auto debut = std::chrono::steady_clock::now();

    for (int i = 0; i < NB_ELEMENT - 1; i++){
        addition_manuelle[i] = addition(gf256[i], gf256[i+1]);
    }

    auto fin = std::chrono::steady_clock::now();
    auto duree_us = std::chrono::duration_cast<std::chrono::microseconds>(fin - debut).count();
    std::cout << "Temps addition manuelle : " << duree_us << " µs\n";

    // ntl

    debut = std::chrono::steady_clock::now();

    for (int i = 0; i < NB_ELEMENT - 1; i++){
        addition_ntl[i] = gf2e[i] + gf2e[i+1];
    }

    fin = std::chrono::steady_clock::now();
    duree_us = std::chrono::duration_cast<std::chrono::microseconds>(fin - debut).count();
    std::cout << "Temps addition ntl : " << duree_us << " µs\n";

    /********************** Multiplication **********************/
    // manuelle
    debut = std::chrono::steady_clock::now();
    for (int i = 0; i < NB_ELEMENT - 1; i++){
        addition_manuelle[i] = multiplication(gf256[i], gf256[i+1]);
    }
    fin = std::chrono::steady_clock::now();
    duree_us = std::chrono::duration_cast<std::chrono::microseconds>(fin - debut).count();
    std::cout << "Temps multiplication manuelle : " << duree_us << " µs\n";

    // ntl
    debut = std::chrono::steady_clock::now();
    for (int i = 0; i < NB_ELEMENT - 1; i++){
        addition_ntl[i] = gf2e[i] * gf2e[i+1];
    }
    fin = std::chrono::steady_clock::now();
    duree_us = std::chrono::duration_cast<std::chrono::microseconds>(fin - debut).count();
    std::cout << "Temps multiplication ntl : " << duree_us << " µs\n";


    /********************** Inverse **********************/
    // manuelle
    debut = std::chrono::steady_clock::now();
    for (int i = 0; i < NB_ELEMENT; i++){
        inverse_manuelle[i] = inverse(gf256[i]);
    }
    fin = std::chrono::steady_clock::now();
    duree_us = std::chrono::duration_cast<std::chrono::microseconds>(fin - debut).count();
    std::cout << "Temps inverse manuelle : " << duree_us << " µs\n";

    // ntl
    debut = std::chrono::steady_clock::now();
    for (int i = 0; i < NB_ELEMENT; i++){
        inverse_ntl[i] = inv(gf2e[i]);
    }
    fin = std::chrono::steady_clock::now();
    duree_us = std::chrono::duration_cast<std::chrono::microseconds>(fin - debut).count();
    std::cout << "Temps inverse ntl : " << duree_us << " µs\n";
    
    /********************** Vérifier les valeurs **********************/
    for (int i = 0; i < NB_ELEMENT-1; i++){
        gf256_t ntl_add = GF2E_to_gf256(addition_ntl[i]);
        if (addition_manuelle[i] != ntl_add){
            printf("Erreur addition à l'indice %d : %X différent de %X !", i, addition_manuelle[i], ntl_add);
            exit(-1);
        }
        gf256_t ntl_mul = GF2E_to_gf256(multiplication_ntl[i]);
        if (multiplication_manuelle[i] != ntl_mul){
            printf("Erreur multiplication à l'indice %d : %X différent de %X !", i, multiplication_manuelle[i], ntl_mul);
            exit(-1);
        }
    }

    for (int i = 0; i < NB_ELEMENT-1; i++){
        gf256_t ntl_inv = GF2E_to_gf256(inverse_ntl[i]);
        if (inverse_manuelle[i] != ntl_inv){
            printf("Erreur inverse à l'indice %d : %X différent de %X !", i, inverse_manuelle[i], ntl_inv);
        }
    }

    printf("Tous les résultats sont identiques entre l'implémentation manuelle et NTL !\n");
    return 0;
}

/* ------------------------------- IMPLEMENTATION MANUELLE ----------------------------- */

/**
 * @brief Produit une séquence aléatoire de 8bits et retourne un gf256_t
 */
gf256_t generateElement(void){
    random_device rd;
    mt19937 gen(rd());

    gf256_t res = 0b00000000;
    while (res == 0b00000000){
        for (uint8_t i = 0; i < 7; i++){
            res |= (gen() & 1);
            res <<= 1;
        }
    }

    return res;
}

gf256_t addition(gf256_t a, gf256_t b){
    return a^b;
}

gf256_t multiplication(gf256_t a, gf256_t b){
    gf256_t res = 0;
    
    for (uint8_t i = 0; i < 8; i++){
        if ((b >> i) & 1){
            // Ajouter a à res
            res = addition(res, a);
        }

        // Vérifier le bit de poids fort de a
        uint8_t bit_de_poids_fort = a & 0b10000000;

        // On multiplie a par 2
        a <<= 1; 

        if (bit_de_poids_fort){
            // On applique la réduction mod 27 (cf le document du NIST sur l'AES, partie multiplication in GF(256))
            a ^= 0x1B;
        }    
    }
    return res;
}

gf256_t inverse(gf256_t a){

    // Square and multiply de gauche à droite
    gf256_t res = a;
    gf256_t b254 = 0b11111110;
    for (int8_t i = 6; i >= 0; i--){
        res = square(res);
        if ((b254>>i)&1){
            res = multiplication(res, a);
        }
    }

    return res;
}

gf256_t square(gf256_t a){
    uint16_t res = 0, temp = 0;
    // Décalage des bits (bi --> b2i)
    for(int8_t i = 7; i >= 0; i--){
        if((a>>i)&1){
            temp = 1;
            temp <<= 2*i;
            res ^= temp;
        }
    }

    // Modulo 0x11B
    uint16_t p = 0x11B;
    for(uint8_t i = 14; i >= 8; i--){
        if ((res >> i) & 1){
            res ^= (p << i-8);
        }
        
    }

    return res;
};

/* ------------------------------- VERIFICATION AVEC NTL ----------------------------- */


/**
 * @brief Génère le corps de galois GF256
 */
void Generate_GF256(){
    GF2X P;
    SetCoeff(P, 0);
    SetCoeff(P, 1);
    SetCoeff(P, 3);
    SetCoeff(P, 4);
    SetCoeff(P, 8);

    GF2E::init(P);
}

/**
 * @brief Retourne un GF2E à partir d'un octet
 */
GF2E fromByte(uint8_t b) {
    GF2X f;
    for (uint8_t i = 0; i < 8; i++)
        if ((b >> i) & 1) SetCoeff(f, i);
    return conv<GF2E>(f);
}


gf256_t GF2E_to_gf256(GF2E a){
    GF2X b;
    conv(b,a);
    unsigned char byte;
    BytesFromGF2X(&byte, b, 1);
    uint8_t res = 0, temp = 0;

    for (uint8_t i = 0; i < 8; i++){
        temp = (byte & 1) * pow(2, i);
        res += temp;
        byte >>= 1;
        
    }
    return res;  
}