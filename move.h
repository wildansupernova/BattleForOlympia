/*nama file: move.h*/ 
/*Mengatur mekanisme move*/

#ifndef move_H
#define move_H

#include <stdio.h>
#include <stdlib.h>
#include "adtUnit.h"
#include "point.h"
#include "stackt.h"
#include "listlinierunit.h"
#include "matriksPeta.h"
#include "listliniervillage.h"

boolean isBlocked(MATRIKS M, POINT P, unitaddress a);
/* Menghasilkan false jika petak yang dilewati ada penghalang, true jika tidak */ 

boolean SearchLoc(unitList L, POINT T);
/* Mencari apakah ada unit dalam elemen list yang berada di T */
/* Mengirimkan true jika ada, false jika tidak ada */

boolean isFriendlyUnit(MATRIKS M, int i, int j, unitaddress a);
/* Menghasilkan true jika petak berisi unit yang kepemilikannya sama, false jika 
 * berisi unit milik lawan */
 
boolean isMoveLegal(MATRIKS M, POINT P, unitList L1, unitList L2, unitaddress a);
/* Menghasilkan true jika pergerakan unit tersebut tidak menyalahi aturan movePoint,
 * false jika tidak */ 

int CountMove(POINT P, unitaddress a);
/* Menghitung Vektor MovePoint */

void UpdateUnit(POINT P, unitaddress a);
/* I.S. U terdefinisi, isMoveLegal true */
/* F.S. Menyimpan posisi unit dan movement point terupdate setelah move */

void MoveUnit(MATRIKS M, Stack *S, unitaddress a, char color, unitList UL1, unitList UL2, villageList *L1, villageList *L2, villageList *L3);
/* I.S. M, S, a, color terdefinisi */
/* F.S. Posisi unit diupdate, stack terisi point koordinat unit, 
 * movePoint dari unit berkurang atau habis */

void Undo(Stack *S, unitaddress a);
/* I.S. Stack bisa kosong atau terisi, unitaddress terdefinisi */
/* F.S. Unit kembali ke keadaan state sebelumnya */

boolean isVillage(MATRIKS M, POINT P);
/*Mengecek apakah petak yang dituju merupakan village */

void VillageIsMine(unitaddress a, villageList *L1, villageList *L2, villageList *Universal, char color);
/* I.S. Village tanpa kepemilikan atau milik lawan */
/* F.S. Village menjadi milik pemain yang unitnya menempati village tersebut */

void CariVillage (villageList L, unitaddress a, villageaddress *Prec, villageaddress *P);
/* Mencari apakah ada elemen list yang berinfo T */
/* Mengirimkan address jika ada, nil jika tidak ada */

#endif 
