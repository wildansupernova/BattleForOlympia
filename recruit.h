//recruit

#include "boolean.h"
#include "matriksPeta.h"
#include "adtUnit.h"
#include "listlinierunit.h"
#include "array.h"
#include "mesinkatainput.h"
#include "pemain.h"
#include "stackt.h"

void recplayer1(unitList *L, MATRIKS M , TabUnit TabPemain, char turnNow, unit U, pemain *P, Stack *S);
/* I.S. : list unit terdefinisi */
/* F.S. : akan melakukan perekrutan 
		  jika unit itu hanya king, king harus berada di tower, 
		  king boleh merekrut apabila ada suatu castle yang tidak
		  ditempati 
*/
boolean cekKingIntower(MATRIKS M,unit U);
//F.S : true apabila king berada di tower dan sebaliknya


boolean isAllCastleFull(char turnNow, MATRIKS M);
//F.S : mengirimkan true jika semua castle telah ditempati oleh unit

