#ifndef turn_H
#define turn_H

#include "boolean.h"
#include "stackt.h"
#include "queue.h"
#include "pemain.h"

void EndTurn(Queue *turnQueue, Stack *stackUndo, pemain *pR, pemain *pB, char *turnNow);
// I.S. turnQueue, stackUndo, pR, pB terdefinisi
// F.S. turnQueue, stackUndo, pR, pB terupdate dan unitNow berisi unit yang sedang jalan pada awal turn (re: King)

void HealUnit(POINT petak, pemain *P);
// I.S. petak terdefinisi dan *P menyimpan list linier unit yang telah terdefinisi
// F.S. unit pada petak tersebut ter-heal

#endif