#include "mesinkar.h"
#include "mesinkata.h"
#include <stdio.h>

int main() {
    //Kamus
    char NamaFile[50];
    int i;
    Kata tKata;

    //Algoritma
    fgets(NamaFile, 49, stdin);
    for (i = 0; NamaFile[i] != '\n'; i++) {
    }
    NamaFile[i] = '\0';

    if (!IsFileExist(NamaFile)) {
        printf("That file is not found\n");
    } else {
        START(NamaFile);

        printf("First Alphabet : %c\n", CC);
        ADV();
        printf("Second Alphabet : %c\n", CC);
        
        //menutup pita
        while (CC != MARK) {
            ADV();
        }
        ADV();

        //membuka file
        STARTKATA(NamaFile);

        printf("First Word : ");
        PrintKata();
        tKata = CKata;
        ADVKATA();
        printf("\nSecond Word : ");
        PrintKata(); 
        printf("\nConvert 'Kata' to integer : %d\n", KataToInt(CKata));

        printf("Compare the first and second word\n");
        if (IsKataSama(tKata, CKata)) {
            printf("they're same\n");
        } else {
            printf("they're different\n");
        }

        CKata = StrToKata("LALA");
        //Mengubah lala menjadi Kata
        PrintKata();
    }
}