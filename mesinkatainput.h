/* File: mesinkata.h */
/* Definisi Mesin Kata: Model Akuisisi Versi I */

#ifndef __MESINKATA_INPUT_H__
#define __MESINKATA_INPUT_H__

#include "boolean.h"
#include "point.h"
#include "mesinkarinput.h"

#define BLANK ' '
#define NEWLINE '\n'

/* State Mesin Kata */
extern boolean EndKataInput;
extern Kata CKataInput;

void IgnoreBlankInput();
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang 
   F.S. : CC ≠ BLANK atau CC = MARK */

void STARTKATAINPUT();
/* I.S. : CC sembarang 
   F.S. : EndKata = true, dan CC = MARK; 
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */

void ADVKATAINPUT();
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi 
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi, 
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKata = true.		  
   Proses : Akuisisi kata menggunakan procedure SalinKata */

void SalinKataInput();
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi; 
          CC = BLANK atau CC = MARK; 
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */

void InputPoint(POINT *P, char* katakata);
// I.S. bebas
// F.S. *P terdefinisi yang berisikan point sesuai dengan input yang telah diberikan

void InputInteger(int *X, char* katakata);
// I.S. bebas
// F.S. *P terdefinisi yang berisikan integer sesuai dengan input yang telah diberikan

void InputKata(Kata *inKata, char* katakata);
// I.S. bebas
// F.S. *P terdefinisi yang berisikan Kata sesuai dengan input yang telah diberikan

boolean IsKataNumber (Kata CKataInput);
// menghasilkan true ketika kata tersebut merupakan angka

#endif
