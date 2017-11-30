/* File: jam.c */
/* Tanggal: 31 Agustus 2016 */
/* Definisi ADT JAM */

/* #ifndef JAM_H */
/* #define JAM_H */

#include "stdio.h"
#include "boolean.h"
#include "jam.h"

/* *** Definisi TYPE JAM <HH:MM:SS> *** */
/* typedef struct { 
/* 	int HH; /* integer [0..23] */
/* 	int MM; /* integer [0..59] */
/* 	int SS; /* integer [0..59] */
/* } JAM; */

/* *** Notasi Akses: selektor JAM *** */
/* #define Hour(J) (J).HH   */
/* #define Minute(J) (J).MM */
/* #define Second(J) (J).SS */

/* ***************************************************************** */
/* DEFINISI PRIMITIF                                                 */
/* ***************************************************************** */
/* KELOMPOK VALIDASI TERHADAP TYPE                                   */
/* ***************************************************************** */

/* *** Konstruktor: Membentuk sebuah JAM dari komponen-komponennya *** */
JAM MakeJAM (int HH, int MM, int SS)
/* Membentuk sebuah JAM dari komponen-komponennya yang valid */
/* Prekondisi : HH, MM, SS valid untuk membentuk JAM */
{
	//Kamus lokal
	JAM J;
	
	//Algoritma
	Hour(J) = HH;
	Minute(J) = MM;
	Second(J) = SS;
	return J;
}

/* ***************************************************************** */
/* KELOMPOK BACA/TULIS                                               */
/* ***************************************************************** */
void BacaJAM (JAM * J)
/* I.S. : J tidak terdefinisi */
/* F.S. : J terdefinisi dan merupakan jam yang valid */
/* Proses : mengulangi membaca komponen HH, MM, SS sehingga membentuk J */
/* yang valid. Tidak mungkin menghasilkan J yang tidak valid. */
/* Pembacaan dilakukan dengan mengetikkan komponen HH, MM, SS
   dalam satu baris, masing-masing dipisahkan 1 spasi, diakhiri enter. */
/* Jika JAM tidak valid maka diberikan pesan: "Jam tidak valid", dan pembacaan
   diulangi hingga didapatkan jam yang valid. */
/* Contoh: 
   60 3 4
   Jam tidak valid
   1 3 4
   --> akan terbentuk JAM <1,3,4> */
{
	//Kamus lokal
	int th, tm, ts; 
	
	//Algoritma
	scanf("%d %d %d", &th, &tm, &ts);
	while(!IsJAMValid(th, tm, ts)) {
		printf("Jam tidak valid\n");
		scanf("%d %d %d", &th, &tm, &ts);
	}
	
	*J = MakeJAM(th, tm, ts);
}
   
void TulisJAM (JAM J)
/* I.S. : J sembarang */
/* F.S. :   Nilai J ditulis dg format HH:MM:SS */
/* Proses : menulis nilai setiap komponen J ke layar dalam format HH:MM:SS
   tanpa karakter apa pun di depan atau belakangnya, termasuk spasi, enter, dll.*/ 
{
	printf("%02d:%02d:%02d", Hour(J), Minute(J), Second(J));   
}

boolean IsJAMValid (int H, int M, int S)
/* Mengirim true  jika H,M,S dapat membentuk J yang valid */
/* dipakai untuk mentest SEBELUM membentuk sebuah Jam */
{
	return ((H >= 0) && (H <= 23) && (M >= 0) && (M <= 59) && (S >= 0) && (S <= 59));
}