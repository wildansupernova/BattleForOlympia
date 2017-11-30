#ifndef adtunit_H
#define adtunit_H

#include "point.h"
#include "boolean.h"
#include "stackt.h"

typedef struct {
	char jenis; // '0' Kalau kosong
	char kepemilikanUnit;
	int maxHealth;
	int health;
	int attack;
	int maxMovePoint;
	int movePoint;
	int tipeSerangan; // Melee = 1, Ranged = 0
	boolean attackChance;
	POINT lokasi;
	int price;
	boolean isSelected;
	int kemungkinanTerserang;
} unit;


/* Selektor UNit */
#define jenisUnit(P) 	(P).jenis
#define unitmilik(P) 	(P).kepemilikanUnit
#define maxH(P) 		(P).maxHealth
#define Health(P) 		(P).health
#define Attack(P) 		(P).attack
#define maxMove(P) 		(P).maxMovePoint
#define moveP(P)		(P).movePoint
#define AtkType(P) 		(P).tipeSerangan
#define atkchance(P) 	(P).attackChance
#define location(P) 	(P).lokasi
#define harga(P) 		(P).price
#define selected(P) 	(P).isSelected
#define prob(P)			(P).kemungkinanTerserang

#endif