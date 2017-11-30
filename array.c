//Nama/NIM : Muhammad Alif Arifin/13516078
//Topik : ADT ARRAY
//Tanggal : 7 September 2017
//Deskripsi : Membuat realisasi dari setiap fungsi dan prosedur yang ada

#include "boolean.h"
#include "array.h"
#include "point.h"
#include <stdio.h>

/* ********** KONSTRUKTOR ********** */

boolean isEmptyAr(TabUnit T)
/* mengirimkan true jika T kosong*/
{
	return NeffAR(T) == 0;
}

/* Konstruktor : create tabel kosong  */
void MakeEmptyArray (TabUnit * T)
/* I.S. T sembarang */
/* F.S. Terbentuk tabel T kosong dengan kapasitas IdxMax-IdxMin+1 */
{
	NeffAR(*T) = 0;
}

void AddElmtArray (TabUnit * T, ElTypeAR tUnit)
/* mengirimkan true jika T kosong*/
{
	//Kamus
	IdxType i;

	//Algoritma
	i = IdxMin + NeffAR(*T);
	ElmtAR(*T, i) = tUnit;
	NeffAR(*T)++;
}

void PrintArray (TabUnit T)
/* I.S. T sembarang
   F.S. tercetak isi array */
{
	//Kamus
	IdxType i;

	//Algoritma
	if (isEmptyAr(T)) {
		printf("Array is empty\n");
	} else {
		for (i = 1; i <= NeffAR(T); i++) {
			if (jenisUnit(ElmtAR(T, i)) == 'A') {
				printf("%d. Archer", i);
			} else if (jenisUnit(ElmtAR(T, i)) == 'S') {
				printf("%d. Swordsman", i);
			} else if (jenisUnit(ElmtAR(T, i)) == 'W') {
				printf("%d. White Mage", i);
			}
			printf(" | Health %d | ATK %d | %dG\n", Health(ElmtAR(T, i)), Attack(ElmtAR(T, i)), harga(ElmtAR(T, i)));
		} 
	}
}


