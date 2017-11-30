#ifndef CHANGEUNIT_H
#define CHANGEUNIT_H

#include "adtUnit.h"
#include "listlinierunit.h"

void ChangeUnit(unitaddress PSelectedOld, unitList *LPlayer);
/* I.S. PSelectedOld dan LPlayer terdefinisi */
/* F.S. Jika ada unit yang bisa dipilih, PSelectedOld tidak selected, dan user telah memilih PSelectedNew */

void NextUnit(unitaddress PSelectedOld, unitList *LPlayer);
/* I.S. PSelectedOld dan LPlayer terdefinisi */
/* F.S. Unit terganti menjadi unit yang masih memiliki movement points atau attack chance */
/* Jika tidak ada, menampilkan pesan kegagalan */

unitaddress canMoveorAttack(unitList LPlayer);
/* Mengirimkan daftar unit yang masih memiliki movement points atau attackchance */

void PrintListOfUnitsNotSelected (unitList L, int *n);
/* I.S. L berisi daftar unit yang dimiliki player tapi tidak selected */
/* F.S. Isi L tercetak ke layar sesuai spesifikasi */

#endif