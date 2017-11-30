//Driver Matriks Peta Secara umum

#include <stdio.h>
#include <stdlib.h>
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
#include "time.h"







int main(){
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

    //Algoritma

    InitArrUnit(&unitRec);

    MenuUtama(&turnQueue, &PR, &PB, &vLUni, &Brs, &Kol, &isExit, &undoStack, &turnNow);
    MakeNormalMATRIKS(Brs, Kol, &mPeta);
    generateDesaNyesuainPeta(&vLUni,mPeta);
    Gambar(&mPeta, listUnitP(PR), listUnitP(PB), listVillageP(PR), listVillageP(PB), vLUni);
    printMatriks(mPeta);
    /*time_t t;*/
    /*srand((unsigned) time(&t));*/
    /*for(int i=1;i<=10;i++){
        //int ci ;
        //scanf("%d",&ci);
        POINT c = KoordinatRandom(mPeta);
        printf("%d %d\n", Absis(c),Ordinat(c));
        printf("randomnya : %d\n",GenerateRandomRange(0,10));

    }*/





}