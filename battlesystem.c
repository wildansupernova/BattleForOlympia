#include "battlesystem.h"
#include "mesinkatainput.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void PrintJenis(unit U)
/* I.S. U terdefinisi */
/* F.S. Jenis U tercetak ke layar */
{
    if (jenisUnit(U)=='A') {
        printf("Archer");
    } else if (jenisUnit(U)=='S') {
        printf("Swordsman");
    } else if (jenisUnit(U)=='K') {
        printf("King");
    } else {
        printf("White Mage");
    }
}


void PrintListCanAttack(unit USelected, unitList L, int *n)
/* I.S. L berisi daftar unit yang dapat diserang oleh USelected */
/* F.S. Isi L tercetak ke layar sesuai spesifikasi */
{
    int i=1;
    unitaddress P;

    if (!atkchance(USelected)) {
        printf("You have ran out of attack chances.\n");
    } else {
        printf("Please select the enemy you want to attack:\n");
        P = UnitFirst(L);
        while (P != Nil) {
            if(canAttack(USelected,UnitInfo(P))) {
                printf("%d. ", i);
                PrintJenis(UnitInfo(P));
                printf(" ");
                TulisPOINT(location(UnitInfo(P)));
                printf(" | ");
                printf("Health %d/%d", Health(UnitInfo(P)), maxH(UnitInfo(P)));
                if (jenisUnit(USelected)==jenisUnit(UnitInfo(P))) {
                    printf(" (Retaliates)");
                }
                printf("\n");
                i++;
            }
            P = UnitNext(P);
        }
        if(i==1) {
            printf("There is no enemy you can attack.\n");
        }
    }
    *n = i;
}

boolean canAttack(unit U1, unit U2)
/* Mengirimkan true jika U1 memiliki Attack Chance dan jarak U1 dan U2 == 1 */
{
    if ((atkchance(U1)) && (Panjang(location(U1), location(U2)) == 1)) {
        return true;
    } else {
        return false;
    }
}

void Battle(unitaddress PPlayer, unitaddress PEnemy, unitList *LPlayer, unitList *LEnemy, Stack *S, boolean *IsKingRDead, boolean *IsKingBDead)
/* I.S. PPlayer, PEnemy, LPlayer, dan LEnemy terdefinisi, dan player telah memilih */
        /* untuk menyerang unit pada PEnemy */
/* F.S. Terjadi pertarungan antar player dan enemy sesuai mekanisme bertarung pada spesifikasi */
{
    boolean deadEnemy = false;

    srand(time(NULL));
    int r = (rand() % 5) + 1;
    if (r<=prob(UnitInfo(PEnemy))) { 
        printf("Your attack succeeded.\n");
        Health(UnitInfo(PEnemy)) -= Attack(UnitInfo(PPlayer));
        printf("Enemy's ");
        PrintJenis(UnitInfo(PEnemy));
        printf(" is damaged by %d.\n", Attack(UnitInfo(PPlayer)));
        if (Health(UnitInfo(PEnemy))<=0) /* Musuh mati */ {
            deadEnemy = true;
            if (jenisUnit(UnitInfo(PEnemy))=='K') {
                if (unitmilik(UnitInfo(PEnemy))=='R') {
                    *IsKingRDead = true;
                } else {
                    *IsKingBDead = true;
                }
            }
            printf("Enemy's ");
            PrintJenis(UnitInfo(PEnemy));
            printf(" is dead.\n");
            DelP(LEnemy, PEnemy);
        }
    } else {
        printf("The enemy evaded the attack.\n");
    } 
    if (((AtkType(UnitInfo(PPlayer)) == AtkType(UnitInfo(PEnemy)) || jenisUnit(UnitInfo(PEnemy)) == 'K')) && (!deadEnemy)) {
        r = (rand() % 5) + 1;
        if (r<=prob(UnitInfo(PPlayer))) {
            Health(UnitInfo(PPlayer)) -= Attack(UnitInfo(PEnemy));
            printf("Enemy's ");
            PrintJenis(UnitInfo(PEnemy));
            printf(" retaliates.\n");
            printf("Your ");
            PrintJenis(UnitInfo(PPlayer));
            printf(" is damaged by %d.\n", Attack(UnitInfo(PEnemy)));
        } else {
            printf("You evaded the enemy's retaliation.\n");
        }
    }
    if (Health(UnitInfo(PPlayer))<=0) {    
        if (jenisUnit(UnitInfo(PPlayer))=='K') {
            if (unitmilik(UnitInfo(PPlayer))=='R') {
                *IsKingRDead = true;
            } else {
                *IsKingBDead = true;
            }
        }    
        printf("Your ");
        PrintJenis(UnitInfo(PPlayer));
        printf(" is dead :(\n");
        DelP(LPlayer, PPlayer);
    } else {
        atkchance(UnitInfo(PPlayer)) = false;
        moveP(UnitInfo(PPlayer)) = 0;
    }
    CreateEmptySt(S);
}

void AttackCommand(unitaddress PSelected, unitList *listPlayer, unitList *listLawan, Stack *S, boolean *IsKingRDead, boolean *IsKingBDead)
/* I.S. PSelected, listPlayer, dan listLawan terdefinisi, player memasukkan command ATTACK */
/* F.S. Command selesai dieksekusi sesuai spesifikasi */
{
    boolean found;
    int N;
    int i=0;
    int count;
    unitaddress PEnemy;

    PrintListCanAttack(UnitInfo(PSelected), *listLawan, &count);
    if (count != 1) {
        do {
            InputInteger(&N, "Select the enemy you want to attack: ");
            if ((N>count) || (N<=0)) {
                printf("Invalid number.\n");
            }
        } while ((N>count) || (N<=0));
        found = false;
        PEnemy = UnitFirst(*listLawan);
        while ((PEnemy != Nil) && (!found)) {
            if (canAttack(UnitInfo(PSelected),UnitInfo(PEnemy))) {
                i++;
            }
            if (i==N) {
                found = true;
            } else {
                PEnemy = UnitNext(PEnemy);
            }
        }
        Battle(PSelected, PEnemy, listPlayer, listLawan, S, IsKingRDead, IsKingBDead);
    }
}