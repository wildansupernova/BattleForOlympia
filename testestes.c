#include <stdio.h>

int main() {
    //Kamus
    char input[20];
    FILE *f;

    //Algoritma
    f = fopen("pitakar.txt", "r");
    if (f) {
        printf("ada\n");
    } else {
        printf("tidak ada\n");
    }

    fclose(f);
}