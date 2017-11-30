/* File: mesinkarinput.h */
/* Definisi Mesin Karakter Input */

#ifndef __MESIN_KAR_INPUT_H_
#define __MESIN_KAR_INPUT_H_

#include "mesinkar.h"

#define NILL '\0'
#define BLANK ' '
#define NEWLINE '\n'

char s_input[201];

void STARTINPUT();
/* Mesin siap dioperasikan. s_input disiapkan untuk dibaca.
   Karakter pertama yang ada pada s_input posisinya adalah pada jendela.
   I.S. : sembarang
   F.S. : CC adalah karakter pertama pada s_input
          Jika CC != MARK maka EOP akan padam (false)
          Jika CC = MARK maka EOP akan menyala (true) */

void ADVINPUT();
/* s_input dimajukan satu karakter. 
   I.S. : Karakter pada jendela = CC, CC != MARK
   F.S. : CC adalah karakter berikutnya dari CC yang lama, 
          CC mungkin = MARK
          Jika  CC = MARK maka EOP akan menyala (true) */

#endif
