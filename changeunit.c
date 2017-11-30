#include "changeunit.h"
#include "mesinkatainput.h"
#include "battlesystem.h"
#include "point.h"
#include <stdio.h>

void ChangeUnit(unitaddress PSelectedOld, unitList *LPlayer)
/* I.S. PSelectedOld dan LPlayer terdefinisi */
/* F.S. Jika ada unit yang bisa dipilih, PSelectedOld tidak selected, dan user telah memilih PSelectedNew */
{
    /* Kamus Lokal */
    boolean found;
    int N, count;
    int i=0;
    unitaddress P,PSelectedNew;

    /* Algoritma */
    PrintListOfUnitsNotSelected(*LPlayer, &count);
    if (count!=1) {
        selected(UnitInfo(PSelectedOld)) = false;
        do {
            InputInteger(&N, "\nPlease enter the no. of unit you want to select:");
            if ((N < 1) || (N > (NbElmtUnit(*LPlayer)-1))) {
                printf("Invalid Number\n");
            }
        } while ((N < 1) || (N > (NbElmtUnit(*LPlayer)-1)));
        found = false;
        P = UnitFirst(*LPlayer);
        while ((P != Nil) && (!found)) {
            if (!selected(UnitInfo(P))) {
                i++;
            }
            if (i==N) {
                found = true;
            } else {
                P = UnitNext(P);
            }
        }
        selected(UnitInfo(P)) = true;
        printf("You are now selecting ");
        PrintJenis(UnitInfo(P)); printf("\n");
    }
}

void NextUnit(unitaddress PSelectedOld, unitList *LPlayer)
/* I.S. PSelectedOld dan LPlayer terdefinisi */
/* F.S. Unit terganti menjadi unit yang masih memiliki movement points atau attack chance */
/* Jika tidak ada, menampilkan pesan kegagalan */
{
    /* Kamus Lokal */
    unitaddress P, PSelectedNew;

    /* Algoritma */
    P = canMoveorAttack(*LPlayer);
    if (P==Nil) {
        printf("Command failed.\n");
    } else {
        selected(UnitInfo(PSelectedOld)) = false;
        selected(UnitInfo(P)) = true;
        printf("You are now selecting ");
        PrintJenis(UnitInfo(P)); printf("\n");
    }
}

unitaddress canMoveorAttack(unitList LPlayer)
/* Mengirimkan unit yang masih memiliki movement points atau attackchance */
{
    /* Kamus Lokal */
    boolean found;
    unitaddress P;

    /* Algoritma */
    found = false;
    P = UnitFirst(LPlayer);
    while ((P != Nil) && (!found)) {
        if ((((moveP(UnitInfo(P)))>0) || atkchance(UnitInfo(P))) && (!selected(UnitInfo(P)))) {
            found = true;
        } else {
            P = UnitNext(P);
        }
    }
    return P;
}

void PrintListOfUnitsNotSelected (unitList L, int *n)
/* I.S. L berisi daftar unit yang dimiliki player tapi tidak selected */
/* F.S. Isi L tercetak ke layar sesuai spesifikasi */
{
    /* Kamus Lokal */
    unitaddress P;
    int i=1;

    /* Algoritma */
    printf("== List of Units ==\n");
    P = UnitFirst(L);
    while (P != Nil) {
        if (!selected(UnitInfo(P))) {
            printf("%d. ", i);
            PrintJenis(UnitInfo(P)); printf(" ");
            TulisPOINT(location(UnitInfo(P)));
            printf(" | Health ");
            printf("%d\n", maxH(UnitInfo(P)));
            i++;
        }
        P = UnitNext(P);
    }
    if (i==1) {
        printf("You don't have any other units to change to.\n");
    }
    *n = i;
}