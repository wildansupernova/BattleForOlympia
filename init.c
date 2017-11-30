#include "loadgame.h"
#include "mesinkatainput.h"
#include "mesinkata.h"
#include "matriksPeta.h"
#include "listliniervillage.h"
#include "init.h"
#include <stdio.h>
#include <time.h>


void Judul() {
//I.S. bebas
//F.S. tulisan batlle for olympia terbentuk dengan cantik

    printf("                              (            \n");
    printf("   (           )   ) (        )\\ )         \n");
    printf(" ( )\\     ) ( /(( /( )\\  (   (()/(    (    \n");
    printf(" )((_) ( /( )\\())\\()|(_)))\\   /(_))(  )(   \n");
    printf("((_)_  )(_)|_))(_))/ _ /((_) (_))_|)\\(()\\  \n");
    printf(" | _ )((_)_| |_| |_ | (_))   | |_ ((_)((_) \n");
    printf(" | _ \\/ _` |  _|  _|| / -_)  | __/ _ \\ '_| \n");
    printf(" |___/\\)_,_|\\__|\\__||_\\___|  |_| \\___/_|   \n");
    printf("    ( /(  (                                \n");
    printf("    )\\()) )\\(       )        (     )       \n");
    printf("   ((_)\\ ((_)\\ )   (    `  ) )\\ ( /(       \n");
    printf("     ((_) _(()/(   )\\  '/(/(((_))(_))      \n");
    printf("    / _ \\| |)(_))_((_))((_)_\\(_|(_)_       \n");
    printf(" _ | (_) | | || | '  \\() '_ \\) / _` |_ _   \n");
    printf("(_|_)___/|_|\\_, |_|_|_|| .__/|_\\__,_(_|_)  \n");
    printf("            |__/       |_|                 \n");
}

void InitEmpty(Queue *turnQueue, pemain *pR, pemain *pB, villageList *vL, Stack *tS) {
// I.S. bebas
// F.S. turnQueue, pR, pB, vL, tS terdefinisi dengan semuanya menjadi empty

    //Kamus
    unitList uL1, uL2;
    villageList vL1, vL2;

    //Algoritma

    //Pengosongan
    CreateEmptyQueue(turnQueue, 2);
    
    CreateEmptyUnit(&listUnitP(*pR));
    CreateEmptyVillage(&listVillageP(*pR));
    
    //Inisialisasi isi pemain R
    warnaP(*pR) = 'R';
    harta(*pR) = 35;
    incomeP(*pR) = 0;
    upkeepP(*pR) = 0;

    //Pengosongan
    CreateEmptyUnit(&listUnitP(*pB));
    CreateEmptyVillage(&listVillageP(*pB));

    CreateEmptyVillage(vL);
    CreateEmptySt(tS);
    
    //Inisialisasi isi pemain B
    warnaP(*pB) = 'B';
    harta(*pB) = 35;
    incomeP(*pB) = 0;
    upkeepP(*pB) = 0;
}

void InitKing(pemain *pR, pemain *pB) {
    //Kamus
    POINT ValUndefP;
    unit tUnit;

    //Algoritma
        
    STARTKATA("king.txt");
    ValUndefP = MakePOINT(-1, -1);
    //Inisialisasi untuk King
    BacaUnit(&tUnit);
    ADVKATA();
    unitmilik(tUnit) = 'R';

    InsVFirstUnit(&listUnitP(*pR), tUnit);

    unitmilik(tUnit) = 'B';
    //Karena pertama kali itu si R
    selected(tUnit) = false;
    InsVFirstUnit(&listUnitP(*pB), tUnit);
}


void MenuUtama (Queue *turnQueue, pemain *pR, pemain *pB, villageList *vL, int *M, int *N, boolean *exit, Stack *tS, char *turnNow, boolean *KingR, boolean *KingB) {
// I.S. turnQueue, pR, pB, vL, N, M, exit bebas
// F.S. semua parameter terdefinisi

    //Kamus
    Kata input;
    boolean isInputBenar = false, loadsuccess;
    int tN, tM;
    MATRIKS mPeta;

    //Algoritma
    //Embel" UI awal" wkwk
    InitEmpty(turnQueue, pR, pB, vL, tS);
    *exit = false;
        
    while (!isInputBenar) {
        Judul();
        printf("===MENU===\n> NEW_GAME\n> LOAD_GAME\n> EXIT\n\n");
        InputKata(&input, "Your input :");
        if (IsKataSama(input, StrToKata("NEW_GAME"))) {
            InitEmpty(turnQueue, pR, pB, vL, tS);
            InitKing(pR, pB);
            do {
                printf("\n===MAP SIZE===\n");
                InputInteger(&tN, "Map column :");
                InputInteger(&tM, "Map row :");
                if ((tN < 8) || (tM < 8)) {
                    printf("The minimum size of map is 8 x 8\n");
                }
            } while ((tN < 8) || (tM < 8));
            isInputBenar = true;
            *M = tM;
            *N = tN;
            AddQueue(turnQueue, 'B');
            AddQueue(turnQueue, 'R');
            *turnNow = 'R';
            InitLocKing(*M, *N, pR, pB);
            MakeNormalMATRIKS(*M, *N, &mPeta);
            generateDesaNyesuainPeta(vL, mPeta);
            *KingR = false;
            *KingB = false;
        } else if (IsKataSama(input, StrToKata("LOAD_GAME"))) {
            InitEmpty(turnQueue, pR, pB, vL, tS);
            LoadGame(turnQueue, pR, pB, vL, N, M, tS, turnNow, &loadsuccess);
            if (loadsuccess) {
                isInputBenar = true;
                *KingR = false;
                *KingB = false;
            } else {
                isInputBenar = false;
            }
        } else if (IsKataSama(input, StrToKata("EXIT"))) {
            do {
                InputKata(&input, "Are you sure?");
                if (IsKataSama(input, StrToKata("YES"))) {
                    *exit = true; 
                    isInputBenar = true;
                } else if (!IsKataSama(input, StrToKata("NO"))) {
                    printf("\nInput must be 'YES' or 'NO'\n\n");
                }
            } while ((!IsKataSama(input, StrToKata("YES"))) && (!IsKataSama(input, StrToKata("NO"))));
        } else {
            printf("Input must be 'NEW_GAME' or 'LOAD_GAME' or 'EXIT'\n\n");
        }
    }
}

void InitArrUnit(TabUnit * unitRec) {
// I.S. bebas
// F.S. unitRec terdefinisi berisi 3 unit yang dapat direkrut

    //Kamus
    unit tUnit;
    POINT ValUndefP;
    FILE *f;

    //Algoritma

    //Inisialisasi
    MakeEmptyArray(unitRec);
    ValUndefP = MakePOINT(-1, -1);

    STARTKATA("unit.txt");
    BacaUnit(&tUnit);
    AddElmtArray(unitRec, tUnit);
    ADVKATA();
    BacaUnit(&tUnit);
    AddElmtArray(unitRec, tUnit);
    ADVKATA();
    BacaUnit(&tUnit);
    AddElmtArray(unitRec, tUnit);
    ADVKATA();
    //EOP;
}

void InitVillage(int M, int N, villageList *vL) {
// I.S. M dan N terdefinisi dan vL dalam keadaan empty
// F.S. vL berisi village-village baru yang telah diciptakan

    //Kamus
    int sumVil, X, Y, i;
    POINT P;
    villageaddress Pv;
    village vtemp;
    boolean found;

    //Algoritma
    sumVil = (N * M)/13;

    srand(time(NULL));
    
    i = 1;
    
    while (i <= sumVil) {
        do {
            Y = (int) rand() % N;
        } while (Y <= 3 || Y >= (Y - 3));

        X = (int) rand() % M;

        P = MakePOINT(X, Y);
        Pv = VillageFirst(*vL);

        found = false;

        while (Pv != Nil && !found) {
            found = (EQPOINT(LokasiVillage(VillageInfo(Pv)), P));
        }

        if (!found) {   //jika lokasi unik
            LokasiVillage(vtemp) = P;
            i++;
            InsVFirstVillage(vL, vtemp);
        }
    }
}

void InitLocKing (int M, int N, pemain *pR, pemain *pB) {
//I.S. M, N, pR dan pB terdefinisi (M itu yang X (yang kebawah) N itu yang Y (yang ke samping))
//F.S. lokasi unit king pada masing-masing list linier unit player tergantikan (jadi benar)
    //Kamus
    unitaddress P;

    //Algoritma
    //First unit merupakan raja/king
    P = UnitFirst(listUnitP(*pR));
    location(UnitInfo(P)) = MakePOINT(M - 2, 1);
    P = UnitFirst(listUnitP(*pB));
    location(UnitInfo(P)) = MakePOINT(1 , N - 2);
}