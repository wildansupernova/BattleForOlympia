#include <stdio.h>
#include <time.h>
#include "mesinkata.h"
#include "mesinkar.h"
#include "boolean.h"
#include "adtUnit.h"
#include "adtVillage.h"
#include "listlinierunit.h"
#include "array.h"
#include "point.h"
#include "savegame.h"
#include "stackt.h"
#include "jam.h"

void SaveGame(int i, int j, int N, char turnNow, villageList vL, pemain pR, pemain pB, Stack stackUndo) {
// I.S. i, j, N, turnNow, uL1, uL2, vL terdefinisi
//      dengan N merupakan nilai slot ('1'/'2'/'3')
// F.S. terbentuk file eksternal untuk menyimpan data
// i = baris peta; j = kolom peta; N = nomor slot; 
    //Kamus
    FILE *f;
    time_t rawtime;
    struct tm * timeinfo;
    unitaddress Pu;
    villageaddress Pv;
    unit tUnit;
    village tVillage;
    unitList uL1, uL2;
    villageList vL1, vL2;
    POINT pLetak;
    JAM J;

    //Algoritma
    if (N == 1) {
        f = fopen("slot1.txt", "w");
    } else if (N == 2) {
        f = fopen("slot2.txt", "w");
    } else if (N == 3) {
        f = fopen("slot3.txt", "w");
    }

    if (f == NULL) {
        printf("Error while saving the game\n");
    } else {
        //Mencetak waktu saat pengesave-an berlangsung
        time ( &rawtime );
        timeinfo = localtime ( &rawtime );
        J = MakeJAM(timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
        fprintf(f, "time\n%d %d %d %d:%d:%d\n", timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, Hour(J), Minute(J), Second(J));
        //luas turn
        fprintf(f, "turn\n%c\n", turnNow);
        
        //luas peta
        fprintf(f, "peta\n");
        fprintf(f, "%d %d\n", i, j);

        //penanda player
        fprintf(f, "playerR\n");
        //mencetak info pemain 1
        fprintf(f, "info\n");
        fprintf(f, "%c | %d | %d | %d\n", warnaP(pR), harta(pR), incomeP(pR), upkeepP(pR));
        
        //mencetak unit player 1
        fprintf(f, "unit\n");
        uL1 = listUnitP(pR);
        Pu = UnitFirst(uL1);
        while (Pu != Nil) {
            tUnit = UnitInfo(Pu);
            fprintf(f, "%c | %c | %d | %d | %d | %d | %d | %d | %d %d | %d | %d |", jenisUnit(tUnit), unitmilik(tUnit), maxH(tUnit), Health(tUnit), Attack(tUnit), maxMove(tUnit), moveP(tUnit), AtkType(tUnit), Absis(location(tUnit)), Ordinat(location(tUnit)), harga(tUnit), prob(tUnit) );
            if (atkchance(tUnit)) {
                fprintf(f, " 1 |");
            } else {
                fprintf(f, " 0 |");
            }
            if (selected(tUnit)) {
                fprintf(f, " 1\n");
            } else {
                fprintf(f, " 0\n");
            }
            Pu = UnitNext(Pu);
        }

        //mencetak village player 1
        fprintf(f, "village\n");
        vL1 = listVillageP(pR);
        Pv = VillageFirst(vL1);
        while (Pv != Nil) {
            tVillage = VillageInfo(Pv);
            fprintf(f, "%d %d | %c\n", Absis(LokasiVillage(tVillage)), Ordinat(LokasiVillage(tVillage)), MilikVillage(tVillage));
            Pv = VillageNext(Pv);
        }

        //penanda player
        fprintf(f, "playerB\n");

        //mencetak info pemain 1
        fprintf(f, "info\n");
        fprintf(f, "%c | %d | %d | %d\n", warnaP(pB), harta(pB), incomeP(pB), upkeepP(pB));

        //mencetak unit player 2
        fprintf(f, "unit\n");
        uL2 = listUnitP(pB);
        Pu = UnitFirst(uL2);
        while (Pu != Nil) {
            tUnit = UnitInfo(Pu);
            fprintf(f, "%c | %c | %d | %d | %d | %d | %d | %d | %d %d | %d | %d |", jenisUnit(tUnit), unitmilik(tUnit), maxH(tUnit), Health(tUnit), Attack(tUnit), maxMove(tUnit), moveP(tUnit), AtkType(tUnit), Absis(location(tUnit)), Ordinat(location(tUnit)), harga(tUnit), prob(tUnit) );
            if (atkchance(tUnit)) {
                fprintf(f, " 1 |");
            } else {
                fprintf(f, " 0 |");
            }
            if (selected(tUnit)) {
                fprintf(f, " 1\n");
            } else {
                fprintf(f, " 0\n");
            }
            Pu = UnitNext(Pu);
        }

        //mencetak village player 2
        fprintf(f, "village\n");
        vL2 = listVillageP(pB);
        Pv = VillageFirst(vL2);
        while (Pv != Nil) {
            tVillage = VillageInfo(Pv);
            fprintf(f, "%d %d | %c\n", Absis(LokasiVillage(tVillage)), Ordinat(LokasiVillage(tVillage)), MilikVillage(tVillage));
            Pv = VillageNext(Pv);
        }

        //mencetak village yang tidak berpemilik
        fprintf(f, "villageUni\n");
        Pv = VillageFirst(vL);
        while (Pv != Nil) {
            tVillage = VillageInfo(Pv);
            fprintf(f, "%d %d | %c\n", Absis(LokasiVillage(tVillage)), Ordinat(LokasiVillage(tVillage)), MilikVillage(tVillage));
            Pv = VillageNext(Pv);
        }

        fprintf(f, "stack\n");
        while (!IsEmptySt(stackUndo)) {
            fprintf(f, "%d %d ", Absis(InfoTop(stackUndo)), Ordinat(InfoTop(stackUndo)));
        }
        fprintf(f, "."); //Mark
    }
}