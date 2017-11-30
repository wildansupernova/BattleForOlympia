#include "queue.h"
#include "boolean.h"
#include <stdio.h>
#include <stdlib.h>

/* ********* Prototype ********* */
boolean IsEmptyQueue (Queue Q)
/* Mengirim true jika Q kosong: lihat definisi di atas */
{
    return Head(Q) == NilQu && Tail(Q) == NilQu;
}
boolean IsFullQueue (Queue Q)
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxElQu */
{
    //return ((Head(Q) - 1) == Tail(Q) || ((Head(Q) - 1) == 0 && Tail(Q) == MaxElQu(Q)));
    return (Tail(Q) + MaxElQu(Q) - Head(Q) + 1) % MaxElQu(Q) == 0;
}
int NBElmtQueue (Queue Q)
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */
{
    if (IsEmptyQueue(Q)) {
        return 0;
    } else if (Tail(Q) < Head(Q)) {
        return (Tail(Q) - Head(Q) + MaxElQu(Q) + 1);
    } else {
        return (Tail(Q) - Head(Q) + 1);
    } 
}

/* *** Kreator *** */
void CreateEmptyQueue (Queue * Q, int Max)
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxElQu=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */
{
    (*Q).T = (infotypeQu*)malloc((Max + 1) * sizeof(infotypeQu));

    if ((*Q).T == NULL) {
        MaxElQu(*Q) = 0;
    } else {
        Head(*Q) = NilQu;
        Tail(*Q) = NilQu;
        MaxElQu(*Q) = Max;
    }
}
/* *** Destruktor *** */
void DeAlokasiQueue(Queue * Q)
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxElQu(Q) diset 0 */
{
    MaxElQu(*Q) = 0;
    Head(*Q) = NilQu;
    Tail(*Q) = NilQu;
    free((*Q).T);
}
/* *** Primitif Add/Delete *** */
void AddQueue (Queue * Q, infotypeQu X)
/* Proses: Menambahkan X pada Q dengan aturan FIFO */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" dengan mekanisme circular buffer */
{
    if (IsEmptyQueue(*Q)) {
        Head(*Q) = 1;
    }
    Tail(*Q) = (Tail(*Q) % MaxElQu(*Q)) + 1;
    InfoTail(*Q) = X;
}
void DelQueue (Queue * Q, infotypeQu * X)
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = NilQuai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer; 
        Q mungkin kosong */
{
    *X = InfoHead(*Q);
    if (Head(*Q) == Tail(*Q)) {
        Head(*Q) = NilQu;
        Tail(*Q) = NilQu;
    } else {
        Head(*Q) = (Head(*Q) % MaxElQu(*Q)) + 1;
    }
}