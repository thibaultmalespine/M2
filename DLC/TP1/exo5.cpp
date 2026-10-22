#include <iostream>
#include <string>
#include <NTL/GF2X.h>
#include <NTL/GF2XFactoring.h>
#include <NTL/GF2E.h>
#include <NTL/mat_GF2E.h>

using namespace std;
using namespace NTL;

int main(int argc, char **argv){
    if (argc != 4){
        cout << "Veuillez entrer m,n et k" << endl;
        cout << "m = degré de l'extension" << endl;
        cout << "n = nombre de colonnes de la matrice" << endl;
        cout << "k = nombre de lignes de la matrice" << endl;
        cout << "Utilisation : ./exo5 m n k" << endl;
    }

    int m = atoi(argv[1]);
    int n = atoi(argv[2]);
    int k = atoi(argv[3]);

    // initialiser le corps GF2^m
    GF2X P = BuildSparseIrred_GF2X(m);
    GF2E::init(P);

    // générer une matrice aléatoire de taille k*n
    mat_GF2E matrice = random_mat_GF2E(k, n);
    cout << "Matrice de taille " << k << " * " << n << ":" << endl;
    cout << matrice << endl;
    cout << endl << endl;

    // générer un vecteur dans GF2^m
    cout << "Vecteur à " << n << " coefficient :" << endl;
    vec_GF2E vecteur = random_vec_GF2E(n);
    cout << vecteur << endl;
    cout << endl << endl;

    // afficher le produit de matrice / vecteur
    vec_GF2E resultat;
    mul(resultat, matrice, vecteur);
    cout << "Résultat du produit matrice . vecteur :" << endl;
    cout << resultat << endl;

    return 0;
    
}