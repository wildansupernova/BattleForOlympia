#include "mesinkata.h"
#include <stdio.h>

boolean EndKata;
Kata CKata;

void IgnoreBlank()
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang 
   F.S. : CC ≠ BLANK atau CC = MARK */
{
    //Kamus

    //ALgoritma
     while (((CC == BLANK) || (CC == NEWLINE)) && (CC != MARK)) {
        ADV();
    }
}

void STARTKATA(char* namaFile)
/* I.S. : CC sembarang 
   F.S. : EndKata = true, dan CC = MARK; 
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */
{
    //Kamus

    //Algoritma
    START(namaFile);
    IgnoreBlank();
    if (CC == MARK) {
        EndKata = true;
    } else {
        EndKata = false;
        SalinKata();
    }
}
void ADVKATA()
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi 
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi, 
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKata = true.		  
   Proses : Akuisisi kata menggunakan procedure SalinKata */
{
    //Kamus

    //ALgoritma
    IgnoreBlank();
    if (CC == MARK) {
        EndKata = true;
    } else {
        SalinKata();
    }
}

void SalinKata()
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi; 
          CC = BLANK atau CC = MARK; 
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
{
    //Kamus
    int i;

    //Algoritma
    i = 1;
    while ((CC != MARK) && (CC != BLANK) && (CC != NEWLINE) && (i <= NMax)) {
        CKata.TabKata[i] = CC;
        i++;
        ADV();
    }
    // CC = MARK atau CC = BLANK
    CKata.Length = i-1;
}

int KataToInt(Kata kString) {
// menghasilkan integer dari suatu kata yang ada
    //Kamus
    int i = 1, sum = 0;

    //Algoritma
    if (chr(kString, i) == '-') {
        i++;
    }
    
    while (i <= length(kString)) {
        sum = sum * 10 + chr(kString, i) - '0';
        i++;
    }
    
    if (chr(kString, 1) == '-') {
        sum = -1 * sum;
    }

    return sum;
}

void nextKataFile() {
// ini untuk keperluan membaca file:)
    ADVKATA();
    ADVKATA();
}

boolean IsKataSama(Kata K1, Kata K2) {
// menghasilkan true ketika K1 = K2
    //Kamus
    boolean found;
    int i;

    //Algoritma
    if (length(K1) != length(K2)) {
        return false;
    } else {
        found = true;
        for (i = 1; i <= length(K1) && found; i++) {
            found = (chr(K1, i) == chr(K2, i));
        }
        return found;
    }
}

Kata StrToKata(char* sString) {
// menghasilkan kata dari string yang diberi input
    //Kamus
    Kata K1;
    int i, j;

    //Algoritma
    for(i = 1, j = 0; sString[j] != '\0'; i++, j++) {
        K1.TabKata[i] = sString[j];
    }
    K1.Length = i - 1;

    return K1;
}

void PrintKata() {
// I.S. terserah
// F.S. tercetak CKata pada layar
    //Kamus
    int i;

    //Algoritma
    
    for (i = 1; i <= length(CKata); i++) {
        printf("%c", chr(CKata, i));
    }
}