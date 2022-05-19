#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <time.h>

//elementy konstrukcyjne planszy
#define mid 0xCE
#define dhori 0xCD
#define dvert 0xBA
#define top 0xCB
#define bot 0xCA
#define right 0xB9
#define left 0xCC
#define ltcor 0xC9
#define rtcor 0xBB 
#define lbcor 0xC8
#define rbcor 0xBC
#define spc 32

//zetony do wyboru
#define ch1 0x1
#define ch2 0x2
#define ch3 0x3
#define ch4 0x4
#define ch5 0x5
#define ch6 0x6

#define MaxOdsTab 63  //max odstep tablicy
#define MaxOdsDanych 42  //max odstep wyswietlania danych

#define MaxCzasGry 180  //max czas gry	<---mozna zmienic

using namespace std;

struct Gracz{
	string nazwa;
	char ikona;
	time_t czas;
	
};

struct Plansza{
	string nazwa;
	char tab1[9];
	char tab2[9];
	char tab3[9];
	char tab4[9];
	char glowna_tab[6][6];
	
	
	void wyczysc_glowna_tablice();
	void wyczysc_male_tablice();

	void aktualizuj();
};

void Plansza::wyczysc_glowna_tablice(){
	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 6; j++){
			glowna_tab[i][j] = ' ';
		}
	}	
}
void Plansza::wyczysc_male_tablice(){
	for(int i = 0; i < 9; i++){
		tab1[i] = ' ';
	}
	for(int i = 0; i < 9; i++){
		tab2[i] = ' ';
	}
	for(int i = 0; i < 9; i++){
		tab3[i] = ' ';
	}
	for(int i = 0; i < 9; i++){
		tab4[i] = ' ';
	}
}

void Plansza::aktualizuj(){
	
	for(int j = 0; j < 3; j++){
		glowna_tab[0][j] = tab1[j];
	}
	for(int j = 3; j < 6; j++){
		glowna_tab[0][j] = tab2[j-3];
	}
	for(int j = 0; j < 3; j++){
		glowna_tab[1][j] = tab1[j+3];
	}
	for(int j = 3; j < 6; j++){
		glowna_tab[1][j] = tab2[j];
	}
	for(int j = 0; j < 3; j++){
		glowna_tab[2][j] = tab1[j+6];
	}
	for(int j = 3; j < 6; j++){
		glowna_tab[2][j] = tab2[j+3];
	}


	for(int j = 0; j < 3; j++){
		glowna_tab[3][j] = tab3[j];
	}
	for(int j = 3; j < 6; j++){
		glowna_tab[3][j] = tab4[j-3];
	}
	for(int j = 0; j < 3; j++){
		glowna_tab[4][j] = tab3[j+3];
	}
	for(int j = 3; j < 6; j++){
		glowna_tab[4][j] = tab4[j];
	}
	for(int j = 0; j < 3; j++){
		glowna_tab[5][j] = tab3[j+6];
	}
	for(int j = 3; j < 6; j++){
		glowna_tab[5][j] = tab4[j+3];
	}
}


void jedna_linia(char, char, char, char);
void generuj_plansze(Plansza , char , char , int ods=0);
void przykladowaPlansza(Plansza &, Gracz , Gracz );
void podstawowaPlansza(Plansza &, Gracz , Gracz );
void wprowadz_komende(Plansza &, char &, Gracz &, Gracz &, int, clock_t &, clock_t &, int);
void init_gracze(Gracz &, Gracz &);
void init_zetony(Plansza &, Gracz &, Gracz &);
void wybor_zetonu(Plansza &, Gracz *, Gracz *);
int wybor_trybu_gry(Gracz, Gracz);
char sprawdz_wygrana(Plansza &, Gracz, Gracz);
void obrot_tablicy(Plansza *, char, char);
void wprowadz_komende_2(Plansza &, char &, Gracz &, Gracz &, int, clock_t &, clock_t &, int);
void odstep(int, int);
void wyswietl_dane(Gracz, Gracz, string, int x = 0);
void wyswietl_kolejke(Gracz, Gracz, int, int y = 0);

int main(){
	cout << "-----------------------" << endl;
	cout << " |Gry - projekt z POP| " << endl;
	cout << "-----------------------" << endl;
	Plansza plansza;
	Gracz gracz1, gracz2;
	
	init_gracze(gracz1, gracz2);
	init_zetony(plansza, gracz1, gracz2);
	double czasGry = MaxCzasGry;
	gracz1.czas = czasGry;
	gracz2.czas = czasGry;
	
	Gracz *wskGr1 = &gracz1;
	Gracz *wskGr2 = &gracz2;
	
	int gra = wybor_trybu_gry(gracz1, gracz2);		//wybor gry
	string opcja;
	bool petla = true;
	while(petla){
		string opcja_2;
		bool petla_2 = true;
		if(gra == 1 ){
			wyswietl_dane(gracz1, gracz2, "kolko krzyzyk");
		}
		else if(gra == 2){
			wyswietl_dane(gracz1, gracz2, "pentago");
		}
		
		cout << "h - opis gry" << endl;
		cout << "o - wczytanie przykladowej planszy" << endl;
		cout << "c - wczytanie podstawowej planszy" << endl;
		cout << "m - ustawienia gry (zmiana tokena)"<< endl;
		cin >> opcja;
		cin.ignore(200, '\n');
		if(opcja.length() == 1){
			if(isdigit(opcja[0]) != 1){
				switch(opcja[0]){
					case 'm':
						while(petla_2){
							system("cls");
							cout << "---Ustawienia---" << endl;
							cout << "a - zmiana tokena u gracza1" << endl;
							cout << "b - zmiana tokena u gracza2" << endl;	
							cout << "m - powrot" << endl;
							cin >> opcja_2;
							cin.ignore(200, '\n');
							if(opcja_2[0] == 'm'){
								system("cls");
								petla_2 = false;
							}
							else if(opcja_2[0] == 'a'){
								system("cls");
								cout << "Ustawione zetony    " << "gracz1: " << gracz1.nazwa << ": " << gracz1.ikona << " , gracz2: " << gracz2.nazwa<< ": " << gracz2.ikona << endl;
								wybor_zetonu(plansza, wskGr1, wskGr2);	
							}
							else if(opcja_2[0] == 'b'){
								system("cls");
								cout << "Ustawione zetony    " << "gracz1: " << gracz1.nazwa << ": " << gracz1.ikona << " , gracz2: " << gracz2.nazwa << ": " << gracz2.ikona << endl;
								wybor_zetonu(plansza, wskGr2, wskGr1);
							}else{
								system("cls");
								cout << "zle dane!" << endl;
							}
						}
						break;
					case 'h':
						while(petla_2){
							system("cls");
							cout << "------kolko krzyzyk------" << endl;
							cout << "Wpisujac wlasciwa komende, gracz wybiera dokladne miejsce na swoj zeton" << endl;
							cout << "q,w,a,s - wybor czesci planszy" << endl;
							cout << "odpowiednio: lewej gornej, prawej gornej, lewej dolnej, prawej dolnej" << endl;
							cout << "1..9 - wybor pola na czesci planszy jak na klawiaturze numerycznej" << endl;
							cout << "tj. 1 to dolne lewe pole. np. q5" << endl;
							cout << "Wygrana jest wtedy gdy gracz ulozy pionowo, poziomo lub pod ukosem" << endl;
							cout << "dokladnie 5 kolejnych zetonow" << endl;
							cout << endl;
							cout << "------pentago------" << endl;
							cout << "Wpisujac pierwsza komende, gracz wybiera dokladne miejsce na swoj zeton" << endl;
							cout << "Wpisujac druga komende, gracz wybiera ktora czesc planszy chce obrocic" << endl;
							cout << "o 90 stopni w wybranym kierunku" << endl;
							cout << "q,w,a,s - wybor czesci planszy" << endl;
							cout << "odpowiednio: lewej gornej, prawej gornej, lewej dolnej, prawej dolnej" << endl;
							cout << "1..9 - wybor pola na czesci planszy jak na klawiaturze numerycznej" << endl;
							cout << "tj. 1 to dolne lewe pole. np. q5" << endl;
							cout << endl;
							cout << "q,w,a,s - wybor czesci planszy" << endl;
							cout << "odpowiednio: lewej gornej, prawej gornej, lewej dolnej, prawej dolnej" << endl;
							cout << "z,x - obrot odpowiednio: zgodnie z ruchem wskazowek zegara i odwrotnie. np. qz" << endl;
							cout << "Wygrana jest wtedy gdy gracz ulozy pionowo, poziomo lub pod ukosem" << endl;
							cout << "dokladnie 5 kolejnych zetonow" << endl;
							cout << "h - powrot: ";
							cin >> opcja_2;
							cin.ignore(200, '\n');
							if(opcja_2[0] == 'h'){
								system("cls");
								petla_2 = false;
							}else{
								system("cls");
								cout << "zle dane!" << endl;
							}
						}
						break;	
					case 'o':
						petla = false;
						plansza.wyczysc_glowna_tablice();
						plansza.wyczysc_male_tablice();
						if(gra == 1){
							system("cls");
							wyswietl_dane(gracz1, gracz2, "kolko krzyzyk");
							wyswietl_kolejke(gracz1, gracz2, 1);
						}
						else if(gra == 2){
							system("cls");
							wyswietl_dane(gracz1, gracz2, "pentago");
							wyswietl_kolejke(gracz1, gracz2, 1);
						}
						przykladowaPlansza(plansza, gracz1, gracz2);
						break;
					case 'c':
						petla = false;
						plansza.wyczysc_glowna_tablice();
						plansza.wyczysc_male_tablice();
						if(gra == 1){
							system("cls");
							wyswietl_dane(gracz1, gracz2, "kolko krzyzyk");
							wyswietl_kolejke(gracz1, gracz2, 1);
						}
						else if(gra == 2){
							system("cls");
							wyswietl_dane(gracz1, gracz2, "pentago");
							wyswietl_kolejke(gracz1, gracz2, 1);
						}
						podstawowaPlansza(plansza, gracz1, gracz2);	
						break;
					default:
						system("cls");
						cout << "zle dane!" << endl;
						break;						
				}	
			}else{
				system("cls");
				cout << "zle dane!" << endl;
			}	
		}else{
			system("cls");
			cout << "zle dane!" << endl;
		} 
	}		
	
	int a = 1;	//zmienna ktora ustala kolejke gracza
	if(gra == 1){	//rozgrywka kolko krzyzyk
		clock_t start;
		clock_t stop;
		double roznica;
		
		while(1){
			char ico;
			if(a == 1){
				ico = gracz1.ikona;
			}
			else if(a == -1){
				ico = gracz2.ikona;
			}
			start = clock();
			
			wprowadz_komende(plansza, ico, gracz1, gracz2, a, start, stop, 1);
			stop = clock();
			roznica = (double)(stop - start)/CLOCKS_PER_SEC;
			if(a == 1){
				gracz1.czas -= roznica;
			}
			else if(a == -1){
				gracz2.czas -= roznica;
			}
			plansza.aktualizuj();
			system("cls");
			wyswietl_dane(gracz1, gracz2, "kolko krzyzyk");
			wyswietl_kolejke(gracz1, gracz2, -a);
			generuj_plansze(plansza, dvert, spc);
			if(sprawdz_wygrana(plansza, gracz1, gracz2) == 'w'){
				return 0;
			}
			else if(sprawdz_wygrana(plansza, gracz1, gracz2) == 'r'){
				cout << "nie ma zwyciezcy";
				return 0;
			}
			a = (-1)*a;
		}		
	}
	
	else if(gra == 2){	//rozgrywka pentago
		clock_t start;
		clock_t stop;
		double roznica;
	
		while(1){
			char ico;
			if(a == 1){
				ico = gracz1.ikona;
			}
			else if(a == -1){
				ico = gracz2.ikona;
			}
			start = clock();
			
			wprowadz_komende(plansza, ico, gracz1, gracz2, a, start, stop, -1);
			stop = clock();
			roznica = (double)(stop - start)/CLOCKS_PER_SEC;
			if(a == 1){
				gracz1.czas -= roznica;
			}
			else if(a == -1){
				gracz2.czas -= roznica;
			}
			plansza.aktualizuj();
			system("cls");
			wyswietl_dane(gracz1, gracz2, "pentago");
			wyswietl_kolejke(gracz1, gracz2, a);
			generuj_plansze(plansza, dvert, spc);
			start = clock();
			
			wprowadz_komende_2(plansza, ico, gracz1, gracz2, a, start, stop, -1);
			stop = clock();
			roznica = (double)(stop - start)/CLOCKS_PER_SEC;
			if(a == 1){
				gracz1.czas -= roznica;
			}
			else if(a == -1){
				gracz2.czas -= roznica;
			}
			plansza.aktualizuj();
			system("cls");
			wyswietl_dane(gracz1, gracz2, "pentago");
			wyswietl_kolejke(gracz1, gracz2, -a);
			generuj_plansze(plansza, dvert, spc);
			if(sprawdz_wygrana(plansza, gracz1, gracz2) == 'w'){
				return 0;
			}
			else if(sprawdz_wygrana(plansza, gracz1, gracz2) == 'r'){
				cout << "nie ma zwyciezcy";
				return 0;
			}
			a = (-1)*a;
			
		}
	}
}

//Funkcje ---------------
void wyswietl_kolejke(Gracz A, Gracz B, int x, int y){
	odstep(y, MaxOdsDanych);
	if(x == 1){
		cout << " ruch gracza1: " << A.nazwa << endl;
	}
	else if(x == -1){
		cout << " ruch gracza2: " << B.nazwa << endl;
	}
	odstep(y, MaxOdsDanych);
	cout << "--------------------------------------" << endl;
}

int wybor_trybu_gry(Gracz A, Gracz B){
	int mem;
	bool petla = true;
	while(petla){
		string gm; // tryb gry
		cout << "token gracza1: " << A.ikona << endl;
		cout << "token gracza2: " << B.ikona << endl;
		cout << "wybierz tryb gry (1 - kolko krzyzyk, 2 - pentago): ";
		cin >> gm;
		cin.ignore(200, '\n');
		if(gm.length() != 1){
			system("cls");
			cout << "zle dane" << endl;
		}else{
			if(isdigit(gm[0]) == 1){
				switch(gm[0]){
					case '1':
						system( "cls" );
						mem = 1;
						return mem;
						petla = false;
						break;
					case '2':
						system( "cls" );
						mem = 2;
						return mem;
						petla = false;
						break;
					default:
						system("cls");
						cout << "zla cyfra" << endl;
						break;
				}
			}else{
				system("cls");
				cout << "zle dane"<< endl;
			} 
		}
	}
}



void wyswietl_dane(Gracz A, Gracz B, string name, int x){
	odstep(x, MaxOdsDanych);
	cout << "--------------------------------------" << endl;
	odstep(x, MaxOdsDanych);
	if(name == "pentago"){
		cout << "     pentago     " << endl;
	}
	else if(name == "kolko krzyzyk"){
		cout << "  kolko krzyzyk  " << endl;
	}
	odstep(x, MaxOdsDanych);
	cout << "--------------------------------------" << endl;
	odstep(x, MaxOdsDanych);
	cout << " gracz1: " << A.nazwa << " token: " << A.ikona << " czas: " << A.czas << "s" << endl;
	odstep(x, MaxOdsDanych);
	cout << " gracz2: " << B.nazwa << " token: " << B.ikona << " czas: " << B.czas << "s" << endl;
	odstep(x, MaxOdsDanych);
	cout << "--------------------------------------" << endl;
}

void init_gracze(Gracz &A, Gracz &B){
	bool petla = true;
	string tekst;
	while(petla){
		cout << "Nazwa gracza1: ";
		cin >> tekst;
		cin.ignore(200, '\n');
		if(tekst.length() < 10){
			A.nazwa = tekst;
			petla = false;
		}else{
			system("cls");
			cout << "za dluga nazwa" << endl;
		}
	}
	petla = true;
	while(petla){
		cout << "Nazwa gracza2: ";
		cin >> tekst;
		cin.ignore(200, '\n');
		if(tekst.length() < 12){
			if(A.nazwa != tekst){
				B.nazwa = tekst;
				petla = false;
			}else{
				system("cls");
				cout << "nazwa nie moze byc taka sama" << endl;
			}
		}else{
			system("cls");
			cout << "za dluga nazwa" << endl;
		}
	}
	system("cls");
}

void wybor_zetonu(Plansza &P, Gracz *A, Gracz *B){
	bool petla = true;
	string pict;
	char buf; 
	while(petla){
		cout << "do wyboru masz takie zetony: " << endl;
		cout << "1: " << char(ch1) << " " << "2: " << char(ch2) << endl; 
		cout << "3: " << char(ch3) << " " << "4: " << char(ch4) << endl;
		cout << "5: " << char(ch5) << " " << "6: " << char(ch6) << endl;
		cout << "Wybor zetonu dla gracza: " << A->nazwa << endl;
		cin >> pict;
		cin.ignore(200, '\n');
		if(pict.length() == 1){
			if(isdigit(pict[0]) == 1){
					switch(pict[0]){
						case '1':
							buf = A->ikona;
							if(B->ikona != char(ch1)){
								A->ikona = char(ch1);
								for(int i = 0 ; i < 9; i++){
									if(P.tab1[i] == buf){
										P.tab1[i] = char(ch1);
									}
								}
								for(int i = 0 ; i < 9; i++){
									if(P.tab2[i] == buf){
										P.tab2[i] = char(ch1);
									}
								}
								for(int i = 0 ; i < 9; i++){
									if(P.tab3[i] == buf){
										P.tab3[i] = char(ch1);
									}
								}
								for(int i = 0 ; i < 9; i++){
									if(P.tab4[i] == buf){
										P.tab4[i] = char(ch1);
									}
								}
								P.aktualizuj();
								petla = false;
								system("cls");
							}else{
								system("cls");
								cout << "ten zeton nalezy do drugiego gracza" << endl;
								
							}
							break;
						
						case '2':
							buf = A->ikona;
							if(B->ikona != char(ch2)){
								A->ikona = char(ch2);
								for(int i = 0 ; i < 9; i++){
									if(P.tab1[i] == buf){
										P.tab1[i] = char(ch2);
									}
								}
								for(int i = 0 ; i < 9; i++){
									if(P.tab2[i] == buf){
										P.tab2[i] = char(ch2);
									}
								}
								for(int i = 0 ; i < 9; i++){
									if(P.tab3[i] == buf){
										P.tab3[i] = char(ch2);
									}
								}
								for(int i = 0 ; i < 9; i++){
									if(P.tab4[i] == buf){
										P.tab4[i] = char(ch2);
									}
								}
								P.aktualizuj();
								petla = false;
								system("cls");
							}else{
								system("cls");
								cout << "ten zeton nalezy do drugiego gracza" << endl;
								cout << "Ustawione zetony    " << "A: " << A->nazwa << ": " << A->ikona << " , B: " << B->nazwa<< ": " << B->ikona << endl;
							}
							break;
						
						case '3':
							buf = A->ikona;
							if(B->ikona != char(ch3)){
								A->ikona = char(ch3);
								for(int i = 0 ; i < 9; i++){
									if(P.tab1[i] == buf){
										P.tab1[i] = char(ch3);
									}
								}
								for(int i = 0 ; i < 9; i++){
									if(P.tab2[i] == buf){
										P.tab2[i] = char(ch3);
									}
								}
								for(int i = 0 ; i < 9; i++){
									if(P.tab3[i] == buf){
										P.tab3[i] = char(ch3);
									}
								}
								for(int i = 0 ; i < 9; i++){
									if(P.tab4[i] == buf){
										P.tab4[i] = char(ch3);
									}
								}
								P.aktualizuj();
								petla = false;
								system("cls");
							}else{
								system("cls");
								cout << "ten zeton nalezy do drugiego gracza" << endl;
								cout << "Ustawione zetony    " << "A: " << A->nazwa << ": " << A->ikona << " , B: " << B->nazwa<< ": " << B->ikona << endl;
							}
							break;
						
						case '4':
							buf = A->ikona;
							if(B->ikona != char(ch4)){
								A->ikona = char(ch4);
								for(int i = 0 ; i < 9; i++){
									if(P.tab1[i] == buf){
										P.tab1[i] = char(ch4);
									}
								}
								for(int i = 0 ; i < 9; i++){
									if(P.tab2[i] == buf){
										P.tab2[i] = char(ch4);
									}
								}
								for(int i = 0 ; i < 9; i++){
									if(P.tab3[i] == buf){
										P.tab3[i] = char(ch4);
									}
								}
								for(int i = 0 ; i < 9; i++){
									if(P.tab4[i] == buf){
										P.tab4[i] = char(ch4);
									}
								}
								P.aktualizuj();
								petla = false;
								system("cls");
							}else{
								system("cls");
								cout << "ten zeton nalezy do drugiego gracza" << endl;
								cout << "Ustawione zetony    " << "A: " << A->nazwa << ": " << A->ikona << " , B: " << B->nazwa<< ": " << B->ikona << endl;
							}
							break;
						
						case '5':
							buf = A->ikona;
							if(B->ikona != char(ch5)){
								A->ikona = char(ch5);
								for(int i = 0 ; i < 9; i++){
									if(P.tab1[i] == buf){
										P.tab1[i] = char(ch5);
									}
								}
								for(int i = 0 ; i < 9; i++){
									if(P.tab2[i] == buf){
										P.tab2[i] = char(ch5);
									}
								}
								for(int i = 0 ; i < 9; i++){
									if(P.tab3[i] == buf){
										P.tab3[i] = char(ch5);
									}
								}
								for(int i = 0 ; i < 9; i++){
									if(P.tab4[i] == buf){
										P.tab4[i] = char(ch5);
									}
								}
								P.aktualizuj();
								petla = false;
								system("cls");
							}else{
								system("cls");
								cout << "ten zeton nalezy do drugiego gracza" << endl;
								cout << "Ustawione zetony    " << "A: " << A->nazwa << ": " << A->ikona << " , B: " << B->nazwa<< ": " << B->ikona << endl;
							}
							break;
						
						case '6':
							buf = A->ikona;
							if(B->ikona != char(ch6)){
								A->ikona = char(ch6);
								for(int i = 0 ; i < 9; i++){
									if(P.tab1[i] == buf){
										P.tab1[i] = char(ch6);
									}
								}
								for(int i = 0 ; i < 9; i++){
									if(P.tab2[i] == buf){
										P.tab2[i] = char(ch6);
									}
								}
								for(int i = 0 ; i < 9; i++){
									if(P.tab3[i] == buf){
										P.tab3[i] = char(ch6);
									}
								}
								for(int i = 0 ; i < 9; i++){
									if(P.tab4[i] == buf){
										P.tab4[i] = char(ch6);
									}
								}
								P.aktualizuj();
								petla = false;
								system("cls");
							}else{
								system("cls");
								cout << "ten zeton nalezy do drugiego gracza" << endl;
								cout << "Ustawione zetony    " << "A: " << A->nazwa << ": " << A->ikona << " , B: " << B->nazwa<< ": " << B->ikona << endl;
							}
							break;
						
						default:
							system("cls");
							cout << "zle dane" << endl;
							cout << "Ustawione zetony    " << "A: " << A->nazwa << ": " << A->ikona << " , B: " << B->nazwa<< ": " << B->ikona << endl;
							break;
					}
			}else{
				system("cls");
				cout << "zle dane" << endl;
				cout << "Ustawione zetony    " << "A: " << A->nazwa << ": " << A->ikona << " , B: " << B->nazwa<< ": " << B->ikona << endl;
			}
		}else{
			system("cls");
			cout << "zle dane" << endl;
			cout << "Ustawione zetony    " << "A: " << A->nazwa << ": " << A->ikona << " , B: " << B->nazwa<< ": " << B->ikona << endl;
		}
	}
}

void init_zetony(Plansza &P, Gracz &A, Gracz &B){
	A.ikona = char(spc);
	B.ikona = char(spc);
	Gracz *wskA = &A;
	Gracz *wskB = &B;
	wybor_zetonu(P, wskA, wskB);
	wybor_zetonu(P, wskB, wskA);
}

void odstep(int x, int MaxSpace){
	if(x <= MaxSpace){
		for(int i = 0; i < x; i++){
			cout << char(spc);
		}
	}
	else{
		for(int i = 0; i < MaxSpace; i++){
			cout << char(spc);
		}
	}
}

void generuj_plansze(Plansza P, char x, char z, int ods){
	odstep(ods, MaxOdsTab);
	//1
	jedna_linia(ltcor,dhori,top,rtcor);
	//2,3,4
	for(int j = 0; j < 9; j+=3){
	odstep(ods, MaxOdsTab);
	cout << char(x);
	cout << char(z) << P.tab1[j] << char(z) << P.tab1[j+1] << char(z) << P.tab1[j+2] << char(z);
	cout << char(x);
	cout << char(z) << P.tab2[j] << char(z) << P.tab2[j+1] << char(z) << P.tab2[j+2] << char(z);
	cout << char(x);
	cout << endl;
	}
	odstep(ods, MaxOdsTab);
	//5
	jedna_linia(left,dhori,mid,right);
	//6,7,8
	for(int j = 0; j < 9; j+=3){
		odstep(ods, MaxOdsTab);
		cout << char(x);
		cout << char(z) << P.tab3[j] << char(z) << P.tab3[j+1] << char(z) << P.tab3[j+2] << char(z);
		cout << char(x);
		cout << char(z) << P.tab4[j] << char(z) << P.tab4[j+1] << char(z) << P.tab4[j+2] << char(z);
		cout << char(x);
		cout << endl;
	}
	odstep(ods, MaxOdsTab);
	//9
	jedna_linia(lbcor,dhori, bot, rbcor);
}


void podstawowaPlansza(Plansza &P, Gracz r, Gracz s){	//gracz1 gracz2
	P.wyczysc_male_tablice();
	P.wyczysc_glowna_tablice();
	P.aktualizuj();
	generuj_plansze(P, dvert, spc);
}

void przykladowaPlansza(Plansza &P, Gracz A, Gracz B){	//gracz1 gracz2
	P.tab1[1] = B.ikona;
	P.tab2[1] = A.ikona;
	P.tab1[3] = A.ikona;
	P.tab1[4] = A.ikona;
	P.tab1[5] = B.ikona;
	P.tab2[3] = A.ikona;
	P.tab2[4] = B.ikona;
	P.tab1[7] = A.ikona;
	P.tab3[0] = A.ikona;
	P.tab3[4] = A.ikona;
	P.tab3[3] = B.ikona;
	P.tab3[5] = A.ikona;
	P.tab4[4] = B.ikona;
	P.tab3[7] = B.ikona;
	P.tab4[7] = B.ikona;
	P.tab4[8] = B.ikona;
	P.aktualizuj();
	generuj_plansze(P, dvert, spc);
}

void jedna_linia(char w, char x, char y, char z){
	cout << char(w);
	for(int i = 0; i < 7; i++){
		cout << char(x);
	}
	cout << char(y);
	for(int i = 0; i < 7; i++){
		cout << char(x);
	}
	cout << char(z);
	cout << endl;
}

void wprowadz_komende(Plansza &P, char &ico, Gracz &A, Gracz &B, int x, clock_t &start, clock_t &stop, int info){
	Gracz *wGr1 = &A;
	Gracz *wGr2 = &B;
	double roznica;
	char komenda[2];
	bool petla = true;
	bool petla_2;
	string opcja_2;
	while(petla){
		bool petla_2 = true;
		cout << "podaj komende / h - pomoc" << endl;
		cin >> komenda;
		cin.ignore(200, '\n');
		if(!(strlen(komenda) > 2) && !(strlen(komenda) == 0)){
			if(strlen(komenda) == 1){
				switch(komenda[0]){
					case 'p':
						stop = clock();
						roznica = (double) (stop - start)/CLOCKS_PER_SEC;
						if(x == 1){
							A.czas -= roznica;
						}
						else if(x == -1){
							B.czas -= roznica;
						}
						petla_2 = true;
						while(petla_2){
							system("cls");
							cout << "PAUZA" << endl;
							cout << "p - powrot: ";
							cin >> opcja_2;
							cin.ignore(200, '\n');
							if(opcja_2[0] == 'p'){
								system("cls");
								start = clock();
								if(info*x == 1){
									wyswietl_dane(A, B, "kolko krzyzyk");
								}
								else if(info*x == -1){
									wyswietl_dane(A, B, "pentago");
								}
								wyswietl_kolejke(A, B, x);
								generuj_plansze(P, dvert, spc);
								petla_2 = false;
							}else{
								cout << "zle dane!" << endl;
							}
						}
						break;
					case 'h':
						stop = clock();
						roznica = (double) (stop - start)/CLOCKS_PER_SEC;
						if(x == 1){
							A.czas -= roznica;
						}
						else if(x == -1){
							B.czas -= roznica;
						}
						while(petla_2){
							system("cls");
							cout << "Opis gry:...................... " << endl;
							cout << "q,w,a,s - wybor czesci planszy" << endl;
							cout << "odpowiednio: lewej gornej, prawej gornej, lewej dolnej, prawej dolnej" << endl;
							cout << "1..9 - wybor pola na czesci planszy jak na klawiaturze numerycznej" << endl;
							cout << "tj. 1 to dolne lewe pole" << endl;
							cout << endl << "m - zmiana zetonu" << endl;
							cout << "h - powrot: ";
							cin >> opcja_2;
							cin.ignore(200, '\n');
							if(opcja_2[0] == 'h'){
								system("cls");
								start = clock();
								if(info*x == 1){
									wyswietl_dane(A, B, "kolko krzyzyk");
								}
								else if(info*x == -1){
									wyswietl_dane(A, B, "pentago");
								}
								wyswietl_kolejke(A, B, x);
								generuj_plansze(P, dvert, spc);
								petla_2 = false;
								
							}else{
								cout << "zle dane!" << endl;
							}
						}
						break;
					case 'm':
						stop = clock();
						roznica = (double) (stop - start)/CLOCKS_PER_SEC;
						if(x == 1){
							A.czas -= roznica;
						}
						else if(x == -1){
							B.czas -= roznica;
						}
						while(petla_2){
							system("cls");
							cout << "Ustawione zetony    " << "A: " << A.nazwa << ": " << A.ikona << " , B: " << B.nazwa<< ": " << B.ikona << endl;
							if(x == 1){
								wybor_zetonu(P, wGr1, wGr2);
								ico = A.ikona;
							}
							else if(x == -1){
								wybor_zetonu(P, wGr2, wGr1);
								ico = B.ikona;
							}
							cout << "m - powrot: ";
							cin >> opcja_2;
							cin.ignore(200, '\n');
							if(opcja_2[0] == 'm'){
								system("cls");
								start = clock();
								if(info*x == 1){
									wyswietl_dane(A, B, "kolko krzyzyk");
								}
								else if(info*x == -1){
									wyswietl_dane(A, B, "pentago");
								}
								wyswietl_kolejke(A, B, x);
								generuj_plansze(P, dvert, spc);
								petla_2 = false;
							}
						}
						break;						
					default:
						cout << "zla komenda!" << endl;
						break;
				}
			}
			else if(strlen(komenda) == 2){
				int temp;
				if(komenda[0] == 'q'){
					if(isdigit(komenda[1]) && komenda[1] != '0'){
						switch(komenda[1]){
							case '1':
								temp = 7;
								if(P.tab1[temp-1] == ' '){
									P.tab1[temp-1] = ico;
									petla = false;
								}else{
									cout << "te miejsce jest zajete" << endl;
								}
								break;
							case '2':
								temp = 8;
								if(P.tab1[temp-1] == ' '){
									P.tab1[temp-1] = ico;
									petla = false;
								}else{
									cout << "te miejsce jest zajete" << endl;
								}
								break;
							case '3':
								temp = 9;
								if(P.tab1[temp-1] == ' '){
									P.tab1[temp-1] = ico;
									petla = false;
								}else{
									cout << "te miejsce jest zajete" << endl;
								}
								break;
							case '4':
								temp = 4;
								if(P.tab1[temp-1] == ' '){
									P.tab1[temp-1] = ico;
									petla = false;
								}else{
									cout << "te miejsce jest zajete" << endl;
								}
								break;
							case '5':
								temp = 5;
								if(P.tab1[temp-1] == ' '){
									P.tab1[temp-1] = ico;
									petla = false;
								}else{
									cout << "te miejsce jest zajete" << endl;
								}
								break;
							case '6':
								temp = 6;
								if(P.tab1[temp-1] == ' '){
									P.tab1[temp-1] = ico;
									petla = false;
								}else{
									cout << "te miejsce jest zajete" << endl;
								}
								break;
							case '7':
								temp = 1;
								if(P.tab1[temp-1] == ' '){
									P.tab1[temp-1] = ico;
									petla = false;
								}else{
									cout << "te miejsce jest zajete" << endl;
								}
								break;
							case '8':
								temp = 2;
								if(P.tab1[temp-1] == ' '){
									P.tab1[temp-1] = ico;
									petla = false;
								}else{
									cout << "te miejsce jest zajete" << endl;
								}
								break;
							case '9':
								temp = 3;
								if(P.tab1[temp-1] == ' '){
									P.tab1[temp-1] = ico;
									petla = false;
								}else{
									cout << "te miejsce jest zajete" << endl;
								}
								break;
						}	
					}else cout << "zle dane" << endl;
				}
				else if(komenda[0] == 'w'){
					if(isdigit(komenda[1]) && komenda[1] != '0'){
						switch(komenda[1]){
							case '1':
								temp = 7;
								if(P.tab2[temp-1] == ' '){
									P.tab2[temp-1] = ico;
									petla = false;
								}else{
									cout << "te miejsce jest zajete" << endl;
								}
								break;
							case '2':
								temp = 8;
								if(P.tab2[temp-1] == ' '){
									P.tab2[temp-1] = ico;
									petla = false;
								}else{
									cout << "te miejsce jest zajete" << endl;
								}
								break;
							case '3':
								temp = 9;
								if(P.tab2[temp-1] == ' '){
									P.tab2[temp-1] = ico;
									petla = false;
								}else{
									cout << "te miejsce jest zajete" << endl;
								}
								break;
							case '4':
								temp = 4;
								if(P.tab2[temp-1] == ' '){
									P.tab2[temp-1] = ico;
									petla = false;
								}else{
									cout << "te miejsce jest zajete" << endl;
								}
								break;
							case '5':
								temp = 5;
								if(P.tab2[temp-1] == ' '){
									P.tab2[temp-1] = ico;
									petla = false;
								}else{
									cout << "te miejsce jest zajete" << endl;
								}
								break;
							case '6':
								temp = 6;
								if(P.tab2[temp-1] == ' '){
									P.tab2[temp-1] = ico;
									petla = false;
								}else{
									cout << "te miejsce jest zajete" << endl;
								}
								break;
							case '7':
								temp = 1;
								if(P.tab2[temp-1] == ' '){
									P.tab2[temp-1] = ico;
									petla = false;
								}else{
									cout << "te miejsce jest zajete" << endl;
								}
								break;
							case '8':
								temp = 2;
								if(P.tab2[temp-1] == ' '){
									P.tab2[temp-1] = ico;
									petla = false;
								}else{
									cout << "te miejsce jest zajete" << endl;
								}
								break;
							case '9':
								temp = 3;
								if(P.tab2[temp-1] == ' '){
									P.tab2[temp-1] = ico;
									petla = false;
								}else{
									cout << "te miejsce jest zajete" << endl;
								}
								break;
						}	
					}else cout << "zle dane" << endl;
				}
				else if(komenda[0] == 'a'){
					if(isdigit(komenda[1]) && komenda[1] != '0'){
						switch(komenda[1]){
							case '1':
								temp = 7;
								if(P.tab3[temp-1] == ' '){
									P.tab3[temp-1] = ico;
									petla = false;
								}else{
									cout << "te miejsce jest zajete" << endl;
								}
								break;
							case '2':
								temp = 8;
								if(P.tab3[temp-1] == ' '){
									P.tab3[temp-1] = ico;
									petla = false;
								}else{
									cout << "te miejsce jest zajete" << endl;
								}
								break;
							case '3':
								temp = 9;
								if(P.tab3[temp-1] == ' '){
									P.tab3[temp-1] = ico;
									petla = false;
								}else{
									cout << "te miejsce jest zajete" << endl;
								}
								break;
							case '4':
								temp = 4;
								if(P.tab3[temp-1] == ' '){
									P.tab3[temp-1] = ico;
									petla = false;
								}else{
									cout << "te miejsce jest zajete" << endl;
								}
								break;
							case '5':
								temp = 5;
								if(P.tab3[temp-1] == ' '){
									P.tab3[temp-1] = ico;
									petla = false;
								}else{
									cout << "te miejsce jest zajete" << endl;
								}
								break;
							case '6':
								temp = 6;
								if(P.tab3[temp-1] == ' '){
									P.tab3[temp-1] = ico;
									petla = false;
								}else{
									cout << "te miejsce jest zajete" << endl;
								}
								break;
							case '7':
								temp = 1;
								if(P.tab3[temp-1] == ' '){
									P.tab3[temp-1] = ico;
									petla = false;
								}else{
									cout << "te miejsce jest zajete" << endl;
								}
								break;
							case '8':
								temp = 2;
								if(P.tab3[temp-1] == ' '){
									P.tab3[temp-1] = ico;
									petla = false;
								}else{
									cout << "te miejsce jest zajete" << endl;
								}
								break;
							case '9':
								temp = 3;
								if(P.tab3[temp-1] == ' '){
									P.tab3[temp-1] = ico;
									petla = false;
								}else{
									cout << "te miejsce jest zajete" << endl;
								}
								break;
						}	
					}else cout << "zle dane" << endl;
				}
				else if(komenda[0] == 's'){
					if(isdigit(komenda[1]) && komenda[1] != '0'){
						switch(komenda[1]){
							case '1':
								temp = 7;
								if(P.tab4[temp-1] == ' '){
									P.tab4[temp-1] = ico;
									petla = false;
								}else{
									cout << "te miejsce jest zajete" << endl;
								}
								break;
							case '2':
								temp = 8;
								if(P.tab4[temp-1] == ' '){
									P.tab4[temp-1] = ico;
									petla = false;
								}else{
									cout << "te miejsce jest zajete" << endl;
								}
								break;
							case '3':
								temp = 9;
								if(P.tab4[temp-1] == ' '){
									P.tab4[temp-1] = ico;
									petla = false;
								}else{
									cout << "te miejsce jest zajete" << endl;
								}
								break;
							case '4':
								temp = 4;
								if(P.tab4[temp-1] == ' '){
									P.tab4[temp-1] = ico;
									petla = false;
								}else{
									cout << "te miejsce jest zajete" << endl;
								}
								break;
							case '5':
								temp = 5;
								if(P.tab4[temp-1] == ' '){
									P.tab4[temp-1] = ico;
									petla = false;
								}else{
									cout << "te miejsce jest zajete" << endl;
								}
								break;
							case '6':
								temp = 6;
								if(P.tab4[temp-1] == ' '){
									P.tab4[temp-1] = ico;
									petla = false;
								}else{
									cout << "te miejsce jest zajete" << endl;
								}
								break;
							case '7':
								temp = 1;
								if(P.tab4[temp-1] == ' '){
									P.tab4[temp-1] = ico;
									petla = false;
								}else{
									cout << "te miejsce jest zajete" << endl;
								}
								break;
							case '8':
								temp = 2;
								if(P.tab4[temp-1] == ' '){
									P.tab4[temp-1] = ico;
									petla = false;
								}else{
									cout << "te miejsce jest zajete" << endl;
								}
								break;
							case '9':
								temp = 3;
								if(P.tab4[temp-1] == ' '){
									P.tab4[temp-1] = ico;
									petla = false;
								}else{
									cout << "te miejsce jest zajete" << endl;
								}
								break;
						}	
					}else cout << "zle dane" << endl;
				}else cout << "zla komenda!" << endl;
				
			}
		}	
	}
}

char sprawdz_wygrana(Plansza &P, Gracz A, Gracz B){
	int nastepny = 0;
	char ico;
	//wygrana wg kolumny
	//
	//
	if(A.czas <= 0){
		cout << "wygrywa gracz2" << endl;
		return 'w';
	}
	else if(B.czas <= 0){
		cout << "wygrywa gracz1" << endl;
		return 'w';
	}
	
	for(int i = 0; i < 6; i++){
		if(P.glowna_tab[0][i] != char(spc)){
			ico = P.glowna_tab[0][i];
			
			nastepny = 1;
			if(P.glowna_tab[1][i] != char(spc) && P.glowna_tab[1][i] == ico){
				++nastepny;
				for(int j = 2; j < 5; j++){
					if(P.glowna_tab[j][i] == ico){
						++nastepny;
					}
				}
				if(P.glowna_tab[5][i] == ico){
					nastepny = 0;
				}
					
			}
			else if(P.glowna_tab[1][i] != char(spc) && P.glowna_tab[1][i] != ico){
				nastepny = 1;
				ico = P.glowna_tab[1][i];
				for(int j = 2; j < 6; j++){
					if(P.glowna_tab[j][i] == ico){
						++nastepny;
					}	
				}	
			}
			if(nastepny == 5){
				if(ico == A.ikona){
					cout << "wygrywa gracz1" << endl;
					return 'w';
				}	
				else if(ico == B.ikona){
					cout << "wygrywa gracz2" << endl;
					return 'w';
				}
			}	
		}else{
			ico = P.glowna_tab[1][i];
			nastepny = 1;
			for(int j = 2; j < 6; j++){
				if(P.glowna_tab[j][i] == ico){
					++nastepny;
				}
			}
			if(nastepny == 5){
				if(ico == A.ikona){
					cout << "wygrywa gracz1" << endl;
					return 'w';
				}	
				else if(ico == B.ikona){
					cout << "wygrywa gracz2" << endl;
					return 'w';
				} 
			}
			
			
		}
	}
	//wygrana wedlug wiersza
	//
	//
	for(int i = 0; i < 6; i++){
		if(P.glowna_tab[i][0] != char(spc)){
			ico = P.glowna_tab[i][0];
			
			nastepny = 1;
			if(P.glowna_tab[i][1] != char(spc) && P.glowna_tab[i][1] == ico){
				++nastepny;
				for(int j = 2; j < 5; j++){
					if(P.glowna_tab[i][j] == ico){
						++nastepny;
					}
				}
				if(P.glowna_tab[i][5] == ico){
					nastepny = 0;
				}	
			}
			else if(P.glowna_tab[i][1] != char(spc) && P.glowna_tab[i][1] != ico){
				nastepny = 1;
				ico = P.glowna_tab[i][1];
				for(int j = 2; j < 6; j++){
					if(P.glowna_tab[i][j] == ico){
						++nastepny;
					}	
				}	
			}
			if(nastepny == 5){
				if(ico == A.ikona){
					cout << "wygrywa gracz1" << endl;
					return 'w';
				}	
				else if(ico == B.ikona){
					cout << "wygrywa gracz2" << endl;
					return 'w';
				}
			}	
		}else{
			ico = P.glowna_tab[i][1];
			nastepny = 1;
			for(int j = 2; j < 6; j++){
				if(P.glowna_tab[i][j] == ico){
					++nastepny;
				}
			}	
			if(nastepny == 5){
				if(ico == A.ikona){
					cout << "wygrywa gracz1" << endl;
					return 'w';
				}	
				else if(ico == B.ikona){
					cout << "wygrywa gracz2" << endl;
					return 'w';
				} 
			}	
		}
	}
	// wygrana po ukosach
	//
	//
	//
	ico = P.glowna_tab[0][1];
	nastepny = 1;
	for(int i  = 1; i < 6 ; i++){
		if(P.glowna_tab[i][i+1] == ico){
			++nastepny;
		}
	}
	if(nastepny == 5){
		if(ico == A.ikona){
			cout << "wygrywa gracz1" << endl;
			return 'w';
		}	
		else if(ico == B.ikona){
			cout << "wygrywa gracz2" << endl;
			return 'w';
		} 
	}

	ico = P.glowna_tab[1][0];
	nastepny = 1;
	for(int i  = 1; i < 6 ; i++){
		if(P.glowna_tab[i+1][i] == ico){
			++nastepny;
		}
	}
	if(nastepny == 5){
		if(ico == A.ikona){
			cout << "wygrywa gracz1" << endl;
			return 'w';
		}	
		else if(ico == B.ikona){
			cout << "wygrywa gracz2" << endl;
			return 'w';
		} 
	}

	ico = P.glowna_tab[4][0];
	nastepny = 1;
	for(int i  = 3; i >= 0 ; i--){
		if(P.glowna_tab[i][4-i] == ico){
			++nastepny;
		}
	}
	if(nastepny == 5){
		if(ico == A.ikona){
			cout << "wygrywa gracz1" << endl;
			return 'w';
		}	
		else if(ico == B.ikona){
			cout << "wygrywa gracz2" << endl;
			return 'w';
		} 
	}

	ico = P.glowna_tab[5][1];
	nastepny = 1;
	for(int i  = 4; i > 0 ; i--){
		if(P.glowna_tab[i][6-i] == ico){
			++nastepny;
		}
	}
	if(nastepny == 5){
		if(ico == A.ikona){
			cout << "wygrywa gracz1" << endl;
			return 'w';
		}	
		else if(ico == B.ikona){
			cout << "wygrywa gracz2" << endl;
			return 'w';
		} 
	}

	if(P.glowna_tab[0][0] != char(spc)){
		ico = P.glowna_tab[0][0];
		
		nastepny = 1;
		if(P.glowna_tab[1][1] != char(spc) && P.glowna_tab[1][1] == ico){
			++nastepny;
			for(int j = 2; j < 5; j++){
				if(P.glowna_tab[j][j] == ico){
					++nastepny;
				}
			}
			if(P.glowna_tab[5][5] == ico){
				nastepny = 0;
			}
			
		}
		else if(P.glowna_tab[1][1] != char(spc) && P.glowna_tab[1][1] != ico){
			nastepny = 1;
			ico = P.glowna_tab[1][1];
			for(int j = 2; j < 6; j++){
				if(P.glowna_tab[j][j] == ico){
					++nastepny;
				}	
			}
			
		}
		if(nastepny == 5){
			if(ico == A.ikona){
				cout << "wygrywa gracz1" << endl;
				return 'w';
			}	
			else if(ico == B.ikona){
				cout << "wygrywa gracz2" << endl;
				return 'w';
			} 
		}
		
	}else{
		ico = P.glowna_tab[1][1];
		nastepny = 1;
		for(int j = 2; j < 6; j++){
			if(P.glowna_tab[j][j] == ico){
				++nastepny;
			}
		}
		
		
		if(nastepny == 5){
			if(ico == A.ikona){
				cout << "wygrywa gracz1" << endl;
				return 'w';
			}	
			else if(ico == B.ikona){
				cout << "wygrywa gracz2" << endl;
				return 'w';
			} 
		}
		
	}

	if(P.glowna_tab[5][0] != char(spc)){
		ico = P.glowna_tab[5][0];
		
		nastepny = 1;
		if(P.glowna_tab[4][1] != char(spc) && P.glowna_tab[4][1] == ico){
			++nastepny;
			for(int j = 3; j > 0; j--){
				if(P.glowna_tab[j][5-j] == ico){
					++nastepny;
				}
			}
			if(P.glowna_tab[0][5] == ico){
				nastepny = 0;
			}
			 
		}
		else if(P.glowna_tab[4][1] != char(spc) && P.glowna_tab[4][1] != ico){
			nastepny = 1;
			ico = P.glowna_tab[4][1];
			for(int j = 3; j >= 0; j--){
				if(P.glowna_tab[j][5-j] == ico){
					++nastepny;
				}	
			}
			
		}
		if(nastepny == 5){
			if(ico == A.ikona){
				cout << "wygrywa gracz1" << endl;
				return 'w';
			}	
			else if(ico == B.ikona){
				cout << "wygrywa gracz2" << endl;
				return 'w';
			} 
		}
		
	}else{
		ico = P.glowna_tab[4][1];
		nastepny = 1;
		for(int j = 3; j >= 0; j--){
			if(P.glowna_tab[j][5-j] == ico){
				++nastepny;
			}
		}
		
		
		if(nastepny == 5){
			if(ico == A.ikona){
				cout << "wygrywa gracz1" << endl;
				return 'w';
			}	
			else if(ico == B.ikona){
				cout << "wygrywa gracz2" << endl;
				return 'w';
			} 
		}
		
	}
	//remis
	int r = 0;
	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 6; j++){
			if(P.glowna_tab[i][j] == ' '){
				r++;
				
			}
		}
	}
	if(r == 0){
		return 'r';
	}
}

void obrot_tablicy(Plansza *P, char x, char y){
	if(x == 'q'){
		if(y == 'z'){
			char temp = P->tab1[0];
			P->tab1[0] = P->tab1[6];
			P->tab1[6] = P->tab1[8];
			P->tab1[8] = P->tab1[2];
			P->tab1[2] = temp;
			temp = P->tab1[1];
			P->tab1[1] = P->tab1[3];
			P->tab1[3] = P->tab1[7];
			P->tab1[7] = P->tab1[5];
			P->tab1[5] = temp;
			P->aktualizuj();
		}
		else if(y == 'x'){
			
			char temp = P->tab1[0];
			P->tab1[0] = P->tab1[2];
			P->tab1[2] = P->tab1[8];
			P->tab1[8] = P->tab1[6];
			P->tab1[6] = temp;
			temp = P->tab1[1];
			P->tab1[1] = P->tab1[5];
			P->tab1[5] = P->tab1[7];
			P->tab1[7] = P->tab1[3];
			P->tab1[3] = temp;
			P->aktualizuj();
		}
	}
	else if(x == 'w'){
		if(y == 'z'){
			char temp = P->tab2[0];
			P->tab2[0] = P->tab2[6];
			P->tab2[6] = P->tab2[8];
			P->tab2[8] = P->tab2[2];
			P->tab2[2] = temp;
			temp = P->tab2[1];
			P->tab2[1] = P->tab2[3];
			P->tab2[3] = P->tab2[7];
			P->tab2[7] = P->tab2[5];
			P->tab2[5] = temp;
			P->aktualizuj();
		}
		else if(y == 'x'){
			char temp = P->tab2[0];
			P->tab2[0] = P->tab2[2];
			P->tab2[2] = P->tab2[8];
			P->tab2[8] = P->tab2[6];
			P->tab2[6] = temp;
			temp = P->tab2[1];
			P->tab2[1] = P->tab2[5];
			P->tab2[5] = P->tab2[7];
			P->tab2[7] = P->tab2[3];
			P->tab2[3] = temp;
			P->aktualizuj();
		}	
	}
	else if(x == 'a'){
		if(y == 'z'){
			char temp = P->tab3[0];
			P->tab3[0] = P->tab3[6];
			P->tab3[6] = P->tab3[8];
			P->tab3[8] = P->tab3[2];
			P->tab3[2] = temp;
			temp = P->tab3[1];
			P->tab3[1] = P->tab3[3];
			P->tab3[3] = P->tab3[7];
			P->tab3[7] = P->tab3[5];
			P->tab3[5] = temp;
			P->aktualizuj();
		}
		else if(y == 'x'){
			char temp = P->tab3[0];
			P->tab3[0] = P->tab3[2];
			P->tab3[2] = P->tab3[8];
			P->tab3[8] = P->tab3[6];
			P->tab3[6] = temp;
			temp = P->tab3[1];
			P->tab3[1] = P->tab3[5];
			P->tab3[5] = P->tab3[7];
			P->tab3[7] = P->tab3[3];
			P->tab3[3] = temp;
			P->aktualizuj();
		}
	}
	else if(x == 's'){
		if(y == 'z'){
			char temp = P->tab4[0];
			P->tab4[0] = P->tab4[6];
			P->tab4[6] = P->tab4[8];
			P->tab4[8] = P->tab4[2];
			P->tab4[2] = temp;
			temp = P->tab4[1];
			P->tab4[1] = P->tab4[3];
			P->tab4[3] = P->tab4[7];
			P->tab4[7] = P->tab4[5];
			P->tab4[5] = temp;
			P->aktualizuj();
		}
		else if(y == 'x'){
			char temp = P->tab4[0];
			P->tab4[0] = P->tab4[2];
			P->tab4[2] = P->tab4[8];
			P->tab4[8] = P->tab4[6];
			P->tab4[6] = temp;
			temp = P->tab4[1];
			P->tab4[1] = P->tab4[5];
			P->tab4[5] = P->tab4[7];
			P->tab4[7] = P->tab4[3];
			P->tab4[3] = temp;
			P->aktualizuj();
		}	
	}	
}

void wprowadz_komende_2(Plansza &P, char &ico, Gracz &A, Gracz &B, int x, clock_t &start, clock_t &stop, int info){
	Gracz *wGr1 = &A;
	Gracz *wGr2 = &B;
	Plansza *wskP = &P;
	double roznica;
	char komenda[2];
	bool petla = true;
	bool petla_2;
	string opcja_2;
	while(petla){
		petla_2 = true;
		cout << "podaj komende / h - pomoc" << endl;
		cin >> komenda;
		cin.ignore(200, '\n');
		if(!(strlen(komenda) > 2) && !(strlen(komenda) == 0)){
			if(strlen(komenda) == 1){
				switch(komenda[0]){
					case 'p':
						stop = clock();
						roznica = (double) (stop - start)/CLOCKS_PER_SEC;
						if(x == 1){
							A.czas -= roznica;
						}
						else if(x == -1){
							B.czas -= roznica;
						}
						petla_2 = true;
						while(petla_2){
							system("cls");
							cout << "PAUZA" << endl;
							cout << "p - powrot: ";
							cin >> opcja_2;
							cin.ignore(200, '\n');
							if(opcja_2[0] == 'p'){
								system("cls");
								start = clock();
								if(info*x == 1){
									wyswietl_dane(A, B, "kolko krzyzyk");
								}
								else if(info*x == -1){
									wyswietl_dane(A, B, "pentago");
								}
								wyswietl_kolejke(A, B, x);
								generuj_plansze(P, dvert, spc);
								petla_2 = false;
							}else{
								cout << "zle dane!" << endl;
							}
						}
						break;
					case 'h':
						stop = clock();
						roznica = (double) (stop - start)/CLOCKS_PER_SEC;
						if(x == 1){
							A.czas -= roznica;
						}
						else if(x == -1){
							B.czas -= roznica;
						}
						while(petla_2){
							system("cls");
							cout << "Opis gry:...................... " << endl;
							cout << "q,w,a,s - wybor czesci planszy" << endl;
							cout << "odpowiednio: lewej gornej, prawej gornej, lewej dolnej, prawej dolnej" << endl;
							cout << "z,x - obrot odpowiednio: zgodnie z ruchem wskazowek zegara i odwrotnie" << endl;
							cout << endl << "m - zmiana zetonu" << endl;
							cout << "h - powrot: ";
							cin >> opcja_2;
							cin.ignore(200, '\n');
							if(opcja_2[0] == 'h'){
								system("cls");
								start = clock();
								if(info*x == 1){
									wyswietl_dane(A, B, "kolko krzyzyk");
								}
								else if(info*x == -1){
									wyswietl_dane(A, B, "pentago");
								}
								wyswietl_kolejke(A, B, x);
								generuj_plansze(P, dvert, spc);
								petla_2 = false;
								
							}else{
								cout << "zle dane!" << endl;
							}
						}
						break;
					case 'm':
						stop = clock();
						roznica = (double) (stop - start)/CLOCKS_PER_SEC;
						if(x == 1){
							A.czas -= roznica;
						}
						else if(x == -1){
							B.czas -= roznica;
						}
						while(petla_2){
							system("cls");
							cout << "Ustawione zetony    " << "A: " << A.nazwa << ": " << A.ikona << " , B: " << B.nazwa<< ": " << B.ikona << endl;
							if(x == 1){
								wybor_zetonu(P, wGr1, wGr2);
								ico = A.ikona;
							}
							else if(x == -1){
								wybor_zetonu(P, wGr2, wGr1);
								ico = B.ikona;
							}
							cout << "m - powrot: ";
							cin >> opcja_2;
							cin.ignore(200, '\n');
							if(opcja_2[0] == 'm'){
								system("cls");
								start = clock();
								if(info*x == 1){
									wyswietl_dane(A, B, "kolko krzyzyk");
								}
								else if(info*x == -1){
									wyswietl_dane(A, B, "pentago");
								}
								wyswietl_kolejke(A, B, x);
								generuj_plansze(P, dvert, spc);
								petla_2 = false;
							}
						}
						break;					
					default:
						cout << "zla komenda!" << endl;
						break;						
				}
			}
			else if(strlen(komenda) == 2){
				if(!(strlen(komenda) > 2) && !(strlen == 0)){
					if(komenda[0] == 'q'){
						if(!isdigit(komenda[1])){
							obrot_tablicy(wskP, komenda[0], komenda[1]);
							petla = false;
						}
					}
					else if(komenda[0] == 'w'){
						if(!isdigit(komenda[1])){
							obrot_tablicy(wskP, komenda[0], komenda[1]);
							petla = false;
						}
					}
					else if(komenda[0] == 'a'){
						if(!isdigit(komenda[1])){
							obrot_tablicy(wskP, komenda[0], komenda[1]);
							petla = false;
						}
					}	
					else if(komenda[0] == 's'){
						if(!isdigit(komenda[1])){
							obrot_tablicy(wskP, komenda[0], komenda[1]);
							petla = false;
						}
					}	
				}
			}
		}
	}
}
