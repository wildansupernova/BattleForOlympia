#ifndef adtVillage_H
#define adtVillage_H

#include "point.h"

typedef struct {
	POINT lokasi;
	char kepemilikan; //R untuk Red, B untuk Blue dan 0 untuk tidak berpemiliki
} village;

/* Selektor Village */
#define LokasiVillage(P) 	(P).lokasi
#define MilikVillage(P)		(P).kepemilikan

#endif