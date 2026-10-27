#include <stdio.h>
#include <stdlib.h>
#include "salutation.h"


int main(int argc, char *argv[]){


    if (argc != 3)
    {
        printf("Veuillez indiquer votre nom et votre âge!\n");
        printf("Utilisation : ./hello nom age\n");
        return EXIT_FAILURE;
    }
    

    char *nom = argv[1];
    int age = atoi(argv[2]);   

    salut(nom);
    salutMonGrand(nom, age);

    return EXIT_SUCCESS;
}