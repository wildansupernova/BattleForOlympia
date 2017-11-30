#include <stdio.h>
#include "matriksPeta.h"
#include "pcolor.c"
#include "listliniervillage.h"
#include "limits.h"
#include "move.h"

//NIM 13516012
//Nama Wildan Dicky Alnatara
//Tanggal 13 09 2017
//Topik praktikum : matriks
//Deskripsi buat adt matriks

/* NBrsEff <= 1 dan NKolEff <= 1 */
/* Indeks matriks yang digunakan: [BrsMin..BrsMax][KolMin..KolMax] */
/* Memori matriks yang dipakai selalu di "ujung kiri atas" */
#include "time.h"

//Beberapa Inisiasi
int generateRandomRange(int a,int b){
	//Generate random number
   time_t t;

    //   delay(1000);
   int range = b-a +1;
   int angkarandom = rand() % range; 
   return angkarandom + a; 
}


POINT koordinatRandom(MATRIKS m){
	//Mencari koordinat random
    int KoorX = generateRandomRange( GetFirstIdxKol(m) + 3,GetLastIdxKol(m)-3);
    int KoorY = generateRandomRange( GetFirstIdxBrs(m),GetLastIdxBrs(m));
    POINT out;
    Absis(out) = KoorY;
    Ordinat(out) = KoorX;
    return out;


}

void generateDesa(int n, villageList *L, MATRIKS m){
	//Generate DEsa otomatis dengan random
	int counter=0;
	while(counter<n){
		POINT randomnya ;
		randomnya = koordinatRandom(m);
		boolean ada = SearchKoordinatVillage(*L,randomnya);
		if (!ada){
			counter++;
			villageinfotype desayangdimasukin;
			MilikVillage(desayangdimasukin) = 'N';
			LokasiVillage(desayangdimasukin) = randomnya;
			InsVFirstVillage (L, desayangdimasukin);


		}
	}
}
void generateDesaNyesuainPeta(villageList *L, MATRIKS m){
    int KoorX = -(GetFirstIdxKol(m) + 3)+(GetLastIdxKol(m)-3)+1;
    int KoorY = NBrsEff(m);
	int jumlahvillage = ((KoorX*KoorY)*15)/100;	
	generateDesa(jumlahvillage,L,m);
}
/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */              
/* *** Konstruktor membentuk MATRIKS *** */
void infoPetak(MATRIKS m, int x, int y){
	printf("== Cell Info ==\n");
	switch(infoJPetak(m,x,y)){
		case 'N':
			printf("Normal\n");
			break;
		case 'V': 
			printf("Village\n");
			switch(infomilik(m,x,y)){
				case 'N' : printf("Not owned by anyone\n");
					break;
				case 'R' : printf("Owned by player 1\n");
					break;
				case 'B' : printf("Owned by Player 2\n");
					break; 
			}
			break;
		case 'C' : 
			printf("Castle\n");
			switch(infomilik(m,x,y)){
				case 'N' : printf("Not owned by anyone\n");
					break;
				case 'R' : printf("Owned by player 1\n");
					break;
				case 'B' : printf("Owned by Player 2\n");
					break; 
			}
			break;
						
	}
	printf("== Unit Info == \n");
	unitaddress c = infounitpetak(m,x,y);
	if (c == Nil){
		printf("There is no unit\n");

	} else{
		unit thispetak = UnitInfo(c);
		switch(jenisUnit(thispetak)){
			case 'S':printf("Swordsman\n");
				break;
			case 'A':printf("Swordsman\n");
				break;
			case 'K':printf("King\n");
				break;
			case 'W':printf("Whitemage\n");
				break;
					
		}
		switch(unitmilik(thispetak)){
			case 'N' : printf("Not owned by anyone\n");
					break;
			case 'R' : printf("Owned by player 1\n");
					break;
			case 'B' : printf("Owned by Player 2\n");
					break; 
		}
		printf("Health %d/%d | ATK %d \n",Health(thispetak),maxH(thispetak),Attack(thispetak));
	}


}
void statusInfo(char giliran,pemain a){
	//FUngsi dari procesdure ini adalah menampilkan status
	int konversi;
	if(giliran == 'R'){
		konversi = 1;
	} else{
		konversi = 2; 
	}
	printf("Player %c's Turn\n", giliran);
	printf("Cash: %dG | Income: %dG | Upkeep: %dG\n",a.kekayaan,a.income,a.upkeep);
	unitaddress def = UnitFirst(a.listUnit);

	while (def!=Nil){
			unit inf  = UnitInfo(def); 
			if (selected(inf)){
				switch(jenisUnit(inf)){
					case 'K':
						printf("Unit: King(%d,%d) | ", Absis(location(inf)),Ordinat(location(inf)));
						break;
					case 'A':
						printf("Unit: Archer(%d,%d) | ", Absis(location(inf)),Ordinat(location(inf)));
						break;					
					case 'S':
						printf("Unit: Swordman(%d,%d) | ", Absis(location(inf)),Ordinat(location(inf)));
						break;
					case 'W':
						printf("Unit: Whitemage(%d,%d) | ", Absis(location(inf)),Ordinat(location(inf)));
						break;							
				}
				printf("Health %d/%d | ",Health(inf),maxH(inf));
				printf("Movement Point: %d | ",moveP(inf));
				printf("Can attack: ");
				if(atkchance(inf)){
					printf("Yes");
				} else{
					printf("No");
				}

				printf("\n");

			} else{

			}
			def=UnitNext(def);

	}
}


void MakeNormalMATRIKS (int NB, int NK, MATRIKS * M){
/* Membentuk sebuah MATRIKS "kosong" yang siap diisi berukuran NB x NK di "ujung kiri" memori */
/* I.S. NB dan NK adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks M sesuai dengan definisi di atas terbentuk */
	NBrsEff(*M)=NB;
	NKolEff(*M)=NK;
	
	int j,i;
	for (i = GetFirstIdxBrs(*M);i<=GetLastIdxBrs(*M);i++){
		for(j = GetFirstIdxKol(*M);j<=GetLastIdxKol(*M);j++){
			Elmt(*M,i,j).jenisPetak = 'N';
			Absis(Elmt(*M,i,j).p) = j;
			Ordinat (Elmt(*M,i,j).p) = i;
			infounitpetak (*M,i,j)= Nil;
		}
	}


}

void InitializeCastleTemple(MATRIKS *m){
//I.S Usahakan panggil fungsi ini sesudah memanggil fungsi makenormalmatriks untuk menginisiasi
//matriks mnya agara tidak bocor
//F.S sudah ada templenya serta castle mili player R dan B

	int kolompertama=GetFirstIdxKol(*m);
	int barisakhir=GetLastIdxBrs(*m);
	int kolomakhir=GetLastIdxKol(*m);
	int barispertama=GetFirstIdxBrs(*m);

	//Set Tower Red Player
	infoJPetak(*m,barisakhir-1,kolompertama+1) = 'T';
	infomilik(*m,barisakhir-1,kolompertama+1) = 'R';
	//Set Tower Blue Player
	infoJPetak(*m,barispertama+1,kolomakhir-1) = 'T';
	infomilik(*m,barispertama+1,kolomakhir-1) = 'B';
	//Set Red Castle
		//Bawah
		infoJPetak(*m,barisakhir,kolompertama+1) = 'C';
		infomilik(*m,barisakhir,kolompertama+1) = 'R';
		//Atas
		infoJPetak(*m,barisakhir-2,kolompertama+1) = 'C';
		infomilik(*m,barisakhir-2,kolompertama+1) = 'R';
		//Kiri
		infoJPetak(*m,barisakhir-1,kolompertama) = 'C';
		infomilik(*m,barisakhir-1,kolompertama) = 'R';		
		//Kanan
		infoJPetak(*m,barisakhir-1,kolompertama+2) = 'C';
		infomilik(*m,barisakhir-1,kolompertama+2) = 'R';	
	//Set Blue Castle
		//Bawah
		infoJPetak(*m,barispertama+2,kolomakhir-1) = 'C';
		infomilik(*m,barispertama+2,kolomakhir-1) = 'B';
		//Atas
		infoJPetak(*m,barispertama,kolomakhir-1) = 'C';
		infomilik(*m,barispertama,kolomakhir-1) = 'B';
		//Kiri
		infoJPetak(*m,barispertama+1,kolomakhir-2) = 'C';
		infomilik(*m,barispertama+1,kolomakhir-2) = 'B';	
		//Kanan
		infoJPetak(*m,barispertama+1,kolomakhir) = 'C';
		infomilik(*m,barispertama+1,kolomakhir) = 'B';		
	}

void gambarunit(MATRIKS *m,unitList a){
	unitaddress p = UnitFirst(a);
	while(p!=Nil){
		POINT p1 = location(UnitInfo(p));
		infounitpetak(*m,Absis(p1),Ordinat(p1))= p;
		p=UnitNext(p);
		
	}
}
void gambarvillage(MATRIKS *m,villageList b,char kepunyaan){
	villageaddress p = VillageFirst(b);
	while(p!=Nil){
		POINT a = LokasiVillage(VillageInfo(p));
		infoJPetak(*m,Absis(a),Ordinat(a))= 'V';
		infomilik(*m,Absis(a),Ordinat(a)) = kepunyaan;
		p=VillageNext(p);
	}
}
void Gambar(MATRIKS *m,unitList r,unitList b,villageList vr,villageList vb,villageList vn){
	MakeNormalMATRIKS(NBrsEff(*m),NKolEff(*m),m);
	InitializeCastleTemple(m);
	gambarunit(m,r);
	gambarunit(m,b);
	gambarvillage(m,vr,'R');
	gambarvillage(m,vb,'B');
	gambarvillage(m,vn,'N');

}
void MakeMATRIKS (int NB, int NK, MATRIKS * M){
/* Membentuk sebuah MATRIKS "kosong" yang siap diisi berukuran NB x NK di "ujung kiri" memori */
/* I.S. NB dan NK adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks M sesuai dengan definisi di atas terbentuk */
	NBrsEff(*M)=NB;
	NKolEff(*M)=NK;
	int j,i;

	

}
/* *** Nampilin ke layar *** */

void printMatriks(MATRIKS m){
	int i,j;
	// MEnghitung maks digit baris
	int digitbar;
		if (GetLastIdxBrs(m)<=9){
			digitbar = 1;
		} else if (GetLastIdxBrs(m)>9 && (GetLastIdxBrs(m)<=99)) {
			digitbar = 2;
		} else{
			//printf("");
			digitbar = 3;
		}
	for(int i = 1 ;i<=digitbar;i++){
		printf(" ");
	}
	////////////////
	//mEMBUAT PRINT ANGKA
	for(int i = GetFirstIdxKol(m);i<=GetLastIdxKol(m);i++){
		if (i<=9){
			printf("  ");
			printf("%d",i);
			printf(" ");
		} else if (i>9 && (i<=99)) {
			printf(" ");
			printf("%d",i);
			printf(" ");			

		} else{
			//printf("");
			printf("%d",i);
			printf(" ");
		}

	}
	printf("\n");
	for(i =GetFirstIdxBrs(m);i<=GetLastIdxBrs(m);i++){
		for(int l = 1 ;l<=digitbar;l++){
			printf(" ");
		}		
		//Membuat Garis lurus bintang;
		for(j=1;j<=(NKolEff(m)*4)+1;j++){
			printf("*");
		}
		printf("\n");
		//****************************************************
		//Bagian menuliskan jenis petak
		for(int l = 1 ;l<=digitbar;l++){
			printf(" ");
		}
		for(j=GetFirstIdxBrs(m);j<=GetLastIdxKol(m);j++){
			if (Elmt(m,i,j).jenisPetak=='N'){
				printf("*   ");
			} else {
				printf("* ");
				if (infomilik(m,i,j)=='R'){
					print_red(infoJPetak(m,i,j));
				} else if (infomilik(m,i,j)=='B'){
					print_blue(infoJPetak(m,i,j));
				} else{
					putchar(infoJPetak(m,i,j));
				}
				printf(" ");
			}
		}
		printf("*\n");
		//Sub baris kedua untuk menapilkan unit jika ada
		printf("%d",i);
		if (i<=9){
			for(int l = 1 ;l<=digitbar-1;l++){
				printf(" ");
			}
		} else if (i>9 && (i<=99)) {
			for(int l = 1 ;l<=digitbar-2;l++){
				printf(" ");
			}
		} else{
			//printf("");
			for(int l = 1 ;l<=digitbar-3;l++){
				printf(" ");
			}			
		}
		for(j=GetFirstIdxBrs(m);j<=GetLastIdxKol(m);j++){
			if (infounitpetak(m,i,j)==Nil){
				printf("*   ");
			} else{
				printf("* ");
				unitaddress p = infounitpetak(m,i,j);
				if (selected(UnitInfo(p))){
					print_green(jenisUnit(UnitInfo(p)));
				} else{
					if (unitmilik(UnitInfo(infounitpetak(m,i,j)))=='R'){
						print_red(jenisUnit(UnitInfo(p)));
					} else{
						print_blue(jenisUnit(UnitInfo(p)));
					}
				}

				printf(" ");
			}
		}
		printf("*\n");
		for(int l = 1 ;l<=digitbar;l++){
			printf(" ");
		}
		for(j=GetFirstIdxBrs(m);j<=GetLastIdxKol(m);j++){
			
				printf("*   ");
			
		}
		printf("*\n");
	}
		for(int l = 1 ;l<=digitbar;l++){
			printf(" ");
		}
	for(j=1;j<=(NKolEff(m)*4)+1;j++){
		printf("*");
	}
	printf("\n");

}


void printMatriksWithPager(MATRIKS m,unitList L1, unitList L2, unitaddress a,int *keluaran){
	int i,j,counter=0;
	int digitbar;
		if (GetLastIdxBrs(m)<=9){
			digitbar = 1;
		} else if (GetLastIdxBrs(m)>9 && (GetLastIdxBrs(m)<=99)) {
			digitbar = 2;
		} else{
			//printf("");
			digitbar = 3;
		}
	for(int i = 1 ;i<=digitbar;i++){
		printf(" ");
	}
	////////////////
	//mEMBUAT PRINT ANGKA
	for(int i = GetFirstIdxKol(m);i<=GetLastIdxKol(m);i++){
		if (i<=9){
			printf("  ");
			printf("%d",i);
			printf(" ");
		} else if (i>9 && (i<=99)) {
			printf(" ");
			printf("%d",i);
			printf(" ");			

		} else{
			//printf("");
			printf("%d",i);
			printf(" ");
		}

	}
	printf("\n");
	for(i =GetFirstIdxBrs(m);i<=GetLastIdxBrs(m);i++){
		for(int l = 1 ;l<=digitbar;l++){
			printf(" ");
		}	
		//Membuat Garis lurus bintang;
		for(j=1;j<=(NKolEff(m)*4)+1;j++){
			printf("*");
		}
		printf("\n");
		//****************************************************
		//Bagian menuliskan jenis petak
		for(int l = 1 ;l<=digitbar;l++){
			printf(" ");
		}	
		for(j=GetFirstIdxBrs(m);j<=GetLastIdxKol(m);j++){
			if (Elmt(m,i,j).jenisPetak=='N'){
				printf("*   ");
			} else {
				printf("* ");
				if (infomilik(m,i,j)=='R'){
					print_red(infoJPetak(m,i,j));
				} else if (infomilik(m,i,j)=='B'){
					print_blue(infoJPetak(m,i,j));
				} else{
					putchar(infoJPetak(m,i,j));
				}
				printf(" ");
			}
		}
		printf("*\n");
		//Sub baris kedua untuk menapilkan unit jika ada
		printf("%d",i);
		if (i<=9){
			for(int l = 1 ;l<=digitbar-1;l++){
				printf(" ");
			}
		} else if (i>9 && (i<=99)) {
			for(int l = 1 ;l<=digitbar-2;l++){
				printf(" ");
			}
		} else{
			//printf("");
			for(int l = 1 ;l<=digitbar-3;l++){
				printf(" ");
			}			
		}
		for(j=GetFirstIdxBrs(m);j<=GetLastIdxKol(m);j++){
			if (infounitpetak(m,i,j)==Nil){
				printf("* ");
				POINT titiknya;
				Absis(titiknya) = i;
				Ordinat(titiknya) = j;
				if (isMoveLegal(m,titiknya,L1,L2,a)){
					printf("#");
					counter++;
				} else{
					printf(" ");
				}
				printf(" ");
			} else{
				printf("* ");
				unitaddress p = infounitpetak(m,i,j);
				if (selected(UnitInfo(p))){
					print_green(jenisUnit(UnitInfo(p)));
				} else{
					if (unitmilik(UnitInfo(infounitpetak(m,i,j)))=='R'){
						print_red(jenisUnit(UnitInfo(p)));
					} else{
						print_blue(jenisUnit(UnitInfo(p)));
					}
				}

				printf(" ");
			}
		}
		printf("*\n");
		for(int l = 1 ;l<=digitbar;l++){
			printf(" ");
		}	
		for(j=GetFirstIdxBrs(m);j<=GetLastIdxKol(m);j++){
			
				printf("*   ");
			
		}
		printf("*\n");
	}
		for(int l = 1 ;l<=digitbar;l++){
			printf(" ");
		}	
	for(j=1;j<=(NKolEff(m)*4)+1;j++){
		printf("*");
	}
	printf("\n");
	*keluaran = counter;
}

/* *** Selektor "DUNIA MATRIKS" *** */
boolean IsIdxValid (int i, int j){
/* Mengirimkan true jika i, j adalah indeks yang valid untuk matriks apa pun */

	return (i >= BrsMin && i <= BrsMax) && (j >= BrsMin && j <= BrsMax) ;
}
/* *** Selektor: Untuk sebuah matriks M yang terdefinisi: *** */
indeks GetFirstIdxBrs (MATRIKS M){
/* Mengirimkan indeks baris terkecil M */
	return BrsMin;

}
indeks GetFirstIdxKol (MATRIKS M){
/* Mengirimkan indeks kolom terkecil M */

	return KolMin;
}
indeks GetLastIdxBrs (MATRIKS M){
/* Mengirimkan indeks baris terbesar M */
	return NBrsEff(M)+BrsMin -1;


}
indeks GetLastIdxKol (MATRIKS M){
/* Mengirimkan indeks kolom terbesar M */
	return NKolEff(M)+KolMin -1;


}
boolean IsIdxEff (MATRIKS M, indeks i, indeks j){
/* Mengirimkan true jika i, j adalah indeks efektif bagi M */
	return (i >= GetFirstIdxBrs(M) && i <= GetLastIdxBrs(M) )&&(j >= GetFirstIdxKol(M) && j <= GetLastIdxKol(M) );

}
ElType GetElmtDiagonal (MATRIKS M, indeks i){
/* Mengirimkan elemen M(i,i) */
	return Elmt(M,i,i);

}
/* ********** Assignment  MATRIKS ********** */
void CopyMATRIKS (MATRIKS MIn, MATRIKS * MHsl){
/* Melakukan assignment MHsl  MIn */
	indeks i,j;
	MakeMATRIKS(NBrsEff(MIn),NKolEff(MIn),MHsl);
	for (i=GetFirstIdxBrs(MIn);i<=GetLastIdxBrs(MIn);i++){
		for (j=GetFirstIdxKol(MIn);j<=GetLastIdxKol(MIn);j++){
				Elmt(*MHsl,i,j) = Elmt(MIn,i,j);
		}		
	}

}


                              





/* ********** KELOMPOK OPERASI RELASIONAL TERHADAP MATRIKS ********** */


boolean EQSize (MATRIKS M1, MATRIKS M2){
/* Mengirimkan true jika ukuran efektif matriks M1 sama dengan ukuran efektif M2 */
/* yaitu GetBrsEff(M1) = GetNBrsEff (M2) dan GetNKolEff (M1) = GetNKolEff (M2) */

	return (NBrsEff(M1) == NBrsEff (M2)) &&  (NKolEff (M1) == NKolEff (M2)) ;

}
/* ********** Operasi lain ********** */
int NBElmt (MATRIKS M){
/* Mengirimkan banyaknya elemen M */

	return NBrsEff(M)*NKolEff(M);
}
/* ********** KELOMPOK TEST TERHADAP MATRIKS ********** */
boolean IsBujurSangkar (MATRIKS M){
/* Mengirimkan true jika M adalah matriks dg ukuran baris dan kolom sama */
	return NBrsEff(M) == NKolEff(M);
}

void Transpose (MATRIKS * M){
/* I.S. M terdefinisi dan IsBujursangkar(M) */
/* F.S. M "di-transpose", yaitu setiap elemen M(i,j) ditukar nilainya dengan elemen M(j,i) */
	MATRIKS temp;
	indeks i,j;
	MakeMATRIKS(NBrsEff(*M),NKolEff(*M),&temp);
		for (i=GetFirstIdxBrs(*M);i<=GetLastIdxBrs(*M);i++){
			for(j=GetFirstIdxKol(*M);j<=GetLastIdxKol(*M);j++){
				Elmt(temp,i,j)=Elmt(*M,j,i);			
			}
		}	

	*M= temp;
}









/*int main(){
	MATRIKS a;
	MakeNormalMATRIKS(8,8,&a);
	InitializeCastleTemple(&a);
	printMatriks(a);
}*/

