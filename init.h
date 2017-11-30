#ifndef init_H
#define init_H

#define MaxElUnit 3

#include "queue.h"
#include "pemain.h"
#include "listliniervillage.h"
#include "listlinierunit.h"
#include "stackt.h"
#include "boolean.h"
#include "array.h"

void Judul();
//I.S. bebas
//F.S. tulisan batlle for olympia terbentuk dengan cantik

void InitEmpty(Queue *turnQueue, pemain *pR, pemain *pB, villageList *vL, Stack *tS);
// I.S. bebas
// F.S. turnQueue, pR, pB, vL, tS terdefinisi dengan semuanya menjadi empty

void MenuUtama (Queue *turnQueue, pemain *pR, pemain *pB, villageList *vL, int *N, int *M, boolean *exit, Stack *tS, char *turnNow, boolean *KingR, boolean *KingB);
// I.S. bebas
// F.S. semua parameter terdefinisi dan terdapat menu utama yang ditampilkan

void InitKing(pemain *pR, pemain *pB);

void InitArrUnit(TabUnit *unitRec);
// I.S. bebas
// F.S. unitRec terdefinisi berisi 3 unit yang dapat direkrut

void InitVillage(int M, int N, villageList *vL);
// I.S. M dan N terdefinisi dan vL dalam keadaan empty
// F.S. vL berisi village-village baru yang telah diciptakan

void InitLocKing (int M, int N, pemain *pR, pemain *pB);
//I.S. M, N, pR dan pB terdefinisi
//F.S. lokasi unit king pada masing-masing list linier unit player tergantikan (jadi benar)

#endif