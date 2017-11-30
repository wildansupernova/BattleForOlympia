#include "point.h"
#include <stdio.h>
//NIM 13516012
//Nama Wildan Dicky Alnatara
//Tanggal 31/08/2017	
//Topik praktikum :modularitas c
//Deskripsi modularitas c
int main(){
	/* KAMUS */
	POINT P, P1;
	float dx, dy;
	/* ALGORITMA */
	/* Test Baca dan Tulis */
	printf("Masukkan nilai absis dan ordinat untuk Variabel P: \n");
	BacaPOINT(&P);
	printf("Titik yang dibaca ");
	TulisPOINT(P);
	printf("\n");
	printf("Hasil Make Point dengan x=3 dan y=4");
	printf("\n");
	TulisPOINT(MakePOINT (3, 4));
	printf("\n");
	printf("Hasil EQPOINT dan NEQPOINT dengan x1=3 y1=3 x2=3 dan y2=3\n");
	printf("EQPOINT\n");
	if (EQPOINT(MakePOINT (3, 3),MakePOINT (3, 3))){
		printf("Benar sama \n");
	} else{
		printf("tidak sama \n");
	}
	printf("nEQ\n");
	if (NEQPOINT(MakePOINT (3, 3),MakePOINT (3, 3))){
		printf("Tidak sama \n");
	} else{
		printf("Benar sama \n");
	}
	printf("Hasil EQPOINT dan NEQPOINT dengan x1=4 y1=1 x2=3 dan y2=3\n");
	if (EQPOINT(MakePOINT (4, 1),MakePOINT (3, 3))){
		printf("Benar sama \n");
	} else{
		printf("tidak sama \n");
	}
	printf("nEQ\n");
	if (NEQPOINT(MakePOINT (4, 1),MakePOINT (3, 3))){
		printf("Tidak sama \n");
	} else{
		printf("Sama \n");
	}
	


	return 0;
}