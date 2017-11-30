#ifndef battlesystem_H
#define battlesystem_H

#include "adtUnit.h"
#include "point.h"
#include "boolean.h"
#include "stackt.h"
#include "listlinierunit.h"

unitList ListCanAttack(unit USelected, unitList listUnitLawan);
/* Mengirimkan daftar unit yang bisa diserang oleh USelected */

void PrintJenis(unit U);
/* I.S. U terdefinisi */
/* F.S. Jenis U tercetak ke layar */

void PrintListCanAttack(unit USelected, unitList L, int *n);
/* I.S. L berisi daftar unit yang dapat diserang oleh USelected */
/* F.S. Isi L tercetak ke layar sesuai spesifikasi */

boolean canAttack(unit U1, unit U2);
/* Mengirimkan true jika U1 memiliki Attack Chance dan jarak U1 dan U2 == 1 */

void Battle(unitaddress PPlayer, unitaddress PEnemy, unitList *LPlayer, unitList *LEnemy, Stack *S, boolean *IsKingRDead, boolean *IsKingBDead);
/* I.S. PPlayer, PEnemy, LPlayer, dan LEnemy terdefinisi, dan player telah memilih */
        /* untuk menyerang unit pada PEnemy */
/* F.S. Terjadi pertarungan antar player dan enemy sesuai mekanisme bertarung pada spesifikasi */

void AttackCommand(unitaddress PSelected, unitList *listPlayer, unitList *listLawan, Stack *S, boolean *IsKingRDead, boolean *IsKingBDead);
/* I.S. PSelected, listPlayer, dan listLawan terdefinisi, player memasukkan command ATTACK */
/* F.S. Command selesai dieksekusi sesuai spesifikasi */

#endif