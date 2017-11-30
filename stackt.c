#include <stdio.h>
#include "stackt.h"

void CreateEmptySt (Stack *S)
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack S yang kosong berkapasitas MaxElSt */
/* jadi indeksnya antara 1.. MaxElSt+1 karena 0 tidak dipakai */
/* Ciri stack kosong : TOP berNilStai NilSt */
{
    Top(*S) = NilSt;
}

/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsEmptySt (Stack S)
/* Mengirim true jika Stack kosong: lihat definisi di atas */
{
    return Top(S) == NilSt;
}
boolean IsFullSt (Stack S)
/* Mengirim true jika tabel penampung NilStai elemen stack penuh */
{
    return Top(S) == MaxElSt;
}
/* ************ Menambahkan sebuah elemen ke Stack ************ */
void Push (Stack * S, infotypeSt X)
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */
{
    Top(*S)++;
    InfoTop(*S) = X;
}
/* ************ Menghapus sebuah elemen Stack ************ */
void Pop (Stack * S, infotypeSt* X)
/* Menghapus X dari Stack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah NilStai elemen TOP yang lama, TOP berkurang 1 */
{
    *X = InfoTop(*S);
    Top(*S)--;
}