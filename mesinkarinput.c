/* File: mesinkar.c */
/* Implementasi Mesin Karakter */

#include "mesinkarinput.h"
#include <stdio.h>

char CC;
boolean EOP;

static int nChar;
char s_input[201];

void STARTINPUT() {
/* Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
   Karakter pertama yang ada pada pita posisinya adalah pada jendela.
   I.S. : sembarang
   F.S. : CC adalah karakter pertama pada pita. Jika CC != MARK maka EOP akan padam (false).
          Jika CC = MARK maka EOP akan menyala (true) */

    /* Algoritma */
    nChar = 0; //inisialisasi
    CC = s_input[nChar];
}

void ADVINPUT() {
/* Pita dimajukan satu karakter. 
   I.S. : Karakter pada jendela = 
          CC, CC != MARK
   F.S. : CC adalah karakter berikutnya dari CC yang lama, 
          CC mungkin = MARK.
		  Jika  CC = MARK maka EOP akan menyala (true) */

	/* Algoritma */
    nChar++;
    CC = s_input[nChar];
	EOP = (CC == NILL);
}
