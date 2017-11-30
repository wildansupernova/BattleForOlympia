/*nama file: move.c*/ 
/*implementasi move.h*/

#include <stdio.h>
#include <stdlib.h>
#include "move.h"
#include "mesinkatainput.h"
#include "mesinkata.h"

//unitaddress SearchUnit (unitList L, unitinfotype X)
/* Mencari apakah ada elemen list dengan Info(P)= X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
/*{
	boolean found;
	unitaddress P;
	
	found = false;
	P = UnitFirst(L);
	while(P != Nil && !found)
	{
		if(UnitInfo(P).jenis == X.jenis && UnitInfo(P).kepemilikanUnit == X.kepemilikanUnit)
		{
			found = true;
		}else{
			P = UnitNext(P);
		}
	}
	if(found)
	{
		return P;
	}else{
		return Nil;
	} 
}*/

boolean isBlocked(MATRIKS M, POINT P, unitaddress a)
/* Menghasilkan false jika petak yang dilewati ada penghalang, true jika tidak */ 
{
	POINT T;
	int i,j;
	boolean blocked;
	
	i = UnitInfo(a).lokasi.X;
	j = UnitInfo(a).lokasi.Y;
	Absis(T) = Absis(P);
	Ordinat(T) = Ordinat(P);
	blocked = false;
	/* Cek titik tujuan apakah sudah ada isinya */
	if(infounitpetak(M,Absis(T),Ordinat(T)) != Nil)
	{
		blocked = true;
	}
	/*Cek apakah terhalang unit lawan*/
	if(!blocked)
	{
		if(Ordinat(P) > j )
		{
			while(j + 1 <= Ordinat(P) && !blocked)
			{
				Absis(T) = i;
				Ordinat(T) = j + 1;
				if(infounitpetak(M,Absis(T),Ordinat(T)) != Nil)
				{
					if(!isFriendlyUnit(M,Absis(T),Ordinat(T),a))
					{
						blocked = true;
					}else{
						j++;
					}
				}else{
					j++;
				}
			}
		}else{
			while(j - 1 >= Ordinat(P) && !blocked)
			{
				Absis(T) = i;
				Ordinat(T) = j - 1;
				if(infounitpetak(M,Absis(T),Ordinat(T)) != Nil)
				{
					if(!isFriendlyUnit(M,Absis(T),Ordinat(T),a))
					{
						blocked = true;
					}
					else{
						j--;
					}
				}else{
					j--;
				}
			}
		}
		if(Absis(P) > i)
		{
			while(i + 1 <= Absis(P) && !blocked)
			{
				Absis(T) = i + 1;
				Ordinat(T) = j;
				if(infounitpetak(M,Absis(T),Ordinat(T)) != Nil)
				{
					if(!isFriendlyUnit(M,Absis(T),Ordinat(T),a))
					{
						blocked = true;
					}else{
						i++;
					}
				}else{
					i++;
				}
			}	
		}else{
			while(i - 1 >= Absis(P) && !blocked)
			{
				Absis(T) = i - 1;
				Ordinat(T) = j;
				if(infounitpetak(M,Absis(T),Ordinat(T)) != Nil)
				{
					if(!isFriendlyUnit(M,Absis(T),Ordinat(T),a))
					{
						blocked = true;
					}else{
						i--;
					}
				}else{
					i--;
				}
			}
		}		
		if(blocked)
		{
			i = UnitInfo(a).lokasi.X;
			j = UnitInfo(a).lokasi.Y;
			blocked = false;
			if(Absis(P) > i)
			{
				while(i + 1 <= Absis(P) && !blocked)
				{
					Absis(T) = i + 1;
					Ordinat(T) = j;
					if(infounitpetak(M,Absis(T),Ordinat(T)) != Nil)
					{
						if(!isFriendlyUnit(M,Absis(T),Ordinat(T),a))
						{
							blocked = true;
						}else{
							i++;
						}
					}else{
						i++;
					}
				}	
			}else{
				while(i - 1 >= Absis(P) && !blocked)
				{
					Absis(T) = i - 1;
					Ordinat(T) = j;
					if(infounitpetak(M,Absis(T),Ordinat(T)) != Nil)
					{
						if(!isFriendlyUnit(M,Absis(T),Ordinat(T),a))
						{
							blocked = true;
						}else{
							i--;
						}
					}else{
						i--;
					}
				}
			}
			if(Ordinat(P) > j )
			{
				while(j + 1 <= Ordinat(P) && !blocked)
				{
					Absis(T) = i;
					Ordinat(T) = j + 1;
					if(infounitpetak(M,Absis(T),Ordinat(T)) != Nil)
					{
						if(!isFriendlyUnit(M,Absis(T),Ordinat(T),a))
						{
							blocked = true;
						}else{
							j++;
						}
					}else{
						j++;
					}
				}
			}else{
				while(j - 1 >= Ordinat(P) && !blocked)
				{
					Absis(T) = i;
					Ordinat(T) = j - 1;
					if(infounitpetak(M,Absis(T),Ordinat(T)) != Nil)
					{
						if(!isFriendlyUnit(M,Absis(T),Ordinat(T),a))
						{
							blocked = true;
						}else{
							j--;
						}
					}else{
						j--;
					}
				}
			}
		}
	}
	return blocked;
}
	
boolean SearchLoc(unitList L, POINT T)
/* Mencari apakah ada unit dalam elemen list yang berada di T */
/* Mengirimkan true jika ada, false jika tidak ada */
{
	unitaddress P = UnitFirst(L);
	boolean found=false;
	
	while((!found) &&(P != Nil))
	{
		if (UnitInfo(P).lokasi.X == Absis(T) && UnitInfo(P).lokasi.Y == Ordinat(T))
		{
			found = true;
		}else{
			P = UnitNext(P);
		}
	}
	return found;
}


boolean isFriendlyUnit(MATRIKS M, int i, int j, unitaddress a)
/* Menghasilkan true jika petak berisi unit yang kepemilikannya sama, false jika 
 * berisi unit milik lawan */
{
	return unitmilik(UnitInfo(infounitpetak(M,i,j))) == unitmilik(UnitInfo(a));
}
boolean isMoveLegal(MATRIKS M, POINT P, unitList L1, unitList L2, unitaddress a)
/* Menghasilkan true jika pergerakan unit tersebut tidak menyalahi aturan movePoint,
 * false jika tidak */ 
{
	
	if(Absis(P) <= (NBrsEff(M) - 1) && Absis(P) >= 0 && Ordinat(P) <= (NKolEff(M) -1) && Ordinat(P) >= 0)
	{
		if(UnitInfo(a).movePoint - CountMove(P,a) >= 0)
		{
			if(!isBlocked(M,P,a))
			{
				return true;
			}else{
				return false;
			}
		}else{
			return false;
		}	
	}else{
		return false;
	}
}	 

int CountMove(POINT P, unitaddress a)
/* Menghitung Vektor MovePoint */
{
	return (abs(Absis(P) - Absis(location(UnitInfo(a)))) + abs(Ordinat(P) - Ordinat(location(UnitInfo(a)))));
}

void UpdateUnit(POINT P, unitaddress a)
/* I.S. U terdefinisi, isMoveLegal true */
/* F.S. Menyimpan posisi unit dan movement point terupdate setelah move */
{	
	moveP(UnitInfo(a)) -= CountMove(P,a);
	Absis(location(UnitInfo(a))) = Absis(P);
	Ordinat(location(UnitInfo(a))) = Ordinat(P); 
}

void MoveUnit(MATRIKS M, Stack *S, unitaddress a, char color, unitList UL1, unitList UL2, villageList *L1, villageList *L2, villageList *L3)
/* I.S. M, S, a, color terdefinisi */
/* F.S. Posisi unit diupdate, stack terisi point koordinat unit, 
 * movePoint dari unit berkurang atau habis */
{ 
	POINT P,T;
	int C;
	
	printMatriksWithPager(M, UL1, UL2, a, &C);
	if (C != 0) {
		InputPoint(&P, "Please enter cell's coordinate x y:");
		while(!isMoveLegal(M,P,UL1,UL2,a))
		{
			printf("You can not move there\n");
			InputPoint(&P, "Please enter cell's coordinate x y:");
		}
		if(!IsFullSt(*S))
		{
			Push(S,UnitInfo(a).lokasi);
		}else{
			Pop(S,&T);
			CreateEmptySt(S);
			Push(S,T);
			Push(S,UnitInfo(a).lokasi);
		}
		UpdateUnit(P, a);
		if(isVillage(M,P))
		{
			VillageIsMine(a, L1, L2, L3, color);
			CreateEmptySt(S);
		}
		printf("You have successfully moved to (%d, %d)\n", Absis(P), Ordinat(P));
	} else {
		printf("There is not place available\n");
	}	
}

void Undo(Stack *S, unitaddress a)
/* I.S. Stack bisa kosong atau terisi, unitaddress terdefinisi */
/* F.S. Unit kembali ke keadaan state sebelumnya */
{
	POINT P,T;
	
	if(IsEmptySt(*S))
	{
		printf("\nYou can't undo anymore!\n");
	}else{
		Absis(P) = UnitInfo(a).lokasi.X;
		Ordinat(P) = UnitInfo(a).lokasi.Y;
		Pop(S,&T);
		UnitInfo(a).lokasi.X = Absis(T);
		UnitInfo(a).lokasi.Y = Ordinat(T);
		UnitInfo(a).movePoint = UnitInfo(a).movePoint + CountMove(P, a);
	}
}

boolean isVillage(MATRIKS M, POINT P)
/*Mengecek apakah petak yang dituju merupakan village */
{
	return infoJPetak(M,Absis(P),Ordinat(P)) == 'V';
}

void VillageIsMine(unitaddress a, villageList *L1, villageList *L2, villageList *Universal, char color)
/* I.S. Village tanpa kepemilikan atau milik lawan */
/* F.S. Village menjadi milik pemain yang unitnya menempati village tersebut */
{	
	villageaddress Prec, P;
	boolean Found = false;
	
	moveP(UnitInfo(a)) = 0;
	
	if (color == 'R') {
		CariVillage(*L2, a, &Prec, &P);
		if(P != Nil)
		{
			if (Prec == Nil) {
				VillageFirst(*Universal) = VillageNext(P);
			} else {
				VillageNext(Prec) = VillageNext(P);
			}
			
			VillageNext(P) = Nil;
			VillageInfo(P).kepemilikan = color;
			InsertFirstVillage(L1, P);
			Found = true;
		}
		
	} else {
		CariVillage(*L1, a, &Prec, &P);
		if(P != Nil)
		{
			Found = true;
			if (Prec == Nil) {
				VillageFirst(*L1) = VillageNext(P);
			} else {
				VillageNext(Prec) = VillageNext(P);
			}
		
			VillageNext(P) = Nil;	
			VillageInfo(P).kepemilikan = color;
			InsertFirstVillage(L2, P);
		}/*Di list player 1 nggak ketemu, coba cari di list player 2 */
	}
	
	if (!Found) /*Di list player 2 nggak ketemu juga, berarti village ini belum ada yang punya */{
		CariVillage(*Universal, a, &Prec, &P);
		/* sudah pasti ketemu, jadi nggak mungkin P nya Nil */
		if (Prec == Nil) {
			VillageFirst(*Universal) = VillageNext(P);
		} else {
			VillageNext(Prec) = VillageNext(P);
		}
		
		VillageNext(P) = Nil;
		MilikVillage(VillageInfo(P)) = color;
		if (color == 'B') {
			InsertFirstVillage(L2, P);
		} else {
			InsertFirstVillage(L1, P);
		}
	}
}

void CariVillage (villageList L, unitaddress a, villageaddress *Prec, villageaddress *P)
/* Mencari apakah ada elemen list yang berinfo T */
/* Mengirimkan address jika ada, nil jika tidak ada */
{
    boolean Found;

	*Prec = Nil;
	*P = VillageFirst(L);
    Found = false;
    while ((*P != Nil) && (!Found)) 
    {
        if(EQPOINT(LokasiVillage(VillageInfo(*P)), location(UnitInfo(a)))) 
        {
            Found = true;
        }else{
			*Prec = *P;
			*P = VillageNext(*P);
		}
    }
}
