#include "mesinkatainput.h"
#include "mesinkata.h"
#include "point.h"
#include <stdio.h>

int main() {
    //Kamus
    int i, j, k;
    POINT P;
    Kata Kat;

    //Algoritma
    printf("Integer > \n");
    InputInteger(&i);
    printf("Input Integer = %d\n", i);

    printf("Point > \n");
    InputPoint(&P);
    printf("Input Point = ");
    TulisPOINT(P);
    printf("\n");

    printf("Integer > \n");
    InputKata(&Kat);
    for (i = 1; i <= length(Kat); i++) {
        printf("%c", chr(Kat, i));
    }

    return 0;
}