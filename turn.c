#include "turn.h"
#include <stdlib.h>
#include <stdio.h>

void EndTurn(Queue *turnQueue, Stack *stackUndo, pemain *pR, pemain *pB, char *turnNow) {
// I.S. turnQueue, stackUndo, pR, pB terdefinisi
// F.S. turnQueue, stackUndo, pR, pB terupdate dan unitNow berisi unit yang sedang jalan pada awal turn (re: King)

    //Kamus
    infotypeQu X;
    unitaddress P;
    villageaddress Pv;

    //Algoritma
    DelQueue(turnQueue, &X);
    AddQueue(turnQueue, X);
    CreateEmptySt(stackUndo);
    *turnNow = X;
    if (X == 'R') { //meng-update harta pemain R
        
        harta(*pR) += incomeP(*pR) - upkeepP(*pR);

        P = UnitFirst(listUnitP(*pR));
        while (P != Nil) {
            if (jenisUnit(UnitInfo(P)) == 'K') {
                selected(UnitInfo(P)) = true;
                // *unitNow = P;
            } else if(jenisUnit(UnitInfo(P)) == 'W') {
                HealUnit(PlusDelta(location(UnitInfo(P)), 0, 1), pR);
                HealUnit(PlusDelta(location(UnitInfo(P)), 0, -1), pR);
                HealUnit(PlusDelta(location(UnitInfo(P)), 1, 0), pR);
                HealUnit(PlusDelta(location(UnitInfo(P)), -1, 0), pR);
            }
            moveP(UnitInfo(P)) = maxMove(UnitInfo(P));
            atkchance(UnitInfo(P)) = true;
            P = UnitNext(P);
        } 

        //men-"tidak selected"-kan unit" player lain
        P = UnitFirst(listUnitP(*pB));
        while (P != Nil) {
            selected(UnitInfo(P)) = false;
            P = UnitNext(P);
        }

        //menghitung jumlah unit yang dimiliki kecuali King
        Pv = VillageFirst(listVillageP(*pR));
        while (Pv != Nil) {
            HealUnit(LokasiVillage(VillageInfo(Pv)), pR);
            Pv = VillageNext(Pv);
        }

    } else { //meng-update harta pemain B
        harta(*pB) += incomeP(*pB) - upkeepP(*pB);
        P = UnitFirst(listUnitP(*pB));
        while (P != Nil) {
            if (jenisUnit(UnitInfo(P)) == 'K') {
                selected(UnitInfo(P)) = true;
                // *unitNow = P;
            } else if(jenisUnit(UnitInfo(P)) == 'W') {
                HealUnit(PlusDelta(location(UnitInfo(P)), 0, 1), pB);
                HealUnit(PlusDelta(location(UnitInfo(P)), 0, -1), pB);
                HealUnit(PlusDelta(location(UnitInfo(P)), 1, 0), pB);
                HealUnit(PlusDelta(location(UnitInfo(P)), -1, 0), pB);
            }
            moveP(UnitInfo(P)) = maxMove(UnitInfo(P));
            atkchance(UnitInfo(P)) = true;
            P = UnitNext(P);
        } 
        //jenisUnit(UnitInfo(P)) = 'K'

        //men-"tidak selected"-kan unit" player lain
        P = UnitFirst(listUnitP(*pR));
        while (P != Nil) {
            selected(UnitInfo(P)) = false;
            P = UnitNext(P);
        }

        //menghitung jumlah unit yang dimiliki kecuali King
        Pv = VillageFirst(listVillageP(*pB));
        while (Pv != Nil) {
            HealUnit(LokasiVillage(VillageInfo(Pv)), pB);
            Pv = VillageNext(Pv);
        }
    }
}

void HealUnit(POINT petak, pemain *P) {
// I.S. petak terdefinisi dan *P menyimpan list linier unit yang telah terdefinisi
// F.S. unit pada petak tersebut ter-heal

    //Kamus
    unitaddress PU;

    //Algoritma
    PU = UnitFirst(listUnitP(*P));
    while (PU != Nil) {
        if (EQPOINT(petak, location(UnitInfo(PU)))) {
            Health(UnitInfo(PU)) += 3;
            if (Health(UnitInfo(PU)) > maxH(UnitInfo(PU))) {
                (Health(UnitInfo(PU)) = maxH(UnitInfo(PU)));
            }
        }
        PU = UnitNext(PU);
    }
}