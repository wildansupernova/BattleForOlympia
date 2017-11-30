#include "point.h"
#include <stdio.h>
#include <math.h>

#define PI 3.14159265

//NIM 13516012
//Nama Wildan Dicky Alnatara
//Tanggal 31/08/2017	
//Topik praktikum :modularitas c
//Deskripsi modularitas c
POINT MakePOINT (int x, int y)
/* Membentuk sebuah point dari x dan y dengan x sebagai absis dan
y sebagai ordinat */
{ /* KAMUS */
POINT P;
/* ALGORITMA */
Absis(P) = x;
Ordinat(P) = y;
return P;
}

void BacaPOINT (POINT * P)
/* Membentuk P dari x dan y yang dibaca dari keyboard */
{ /* KAMUS */
	int x, y;
	/* ALGORITMA */
	scanf("%d", &x);
	scanf("%d", &y);
	*P = MakePOINT(x,y);
}

void TulisPOINT (POINT P)
/* Nilai P ditulis ke layar dg format "(X,Y)" */
{ /* ALGORITMA */
	printf("(%d,%d)", Absis(P), Ordinat(P));
}

boolean EQPOINT (POINT P1, POINT P2){
	/* Mengirimkan true jika P1 = P2 : absis dan ordinatnya sama */
	return (Absis(P1)==Absis(P2))&&(Ordinat(P1)==Ordinat(P2));	
}

boolean NEQPOINT (POINT P1, POINT P2){
	/* Mengirimkan true jika P1 tidak sama dengan P2 */
	return (Absis(P1)!=Absis(P2))||(Ordinat(P1)!=Ordinat(P2));
}

/* *** KELOMPOK OPERASI LAIN TERHADAP TYPE *** */                           
POINT NextX (POINT P){
	Absis(P)+=1;
	
	return P;
/* Mengirim salinan P dengan absis ditambah satu */    }          
POINT NextY (POINT P){
	Ordinat(P)+=1;
	return P;
/* Mengirim salinan P dengan ordinat ditambah satu */}
POINT PlusDelta (POINT P, int deltaX, int deltaY){
	POINT temp = P;
	
	Absis(temp)+=deltaX;
	Ordinat(temp)+=deltaY;
	
	return temp;
/* Mengirim salinan P yang absisnya adalah Absis(P) + deltaX dan ordinatnya adalah Ordinat(P) + deltaY */}

void Geser (POINT *P, int deltaX, int deltaY){
/* I.S. P terdefinisi */
/* F.S. P digeser, absisnya sebesar deltaX dan ordinatnya sebesar deltaY */

	
	*P=PlusDelta(*P,deltaX,deltaY);
}


float Panjang(POINT P1, POINT P2) {
	float selisihx = Absis(P1)-Absis(P2);
	float selisihy = Ordinat(P1)-Ordinat(P2);
	return sqrt((selisihx*selisihx)+(selisihy*selisihy));
}

