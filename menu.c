#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "adtUnit.h"
#include "adtVillage.h"
#include "boolean.h"
#include "pemain.h"
#include "array.h"
#include "listlinierunit.h"
#include "listliniervillage.h"
#include "loadgame.h"
#include "mesinkar.h"
#include "mesinkarinput.h"
#include "mesinkata.h"
#include "mesinkatainput.h"
#include "point.h"
#include "queue.h"
#include "savegame.h"
#include "stackt.h"
#include "init.h"
#include "turn.h"
#include "battlesystem.h"
#include "changeunit.h"
#include "matriksPeta.h"
#include "move.h"
#include "jam.h"
#include "recruit.h"

unitaddress UnitSekarang(char turnNow, pemain pR, pemain pB);
// mengirimkan address dari pemain yang sedang dipilih saat ini

int main() {
    //Kamus
    TabUnit unitRec;
    Kata inputKat;
    Queue turnQueue;
    pemain PR, PB;
    unitaddress uP;
    villageaddress vP;
    villageList vLUni;
    int Brs, Kol, N, M, inputInt, nUnit, nVillage;
    boolean isisInputBenar = false, isExit = false, isQuit = false;
    char turnNow;
    Stack undoStack;
    MATRIKS mPeta;
    POINT P;
    boolean KingR, KingB;

    //Algoritma
    srand(time(NULL));
    InitArrUnit(&unitRec);
    
    //Embel" UI awal" wkwk
    while (!isExit) {
        // *exit = false;
        MenuUtama(&turnQueue, &PR, &PB, &vLUni, &Brs, &Kol, &isExit, &undoStack, &turnNow, &KingR, &KingB);

        if (isExit) {
            //goodbye:(
        } else {
            //Sudah Load Game atau New Game
            //InitPeta(Brs, Kol);
            
            MakeNormalMATRIKS(Brs, Kol, &mPeta);
            isQuit = false;
            while (!isQuit) {
                //update peta
                printf("\n");

                if (turnNow == 'R') {
                    

                    //mengupdate income dan upkeep
                    uP = UnitFirst(listUnitP(PR));
                    nUnit = 0;
                    nVillage = 0;
                    while (uP != Nil) {
                        if (jenisUnit(UnitInfo(uP)) != 'K') {
                            nUnit++;
                        }
                        uP = UnitNext(uP);
                    }

                    vP = VillageFirst(listVillageP(PR));
                    while (vP != Nil) {
                        nVillage++;
                        vP = VillageNext(vP);
                    }

                    //Meng-update upkeep dan income
                    upkeepP(PR) = nUnit;
                    incomeP(PR) = nVillage * 3;
                    
                    statusInfo(turnNow, PR);
                } else {
                    

                    //mengupdate income dan upkeep
                    uP = UnitFirst(listUnitP(PB));
                    nUnit = 0;
                    nVillage = 0;
                    while (uP != Nil) {
                        if (jenisUnit(UnitInfo(uP)) != 'K') {
                            nUnit++;
                        }
                        uP = UnitNext(uP);
                    }

                    vP = VillageFirst(listVillageP(PB));
                    while (vP != Nil) {
                        nVillage++;
                        vP = VillageNext(vP);
                    }

                    //Meng-update upkeep dan income
                    upkeepP(PB) = nUnit;
                    incomeP(PB) = nVillage * 3;

                    statusInfo(turnNow, PB);
                }

                printf("\n");

                Gambar(&mPeta, listUnitP(PR), listUnitP(PB), listVillageP(PR), listVillageP(PB), vLUni);
                InputKata(&inputKat, "Your input:");

                if (IsKataSama(inputKat, StrToKata("MOVE"))) {
                    if (moveP(UnitInfo(UnitSekarang(turnNow, PR, PB))) > 0) {
                        MoveUnit(mPeta, &undoStack, UnitSekarang(turnNow, PR, PB), turnNow, listUnitP(PR), listUnitP(PB), &listVillageP(PR), &listVillageP(PB), &vLUni);
                    } else {
                        printf("You can't move again\n");
                    }
                }
                else if (IsKataSama(inputKat, StrToKata("UNDO"))) {
                    Undo(&undoStack, UnitSekarang(turnNow, PR, PB));
                }
                else if (IsKataSama(inputKat, StrToKata("CHANGE_UNIT"))) {
                    if (turnNow == 'R') {
                        ChangeUnit(UnitSekarang(turnNow, PR, PB), &listUnitP(PR)); //belum diedit
                    } else {
                        ChangeUnit(UnitSekarang(turnNow, PR, PB), &listUnitP(PB));
                    }
                }
                else if (IsKataSama(inputKat, StrToKata("NEXT_UNIT"))) {
                    if (turnNow == 'R') {
                        NextUnit(UnitSekarang(turnNow, PR, PB), &listUnitP(PR)); //belum diedit
                    } else {
                        NextUnit(UnitSekarang(turnNow, PR, PB), &listUnitP(PB));
                    }
                }
                else if (IsKataSama(inputKat, StrToKata("RECRUIT"))) {
                    if (jenisUnit(UnitInfo(UnitSekarang(turnNow, PR, PB))) != 'K') {
                        printf("You cannot use this command, because you are not using King\n");
                    } else {
                        if (turnNow == 'R') {
                            recplayer1(&listUnitP(PR), mPeta, unitRec, turnNow, UnitInfo(UnitSekarang(turnNow, PR, PB)), &PR, &undoStack);
                        } else {
                            recplayer1(&listUnitP(PB), mPeta, unitRec, turnNow, UnitInfo(UnitSekarang(turnNow, PR, PB)), &PB, &undoStack);
                        }
                    }
                }
                else if (IsKataSama(inputKat, StrToKata("ATTACK"))) {
                    if (turnNow == 'R') {
                        AttackCommand(UnitSekarang(turnNow, PR, PB), &listUnitP(PR), &listUnitP(PB), &undoStack, &KingR, &KingB);
                    } else { //turnNow = B
                        AttackCommand(UnitSekarang(turnNow, PR, PB), &listUnitP(PB), &listUnitP(PR), &undoStack, &KingR, &KingB);
                    }
                }
                else if (IsKataSama(inputKat, StrToKata("MAP"))) {
                    printMatriks(mPeta);
                }
                else if (IsKataSama(inputKat, StrToKata("INFO"))) {
                    do {
                        InputPoint(&P, "Enter the coordinate of the cell:");
                        if (!IsIdxEff(mPeta, Absis(P), Ordinat(P))) {
                            printf("0 <= X <= %d and 0 <= Y <= %d\n", Brs-1, Kol-1);
                        } else {
                            infoPetak(mPeta, Absis(P), Ordinat(P));
                        }
                    } while (!IsIdxEff(mPeta, Absis(P), Ordinat(P)));
                }
                else if (IsKataSama(inputKat, StrToKata("END_TURN"))) {
                    EndTurn(&turnQueue, &undoStack, &PR, &PB, &turnNow);
                }
                else if (IsKataSama(inputKat, StrToKata("SAVE"))) {
                    
                    printf("Choose Slot :\n");
                    printf("1. Slot 1\n");
                    printf("2. Slot 2\n");
                    printf("3. Slot 3\n");

                    do {
                        InputInteger(&inputInt, "\nYour input :");
                        if (inputInt < 1 || inputInt > 3) {
                            printf("Input must be between 1 and 3\n");
                        }
                    } while(inputInt < 1 || inputInt > 3);
                    
                    SaveGame(Brs, Kol, inputInt, turnNow, vLUni, PR, PB, undoStack);
                    printf("\nYour game has been saved\nYou can load after exit this game\n");
                }
                else if (IsKataSama(inputKat, StrToKata("QUIT"))) {
                    isQuit = true;
                } else { //input salah
                    printf("Invalid command\n");
                }

                Gambar(&mPeta, listUnitP(PR), listUnitP(PB), listVillageP(PR), listVillageP(PB), vLUni);                

                if (KingR) {    //Salah satu king meninggal
                    if (turnNow == 'R') {
                        printf("You Lose\n");
                    } else {
                        printf("You Win\n");
                    }
                    isQuit = true;
                } else if (KingB) {
                    if (turnNow == 'B') {
                        printf("You Lose\n");
                    } else {
                        printf("You Win\n");
                    }
                    isQuit = true;
                }
            } //isQuit = true;
        }
    } //isExit = true;

    return 0;
}

unitaddress UnitSekarang(char turnNow, pemain pR, pemain pB) {
// mengirimkan address dari pemain yang sedang dipilih saat ini
    //KAMUS
    unitaddress PUS;

    //ALGORITMA
    if (turnNow == 'R') {
        PUS = UnitFirst(listUnitP(pR));
        while (!selected(UnitInfo(PUS))) {
            PUS = UnitNext(PUS);
        }
    } else {
        PUS = UnitFirst(listUnitP(pB));
        while (!selected(UnitInfo(PUS))) {
            PUS = UnitNext(PUS);
        }
    }

    return PUS;
}