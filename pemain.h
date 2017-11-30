#ifndef pemain_H
#define pemain_H

#include "point.h"
#include "listlinierunit.h"
#include "listliniervillage.h"
#include "boolean.h"

typedef struct{
	//char nomorPlayer;// 1 atau 2
	char warna; //bisa R bisa B, R untuk  merah , b untuk biru. 
	int kekayaan;
	int income;
	int upkeep;
	unitList listUnit;
	villageList listVillage;
	//List Village;   <<<Bingung ini tipe datanya apa

} pemain;

//Selektor
#define warnaP(P)		(P).warna
#define harta(P)		(P).kekayaan
#define incomeP(P)		(P).income
#define upkeepP(P)		(P).upkeep
#define listUnitP(P)	(P).listUnit
#define listVillageP(P)	(P).listVillage

#endif