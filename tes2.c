#include <stdio.h>
#include "mesinkarinput.h"
#include "mesinkatainput.h"
#include "mesinkar.h"
#include "mesinkata.h"
#include "point.h"

int main() {
    //Kamus
    int i;
    POINT P;
    char lala[20];
    //Algoritma
    // scanf("%s", &lala);
    // if (lala[2] == NILL) {
    //     printf("YES");
    // }

    // Kata K;
    // chr(K, 1) = '1';
    // chr(K, 2) = '2';
    // length(K) = 2;
    
    // printf("%d", chr(K, 1) - '0');

    // int i = 1, sum = 0;

    //Algoritma
    // if (chr(K, i) == '-') {
    //     i++;
    // }
    // printf("Lala");
    // printf("%d", length(K));
    // while (i <= length(K)) {
    //     sum = sum * 10 + chr(K, i) - '0';
    // }
    
    
    // if (chr(K, 1) == '-') {
    //     sum = -1 * sum;
    // }

    // printf("%d", sum);
    
    InputInteger(&i);

    printf("%d", i);

    InputPoint(&P);

    TulisPOINT(P);

    return 0;
}