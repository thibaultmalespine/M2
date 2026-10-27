#include <stdio.h>
#include <stdlib.h>

void printBinary(unsigned int n);
void printBinaryRecLauncher(unsigned int n);
void printBinaryRec(unsigned int n, unsigned int p);
void printWhithSpace(char *str);


int main(int argc, char* argv[]){

    

    if ((argc != 2) || (atol(argv[1])) < 0){
        printf("Veuillez entrer un entier positif\n");
        return EXIT_FAILURE;
    }
    

    unsigned int n = atol(argv[1]);
    unsigned int temp = n;

    int buffer_size = 1;
    while (temp > 0){
        temp /= 8;
        buffer_size ++;
    }
    char str_base_8[buffer_size];
    char str_base_16[buffer_size];
    
    sprintf(str_base_8, "%o", n);
    sprintf(str_base_16, "%X", n);
    
    printf("%u en base 8  = ", n);
    printWhithSpace(str_base_8);

    printf("%u en base 16 = ", n);
    printWhithSpace(str_base_16);

    printf("%u en base 2  = ",n);
    printBinary(n);
    /*
    printf("%u en base 2 (récursif) = ",n);
    printBinaryRecLauncher(n);
    */
    return EXIT_SUCCESS;
}

void printBinary(unsigned int n){
    unsigned int p = 1;
    while (p <= (n/2)){
        p *= 2;
    }
    while (p > 0){
        printf("%d ",n/p);
        n = n % p;
        p /= 2;
    }    
    printf("\n");
}

void printBinaryRecLauncher(unsigned int n){
    unsigned int p = 1;
    while (p <= (n/2)) p*=2;
    printBinaryRec(n, p);
    printf("\n");
}


void printBinaryRec(unsigned int n, unsigned int p){
    
    printf("%d ",n/p);
    if (p/2 > 0){
        printBinaryRec(n%p, p/2);
    } 
}

void printWhithSpace(char *str){
    while (*str != '\0')
    {
        printf("%c ", *str);
        str++;
    }
    printf("\n");    
}
