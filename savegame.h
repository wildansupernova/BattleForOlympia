#ifndef savegame_H
#define savegame_H

#include "pemain.h"
#include "listliniervillage.h"

void SaveGame(int i, int j, int N, char turnNow, villageList vL, pemain pR, pemain pB, Stack stackUndo);
// I.S. i, j, N, turnNow, uL1, uL2, vL terdefinisi
//      dengan N merupakan nilai slot ('1'/'2'/'3')
// F.S. terbentuk file eksternal untuk menyimpan data

#endif