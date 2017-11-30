#include "mesinkatainput.h"
#include "mesinkata.h"
#include <stdio.h>

boolean EndKataInput;
Kata CKataInput;

void IgnoreBlankInput()
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang 
   F.S. : CC ≠ BLANK atau CC = MARK */
{
    //Kamus

    //ALgoritma
    while (((CC == BLANK) || (CC == NEWLINE)) && (CC != NILL)){
        ADVINPUT();
    }
}

void STARTKATAINPUT()
/* I.S. : CC sembarang 
   F.S. : EndKataInput = true, dan CC = MARK; 
          atau EndKataInput = false, CKataInput adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */
{
    //Kamus

    //Algoritma
    STARTINPUT();
    IgnoreBlankInput();
    if (CC == NILL) {
        EndKataInput = true;
    } else {
        EndKataInput = false;
        SalinKataInput();
    }
}
void ADVKATAINPUT()
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi 
   F.S. : CKataInput adalah kata terakhir yang sudah diakuisisi, 
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKataInput = true.		  
   Proses : Akuisisi kata menggunakan procedure SalinKata */
{
    //Kamus

    //ALgoritma
    IgnoreBlankInput();
    if (CC == NILL) {
        EndKataInput = true;
    } else {
        SalinKataInput();
    }
}

void SalinKataInput()
/* Mengakuisisi kata, menyimpan dalam CKataInput
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKataInput berisi kata yang sudah diakuisisi; 
          CC = BLANK atau CC = MARK; 
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
{
    //Kamus
    int i;

    //Algoritma
    i = 1;
    while ((CC != NILL) && (CC != BLANK) && (CC != NEWLINE) && (i <= NMax)) {
        CKataInput.TabKata[i] = CC;
        i++;
        ADVINPUT();
    }
    // CC = MARK atau CC = BLANK
    CKataInput.Length = i-1;
}

void InputPoint(POINT *P, char* katakata) {
// I.S. bebas
// F.S. *P terdefinisi yang berisikan point sesuai dengan input yang telah diberikan
    //Kamus
    int X, Y;
    boolean inBenar = false;

    //Algoritma
    do {
        printf("%s ", katakata);
        fgets(s_input, 200, stdin);
        STARTKATAINPUT();
        if (!EndKataInput) {
            if (IsKataNumber(CKataInput)) {
                X = KataToInt(CKataInput);
                ADVKATAINPUT();
                if (!EndKataInput) {
                    if (IsKataNumber(CKataInput)) {
                        Y = KataToInt(CKataInput);
                        ADVKATAINPUT();
                        if (EndKataInput) {
                            inBenar = true;
                        } 
                    }
                }
            }
        }
        if (!inBenar) {
            printf("input must be point <int> <int>\n");    
        }
    } while (!inBenar);

    *P = MakePOINT(X, Y);
}

void InputInteger(int *X, char* katakata) {
// I.S. bebas
// F.S. *P terdefinisi yang berisikan integer sesuai dengan input yang telah diberikan
    //Kamus
    boolean inBenar = false;

    //Algoritma
    do {
        printf("%s ", katakata);
        fgets(s_input, 200, stdin);
        STARTKATAINPUT();
        if (!EndKataInput) {
            if (IsKataNumber(CKataInput)) {
                *X = KataToInt(CKataInput);
                ADVKATAINPUT();
                if (EndKataInput) {
                    inBenar = true;
                }
            }
        }
        if (!inBenar) {
            printf("input must be <int>\n");
        }
    } while (!inBenar);
}

void InputKata(Kata *inKata, char* katakata) {
// I.S. bebas
// F.S. *P terdefinisi yang berisikan Kata sesuai dengan input yang telah diberikan
    //Kamus
    boolean inBenar = false;

    //Algoritma
    do {
        printf("%s ", katakata);
        fgets(s_input, 200, stdin);
        STARTKATAINPUT();
        if (!EndKataInput) {
            *inKata = CKataInput;
            ADVKATAINPUT();
            if (EndKataInput) {
                inBenar = true;
            }
        }
        if (!inBenar) {
            printf("input must be <string>\n");
        }    
    } while (!inBenar);
}

// void InputDoubleInteger(int *X, int *Y) {
// // I.S. bebas
// // F.S. *P terdefinisi yang berisikan 2 integer sesuai dengan input yang telah diberikan
//     //Kamus
//     boolean inBenar = false;

//     //Algoritma
//     do {
//         fgets(s_input, 198, stdin);
//         STARTKATAINPUT();
//         if (!EndKataInput) {
//             if (IsKataNumber(CKataInput)) {
//                 *X = KataToInt(CKataInput);
//                 ADVKATAINPUT();
//                 if (IsKataNumber(CKataInput)) {
//                     *Y = KataToInt(CKataInput);
//                     if (EndKataInput) {
//                         inBenar = true;
//                     }
//                 }
//             }
//         }
//         if (!inBenar) {
//             printf("input must be <int> <int>\n");
//         }
//     } while (!inBenar);
// }

boolean IsKataNumber (Kata CKataInput) {
// menghasilkan true ketika kata tersebut merupakan angka
    //Kamus
    int i;
    boolean isAngka = true;

    //Algoritma
    if ((chr(CKataInput, 1) == '-') || (((chr(CKataInput, 1)) - '0') >= 0 && ((chr(CKataInput, 1)) - '0') <= 9)) {
        if ((chr(CKataInput, 1) == '-')) {
            i = 2;
        } else {
            i = 1;
        }

        for (; i <= length(CKataInput) && isAngka; i++) {
            isAngka = ((chr(CKataInput, i) - '0') >= 0) && ((chr(CKataInput, i) - '0') <= 9);
        }
    } else {
        isAngka = false;
    }
    return isAngka;
}
