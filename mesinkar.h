/* File: mesinkar.h */
/* Definisi Mesin Karakter */

#ifndef __MESIN_KAR_H_
#define __MESIN_KAR_H_

#define NMax 200
#include "boolean.h"
typedef struct {
	char TabKata[NMax+1]; /* container penyimpan kata, indeks yang dipakai [1..NMax] */
    int Length;
} Kata;

#define MARK '.'

#define chr(CKata, i) (CKata).TabKata[(i)]
#define length(CKata) (CKata).Length

/* State Mesin */
extern char CC;
extern boolean EOP;

void START(char* namaFile);
/* Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
   Karakter pertama yang ada pada pita posisinya adalah pada jendela.
   I.S. : sembarang
   F.S. : CC adalah karakter pertama pada pita
          Jika CC != MARK maka EOP akan padam (false)
          Jika CC = MARK maka EOP akan menyala (true) */

void ADV();
/* Pita dimajukan satu karakter. 
   I.S. : Karakter pada jendela = CC, CC != MARK
   F.S. : CC adalah karakter berikutnya dari CC yang lama, 
          CC mungkin = MARK
          Jika  CC = MARK maka EOP akan menyala (true) */

boolean IsFileExist(char * namaFile); 
// Mengirimkan true jika ada file yang bernama namaFile

#endif
