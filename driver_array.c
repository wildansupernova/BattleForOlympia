#include "array.h"
#include "point.h"
#include <stdio.h>

int main() {
    //Kamus
    TabUnit A;
    unit tUnit;
    POINT ValUndefP;

    //Algoritma
    MakeEmptyArray(&A);

    if (isEmptyAr(A)) {
        printf("Iya\n");
    }

    ValUndefP = MakePOINT(-1, -1);

    jenisUnit(tUnit) = 'A';
    maxH(tUnit) = 35;
    Health(tUnit) = 35;
    Attack(tUnit) = 2;
    maxMove(tUnit) = 2;
    moveP(tUnit) = 2;
    AtkType(tUnit) = 1;
    atkchance(tUnit) = true;
    location(tUnit) = ValUndefP;
    harga(tUnit) = 4;
    selected(tUnit) = true;
    prob(tUnit) = 2;

    AddElmtArray(&A, tUnit);

    PrintArray(A);

    return 0;
}