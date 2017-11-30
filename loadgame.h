#ifndef loadgame_H
#define loadgame_H

#include "adtUnit.h"
#include "queue.h"
#include "pemain.h"
#include "stackt.h"
#include "boolean.h"


void LoadGame(Queue *turnQueue, pemain *pR, pemain *pB, villageList *vL, int *N, int *M, Stack *stackUndo, char *turnNow, boolean *loadsuccess);
// I.S. turnQueue, pR, pB dan vL dalam keadaan empty dan terdefinisi
// F.S. turnQueue, pR, pB dan vL berisi data permainan yang telah di-save kemudian di-load

void BacaUnit(unit *tUnit);
/* I.S. saat ini CKata berisi jenisUnit
   F.S. tUnit berisi spesifikasi lengkap sesuai dengan isi file eksternal */

void BacaVillage (village *tVillage);
/*  I.S. saat ini CKata berisi absis dari lokasi village
    F.S. tUnit berisi spesifikasi lengkap sesuai dengan isi file eksternal */

void PrintSlot (char * namaFile);
/*  I.S. namaFile terdefinisi
    F.S. menampilkan apakah slot tersebut telah berisi atau belum */

void BacaInfo (pemain *tP);
/*  I.S. saat ini CKata berisi warna dari pemain
    F.S. data pemain *tP telah terisi */

#endif