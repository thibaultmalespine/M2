#include <iostream>
#include <NTL/GF2X.h>
#include <NTL/GF2E.h>

using namespace std;
using namespace NTL;

int main(void) {
    GF2X P;
    SetCoeff(P, 8, 1);
    SetCoeff(P, 4, 1);
    SetCoeff(P, 3, 1);
    SetCoeff(P, 1, 1);
    SetCoeff(P, 0, 1);

    //On construit le corps
    GF2E::init(P);

    GF2E A, B;
    random(A);
    random(B);

    cout << "A = " << A << endl;
    cout << "B = " << B << endl;
    cout << "A + B = " << A + B << endl;
    cout << "A * B = " << A * B << endl;
}