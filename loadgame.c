#include <stdio.h>
#include <string.h>
#include "mesinkata.h"
#include "mesinkatainput.h"
#include "loadgame.h"
#include "adtUnit.h"
#include "listlinierunit.h"

void LoadGame(Queue *turnQueue, pemain *pR, pemain *pB, villageList *vL, int *N, int *M, Stack *stackUndo, char *turnNow, boolean *loadsuccess) {
// I.S. turnQueue, pR, pB dan vL dalam keadaan empty dan terdefinisi
// F.S. turnQueue, pR, pB dan vL berisi data permainan yang telah di-save kemudian di-load
    //Kamus
    boolean s; //s menyatakan file slot yang akan di-load (apakah bisa apa tidak)
    int tInput, temp1, temp2;
    char* fInput;
    POINT tPoint;
    unit tUnit;
    unitList uL1, uL2;
    villageList vL1, vL2;
    village tVillage;

    //Algoritma
    printf("Data Slot :\n");
    printf("1. Slot 1\n> ");
    PrintSlot("slot1.txt");
    printf("\n2. Slot 2\n> ");
    PrintSlot("slot2.txt");
    printf("\n3. Slot 3\n> ");
    PrintSlot("slot3.txt");
    printf("\n");

    if (!IsFileExist("slot1.txt") && !IsFileExist("slot2.txt") && !IsFileExist("slot3.txt")) {
        printf("Sorry, there isn't saved game\n");
        *loadsuccess = false;
    } else { //terdapat simpanan
        do {
            InputInteger(&tInput, "Choose slot :");
            if ((tInput < 1) && (tInput > 3)) {
                printf("Input must be between 1 and 3\n");
            } else {
                if (tInput == 1) {
                    s = IsFileExist("slot1.txt");
                } else if (tInput == 2) {
                    s = IsFileExist("slot2.txt");
                } else {
                    s = IsFileExist("slot3.txt");
                }
                if (!s) {   //jika tidak ada data
                    printf("There is not data on that slot\n");
                }
            }
        } while (!s); //validasi hingga yang di-load adalah file yang benar

        if (tInput == 1) {
            STARTKATA("slot1.txt");
        } else if (tInput == 2) {
            STARTKATA("slot2.txt");
        } else {
            STARTKATA("slot3.txt");
        }
        //Inisialisasi
        CreateEmptyUnit(&uL1);
        CreateEmptyUnit(&uL2);
        CreateEmptyVillage(&vL1);
        CreateEmptyVillage(&vL2);
        //CKata = "time"
        ADVKATA(); ADVKATA(); ADVKATA(); ADVKATA(); ADVKATA();
        //CKata = "turn"
        ADVKATA();      
        *turnNow = chr(CKata, 1);
        if (chr(CKata, 1) == 'R') {
            AddQueue(turnQueue, 'B');
            AddQueue(turnQueue, 'R');
        } else {
            AddQueue(turnQueue, 'R');
            AddQueue(turnQueue, 'B');
        }
        ADVKATA();      
        //CKata = "peta"
        ADVKATA();
        *N = KataToInt(CKata);
        ADVKATA();
        *M = KataToInt(CKata);
        ADVKATA();      
        //CKata = "playerR"
        ADVKATA();      
        //CKata = "info"
        ADVKATA();
        BacaInfo(pR);
        ADVKATA();      
        //CKata = "unit"
        ADVKATA();
        while (!IsKataSama(CKata, StrToKata("village"))){
            BacaUnit(&tUnit);
            InsVFirstUnit(&uL1, tUnit);
            ADVKATA();
        }
        listUnitP(*pR) = uL1;
        //CKata = "village"
        ADVKATA();
        while (!IsKataSama(CKata, StrToKata("playerB"))) {
            BacaVillage(&tVillage);
            InsVFirstVillage(&vL1, tVillage);
            ADVKATA();
        }
        listVillageP(*pR) = vL1;
        //CKata = "player B"
        ADVKATA();      
        //CKata = "info"
        ADVKATA();
        BacaInfo(pB);
        ADVKATA();      
        //CKata = "unit"
        ADVKATA();
        while (!IsKataSama(CKata, StrToKata("village"))) {
            BacaUnit(&tUnit);
            InsVFirstUnit(&uL2, tUnit);
            ADVKATA();
        }                
        listUnitP(*pB) = uL2;
        //CKata = "village"
        ADVKATA();
        while (!IsKataSama(CKata, StrToKata("villageUni"))) {
            BacaVillage(&tVillage);
            InsVFirstVillage(&vL2, tVillage);
            ADVKATA();
        }
        listVillageP(*pB) = vL2;
        //CKata = "villageUni"
        ADVKATA();
        while (!IsKataSama(CKata, StrToKata("stack"))) {
            BacaVillage(&tVillage);
            InsVFirstVillage(vL, tVillage);
            ADVKATA();
        }
        //CKata = "stack"
        ADVKATA();
        while (!EndKata) {
            temp1 = KataToInt(CKata);
            ADVKATA();
            temp2 = KataToInt(CKata);
            tPoint = MakePOINT(temp1, temp2);
            Push(stackUndo, tPoint);
            ADVKATA();
        }

        printf("\nYour previous game has been loaded");
        *loadsuccess = true;
    }
}

void BacaUnit(unit * tUnit) {
/* I.S. saat ini CKata berisi jenisUnit
   F.S. tUnit berisi spesifikasi lengkap sesuai dengan isi file eksternal */
   
    //Kamus
    int X, Y;
    POINT P;

    //Algoritma
    //Mengisi jenis unit
    jenisUnit(*tUnit) = chr(CKata, 1);
    //Mengisi kepemilikan unit
    nextKataFile();
    unitmilik(*tUnit) = chr(CKata, 1);
    //Mengisi max health dari unit
    nextKataFile();
    maxH(*tUnit) = KataToInt(CKata);
    //Mengisi health dari unit
    nextKataFile();
    Health(*tUnit) = KataToInt(CKata);
    //Mengisi attack dari unit
    nextKataFile();
    Attack(*tUnit) = KataToInt(CKata);
    //Mengisi max move point unit
    nextKataFile();
    maxMove(*tUnit) = KataToInt(CKata);
    //Mengisi move point unit
    nextKataFile();
    moveP(*tUnit) = KataToInt(CKata);
    //Mengisi attack type unit
    nextKataFile();
    AtkType(*tUnit) = KataToInt(CKata);

    //mengisi point dari unit
    nextKataFile();
    X = KataToInt(CKata);
    ADVKATA();
    Y = KataToInt(CKata);
    location(*tUnit) = MakePOINT(X, Y);

    //mengisi harga dari unit
    nextKataFile();
    harga(*tUnit) = KataToInt(CKata);
    
    //mengisi prob unit
    nextKataFile();
    prob(*tUnit) = KataToInt(CKata);
    //Mengisi attack chance dari unit
    nextKataFile();
    if (chr(CKata, 1) == '0') {
        atkchance(*tUnit) = false;
    } else {
        atkchance(*tUnit) = true;
    }
    
    //mengisi isSelected unit
    nextKataFile();
    if (chr(CKata, 1) == '0') {
        selected(*tUnit) = false;
    } else {
        selected(*tUnit) = true;
    }
}

void BacaVillage (village * tVillage) {
/*  I.S. saat ini CKata berisi absis dari lokasi village
    F.S. tUnit berisi spesifikasi lengkap sesuai dengan isi file eksternal */
    //Kamus
    int X, Y;

    //Algoritma
    X = KataToInt(CKata);
    ADVKATA();
    Y = KataToInt(CKata);
    LokasiVillage(*tVillage) = MakePOINT(X, Y);
    nextKataFile();
    MilikVillage(*tVillage) = chr(CKata, 1);
}

void BacaInfo (pemain *tP) {
/*  I.S. saat ini CKata berisi warna dari pemain
    F.S. data pemain *tP telah terisi */
    //Kamus

    //Algoritma
    warnaP(*tP) = chr(CKata, 1);
    nextKataFile();
    harta(*tP) = KataToInt(CKata);
    nextKataFile();
    incomeP(*tP) = KataToInt(CKata);
    nextKataFile();
    upkeepP(*tP) = KataToInt(CKata);
}

void PrintSlot (char * namaFile) {
/*  I.S. namaFile terdefinisi
    F.S. menampilkan apakah slot tersebut telah berisi atau belum */
    //Kamus
    
    //Algoritma
    if (IsFileExist(namaFile)) {
        STARTKATA(namaFile); //CKata = time
        printf("Last saved : ");
        ADVKATA(); 
        while (!IsKataSama(CKata, StrToKata("turn"))) {
            PrintKata(); printf(" ");
            ADVKATA();
        }
    } else {
        printf("There is not data in this slot");
    }
}