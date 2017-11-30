/* MODUL TABEL INTEGER */
/* Berisi definisi dan semua primitif pemrosesan tabel integer */
/* Penempatan elemen selalu rapat kiri */
/* Versi I : dengan banyaknya elemen didefinisikan secara eksplisit, 
   memori tabel statik */

#ifndef ARRAY_H
#define ARRAY_H

#include "boolean.h"
#include "adtUnit.h"

/*  Kamus Umum */
#define IdxMax 3
/* Indeks maksimum array, sekaligus ukuran maksimum array dalam C */
#define IdxMin 1
/* Indeks minimum array */
#define IdxUndef -999 
/* Indeks tak terdefinisi*/

/* Definisi elemen dan koleksi objek */
typedef int IdxType;  /* type indeks */
typedef unit ElTypeAR;   /* type elemen tabel */
typedef struct { 
	ElTypeAR TI[IdxMax+1]; /* memori tempat penyimpan elemen (container) */
	int NeffAR; /* >=0, banyaknya elemen efektif */
} TabUnit;

/* Indeks yang digunakan [IdxMin..IdxMax] */
/* Jika T adalah TabUnit, cara deklarasi dan akses: */
/* Deklarasi : T : TabUnit */
/* Maka cara akses: 
   T.Neff  untuk mengetahui banyaknya elemen 
   T.TI    untuk mengakses seluruh nilai elemen tabel 
   T.TI[i] untuk mengakses elemen ke-i */
/* Definisi : 
  Tabel kosong: T.Neff = 0
  Definisi elemen pertama : T.TI[i] dengan i=1 
  Definisi elemen terakhir yang terdefinisi: T.TI[i] dengan i=T.Neff */
  
/* ********** SELEKTOR ********** */
#define NeffAR(T)   (T).NeffAR
#define TIAR(T)     (T).TI
#define ElmtAR(T,i) (T).TI[(i)]

/* ********** KONSTRUKTOR ********** */

boolean isEmptyAr(TabUnit T);
/* mengirimkan true jika T kosong*/

/* Konstruktor : create tabel kosong  */
void MakeEmptyArray (TabUnit * T);
/* I.S. T sembarang */
/* F.S. Terbentuk tabel T kosong dengan kapasitas IdxMax-IdxMin+1 */

void AddElmtArray (TabUnit * T, ElTypeAR tUnit);
/* I.S. T tidak penuh */
/* F.S. Bertambah suatu elemen array berupa tUnit dan Neff dari array bertambah 1*/

void PrintArray (TabUnit T);
/* I.S. T sembarang
   F.S. tercetak isi array */

#endif