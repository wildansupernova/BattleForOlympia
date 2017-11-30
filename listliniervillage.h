#ifndef listliniervillage_H
#define listliniervillage_H

#include "point.h"
#include "boolean.h"
#include <stdlib.h>
#include "adtVillage.h"
//#include "time.h"
#define Nil NULL

typedef village villageinfotype;
typedef struct villagetElmtlist *villageaddress;
typedef struct villagetElmtlist { 
	villageinfotype info;
	villageaddress next;
} villageElmtList;
typedef struct {
	villageaddress First;
} villageList;

/* Definisi list : */
/* villageList kosong : First(L) = Nil */
/* Setiap elemen dengan villageaddress P dapat diacu Info(P), Next(P) */
/* Elemen terakhir list : jika addressnya Last, maka Next(Last)=Nil */
#define VillageInfo(P) (P)->info
#define VillageNext(P) (P)->next
#define VillageFirst(L) ((L).First)


/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean IsEmptyVillage (villageList L);
/* Mengirim true jika list kosong */

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmptyVillage (villageList *L);
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */

/****************** Manajemen Memori ******************/
villageaddress AlokasiVillage (villageinfotype X);
/* Mengirimkan unitaddress hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka unitaddress tidak nil, dan misalnya */
/* menghasilkan P, maka info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
void DealokasiVillage (villageaddress *P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian unitaddress P */

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/

villageaddress SearchVillage (villageList L, villageaddress P);
/* Mencari apakah ada elemen list yang beralamat P */
/* Mengirimkan true jika ada, false jika tidak ada */

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsVFirstVillage (villageList *L, villageinfotype X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
void InsVLastVillage (villageList *L, villageinfotype X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */

/*** PENGHAPUSAN ELEMEN ***/
void DelVFirstVillage (villageList *L, villageinfotype *X);
/* I.S. unitList L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
void DelVLastVillage (villageList *L, villageinfotype *X);
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirstVillage (villageList *L, villageaddress P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-unitaddress P sebagai elemen pertama */
void InsertAfterVillage (villageList *L, villageaddress P, villageaddress Prec);
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
void InsertLastVillage (villageList *L, villageaddress P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirstVillage (villageList *L, villageaddress *P);
/* I.S. unitList tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */

void DelLastVillage (villageList *L, villageaddress *P);
/* I.S. unitList tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen terakhir yg lama, */
/* jika ada */
void DelAfterVillage (villageList *L, villageaddress *Pdel, villageaddress Prec);
/* I.S. unitList tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */

/****************** PROSES SEMUA ELEMEN LIST ******************/

int NbElmtVillage (villageList L);
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */

boolean SearchKoordinatVillage (villageList L, POINT P);
//Mencari viilage yang pointnnya sama

#endif