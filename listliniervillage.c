#include "listliniervillage.h"
#include <stdio.h>
#include <stdlib.h>
#include "point.h"



/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean IsEmptyVillage (villageList L)
/* Mengirim true jika list kosong */
{
    return (VillageFirst(L)==Nil);
}

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmptyVillage (villageList *L)
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
{
    VillageFirst(*L) =  Nil;
}

/****************** Manajemen Memori ******************/
villageaddress AlokasiVillage (villageinfotype X)
/* Mengirimkan unitaddress hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka unitaddress tidak nil, dan misalnya */
/* menghasilkan P, maka info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
{
    villageaddress P = (villageElmtList * ) malloc (sizeof(villageElmtList));

    if (P!=Nil) {
        VillageInfo(P) = X;
        VillageNext(P) = Nil;
    }
    return P;
}

void DealokasiVillage (villageaddress *P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian unitaddress P */
{
    free(*P);
}

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/

boolean FSearchVillage (villageList L, villageaddress P)
/* Mencari apakah ada elemen list yang beralamat P */
/* Mengirimkan true jika ada, false jika tidak ada */
{
    villageaddress PSearch;
    boolean Found;

    PSearch = VillageFirst(L);
    Found = false;
    while ((PSearch != Nil) && (!Found)) {
        if (PSearch==P) {
            Found = true;
        }
        PSearch = VillageNext(PSearch);
    }
    return Found;
}

boolean SearchKoordinatVillage (villageList L, POINT P)
/* Mencari apakah ada elemen list yang berpoint P */
/* Mengirimkan true jika ada, false jika tidak ada */
{
    villageaddress PSearch;
    boolean Found;

    PSearch = VillageFirst(L);
    Found = false;
    while ((PSearch != Nil) && (!Found)) {
        if (EQPOINT(P,LokasiVillage(VillageInfo(PSearch)))) {
            Found = true;
        }
        PSearch = VillageNext(PSearch);
    }
    return Found;
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsVFirstVillage (villageList *L, villageinfotype X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
{
    villageaddress p = AlokasiVillage(X);
	if (p!=Nil){
        VillageNext(p) = VillageFirst(*L);
		VillageFirst(*L) = p;
	}
}

void InsVLastVillage (villageList *L, villageinfotype X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
    villageaddress P = AlokasiVillage(X);
	if (P != Nil) {
		if (IsEmptyVillage(*L)) {
			VillageNext(P) = VillageFirst(*L);
			VillageFirst(*L) = P;
		} else {
			villageaddress last = VillageFirst(*L);
			while(VillageNext(last) != Nil) {
				last=VillageNext(last);
			}
			VillageNext(last) = P;
		}
	}
}

/*** PENGHAPUSAN ELEMEN ***/
void DelVFirstVillage (villageList *L, villageinfotype *X)
/* I.S. unitList L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
{
    villageaddress P = VillageFirst(*L);
	*X = VillageInfo(P);
	VillageFirst(*L) = VillageNext(P);
	VillageNext(P) = Nil;
	DealokasiVillage(&P);
}

void DelVLastVillage (villageList *L, villageinfotype *X)
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
{
    villageaddress p = VillageFirst(*L);
	villageaddress prec= Nil;
	
	while(VillageNext(p)!=Nil){
		prec = p;
		p= VillageNext(p);
	}
	*X = VillageInfo(p);
	if (prec==Nil){
		VillageFirst(*L) = Nil;
	}  else{
		VillageNext(prec) = Nil;
	}
	DealokasiVillage(&p);
}

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirstVillage (villageList *L, villageaddress P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-unitaddress P sebagai elemen pertama */
{  
    VillageNext(P) = VillageFirst(*L);
	VillageFirst(*L) = P;
}

void InsertAfterVillage (villageList *L, villageaddress P, villageaddress Prec)
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
{
    VillageNext(P) = VillageNext(Prec);
    VillageNext(Prec) = P;
}

void InsertLastVillage (villageList *L, villageaddress P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
{
    if (IsEmptyVillage(*L)) {
        InsertFirstVillage(L, P);
	} else {
		villageaddress last = VillageFirst(*L);
		while(VillageNext(last)!=Nil){
			last = VillageNext(last);
		}
		InsertAfterVillage(L,P,last);
	}
}

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirstVillage (villageList *L, villageaddress *P)
/* I.S. unitList tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
{
    *P = VillageFirst(*L);
    VillageFirst(*L) = VillageNext(*P);
}

void DelLastVillage (villageList *L, villageaddress *P)
/* I.S. unitList tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen terakhir yg lama, */
/* jika ada */
{
    villageaddress last,prec;

	last = VillageFirst(*L);
	prec = Nil;
	while(VillageNext(last)!=Nil){
		prec = last;
		last = VillageNext(last);
	}
	*P = last;
	if (prec == Nil){
		VillageFirst(*L) = Nil;
	} else {
		VillageNext(prec) = Nil;
	}
}

void DelAfterVillage (villageList *L, villageaddress *Pdel, villageaddress Prec)
/* I.S. unitList tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */
{
    *Pdel = VillageNext(Prec);
	VillageNext(Prec) = VillageNext(VillageNext(Prec));
	VillageNext(*Pdel) =  Nil;
}

/****************** PROSES SEMUA ELEMEN LIST ******************/

int NbElmtVillage (villageList L)
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
{
    int count = 0;
    villageaddress P;

    P = VillageFirst(L);
    while (P != Nil) {
        count++;
        P = VillageNext(P);
    }
    return count;
}