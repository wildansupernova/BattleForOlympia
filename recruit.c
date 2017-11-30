//recruit

#include <stdio.h>
#include "boolean.h"
#include "recruit.h"
#include "point.h"
#include "matriksPeta.h"
#include "stackt.h"

boolean cekKingIntower(MATRIKS M,unit U)
//F.S : true apabila king berada di tower dan sebaliknya
{
	//kamus lokal
	
	//algoritma
	return (infoJPetak(M,U.lokasi.X,U.lokasi.Y)=='T');
	
}

void recplayer1(unitList *L, MATRIKS M , TabUnit TabPemain, char turnNow, unit U, pemain *P, Stack *S)
/* I.S. : list unit terdefinisi */
//* F.S. : akan melakukan perekrutan 
//		  jika unit itu hanya king, king harus berada di tower, 
//		  king boleh merekrut apabila ada suatu castle yang tidak
//		  ditempati */

{
	//kamus lokal
	POINT titik;
	int z;
	boolean found;
	//algoritma
	//ngecek king ada di tower
	if (!cekKingIntower(M,U))
	{
		printf("The king is not in tower\n");
	} else {
		// printf("1. lala\n");
	
	//ngecek misalnya semua castle full
		if (isAllCastleFull(turnNow, M) || harta(*P) < 4) 
		{
			printf("All castle is full! or your money less than 4\n");
		} else 
		{
			found = false;
			do
			{
				InputPoint(&titik, "Enter coordinate of empty castle:");
				if (infoJPetak(M, Absis(titik), Ordinat(titik)) != 'C' && infomilik(M, Absis(titik), Ordinat(titik)) != turnNow)
				{
					printf("That place is not your castle\n");
				} else if (infounitpetak(M, Absis(titik), Ordinat(titik)) != Nil) {
					printf("That castle is not empty\n");
				} else {
					found = true;
				}
			} while(!found);
			// titiknya untuk map sudah dipastikan kosong
			
			printf("\n===List of recruits===\n");
			PrintArray(TabPemain);
			//print list recruit
			printf("\n");
			do
			{
				InputInteger(&z, "Enter no. of unit you want to recruit:");
				U = ElmtAR(TabPemain, z);
				if (jenisUnit(U) == 'A' && harta(*P) >= harga(U))
				{
				printf("You have recruited an archer!"); 
				harta(*P) = harta(*P) - harga(U);
				} else if (jenisUnit(U) == 'S' && harta(*P) >= harga(U))
				{
					printf("You have recruited a swordman!");
					harta(*P)= harta(*P)-harga(U);
				} else if (jenisUnit(U) == 'W' && harta(*P) >= harga(U))
				{
					printf("You have recruited a white mage!");
					harta(*P)= harta(*P)-harga(U);	
				} else if ( z<1 || z>3 ){
					printf("Your input is not valid\n");
				}
			} while (z<1 || z>3);	
			//z >= 1 and z <= 3
			if (harta(*P)<harga(U)){
				printf("Your money does not enough to buy it\n");
			} else {
				CreateEmptySt(S);
			}
			
			unitmilik(U) = turnNow;
			location(U) = MakePOINT(Absis(titik),Ordinat(titik));
			InsVFirstUnit(L,U);
		}	
	}
}

boolean isAllCastleFull(char turnNow, MATRIKS M)
//F.S : mengirimkan true jika semua castle telah ditempati oleh unit
{
	//kamus lokal
	int count = 0;
	
	//algoritma
	if (turnNow == 'R') {
		if(infounitpetak(M, NBrsEff(M) - 2, 0) != Nil) {
			count++;
		} if (infounitpetak(M, NBrsEff(M) - 3, 1) != Nil) {
			count++;
		} if (infounitpetak(M, NBrsEff(M) - 2, 2) != Nil) {
			count++;
		} if(infounitpetak(M, NBrsEff(M) - 1, 1) != Nil) {
			count++;
		}
	} else if(turnNow == 'B') {
		if (infounitpetak(M, 0, NKolEff(M) - 2) != Nil) {
			count++;
		} if (infounitpetak(M, 1, NKolEff(M) - 3) != Nil) {
			count++;
		} if (infounitpetak(M, 1, NKolEff(M) - 1) != Nil) {
			count++;
		} if (infounitpetak(M, 2, NKolEff(M) - 2) != Nil) {
			count++;
		}
	}

	return (count==4);
}
//posisi pemain di update
//kepemilikan unit belum di update
//update harga

