#include <iostream>
#include <fstream>
#include <locale.h>
using namespace std;


int wiersze = 0, kolumny = 0;
int w1 = 0, w2 = 0, k1 = 0, k2 = 0;
int bx1 = 0, bx2 = 0, by1 = 0, by2 = 0;//zmienne wyboru pionka
int bbx1 = 0, bbx2 = 0, bbxx2=0, bbxx1=0, bby1=0, bbyy1 = 0, bby2 = 0, bbyy2=0;//zmienne wybioru pionka
int x = 0, xx = 0, y = 0, yy = 0;

int i = 0, j = 0;
int nr = 0;
char plansza1[8][8] = {	   	' ','B',' ','B',' ','B',' ','B',
							  'B',' ','B',' ','B',' ','B',' ',
							  ' ','B',' ','B',' ','B',' ','B',
							  'X',' ','X',' ','X',' ','X',' ',
							  ' ','X',' ','X',' ','X',' ','X',
							  'C',' ','C',' ','C',' ','C',' ',
							  ' ','C',' ','C',' ','C',' ','C',
							  'C',' ','C',' ','C',' ','C',' '
};
char** plansza2;

class Plansza {
public:
	friend void wybor_bialego_piona_1();
	friend void wybor_czarnego_piona_1();
	friend void ruch_bialego_gracza_1();
	friend void ruch_czarnego_gracza_1();
	friend void wybor_bialego_piona_2();
	friend void ruch_bialego_gracza_2();
	friend void wybor_czarnego_piona_2();
	friend void ruch_czarnego_piona_2();

	void gotowa_plansza_1() {
		cout << 0 << " " << 1 << " " << 2 << " " << 3 << " " << 4 << " " << 5 << " " << 6 << " " << 7 << " " << 8 << endl;

		for (int i = 0; i < 8; i++) {
			nr++;
			cout << nr << " ";
			for (int j = 0; j < 8; j++)
			{
				cout << plansza1[i][j] << "|";
			}
			cout << endl;

		}
	}

	void okresl_plansze_2() {
		cout << "Podaj liczbę wierszy i kolumn (najmniejsza powierzchnia planszy to 8x8). " << endl;
		cout << "Liczba wierszy: " << endl;
		cin >> wiersze;
		cout << "Liczba kolumn: " << endl;
		cin >> kolumny;
		if (wiersze < 8 || kolumny < 8) {
			cout << "Wpisałeś za mało wierszy i(lub) kolumn, wpisz jeszcze raz: " << endl;
			okresl_plansze_2();
		}
		else {
			cout << "Wpisałes prawidłowe liczby wierszy i kolumn, wymiary Twojej planszy to: " << endl;
			cout << "Wiersze: " << wiersze << endl;
			cout << "Kolumny: " << kolumny << endl;
			cout << endl;
		}

		plansza2 = new char* [wiersze];

		for (int i = 0; i < wiersze; i++)
			plansza2[i] = new char[kolumny];

		for (int i = 0; i < 1; i++) {
			for (int j = 0; j < kolumny + 1; j++) {
				cout << j << " ";
			}
			cout << endl;
		}
	}

	void rysuj_plansze_2() {
		//gorna czesc planszy
		for (int i = 0; i < 1; i += 2)
			for (int j = 0; j < kolumny; j += 2)
				plansza2[i][j] = ' ';
		for (int i = 0; i < 1; i += 2)
			for (int j = 1; j < kolumny; j += 2)
				plansza2[i][j] = 'B';

		for (int i = 1; i < 2; i += 2)
			for (int j = 0; j < kolumny; j += 2)
				plansza2[i][j] = 'B';
		for (int i = 1; i < 2; i += 2)
			for (int j = 1; j < kolumny; j += 2)
				plansza2[i][j] = ' ';

		for (int i = 2; i < 3; i += 2)
			for (int j = 0; j < kolumny; j += 2)
				plansza2[i][j] = ' ';
		for (int i = 2; i < 3; i += 2)
			for (int j = 1; j < kolumny; j += 2)
				plansza2[i][j] = 'B';

		//dolna czesc planszy
		for (int i = wiersze - 1; i < wiersze; i += 2)
			for (int j = 0; j < kolumny; j += 2)
				plansza2[i][j] = 'C';
		for (int i = wiersze - 1; i < wiersze; i += 2)
			for (int j = 1; j < kolumny; j += 2)
				plansza2[i][j] = ' ';

		for (int i = wiersze - 2; i < wiersze; i += 2)
			for (int j = 0; j < kolumny; j += 2)
				plansza2[i][j] = ' ';
		for (int i = wiersze - 2; i < wiersze; i += 2)
			for (int j = 1; j < kolumny; j += 2)
				plansza2[i][j] = 'C';

		for (int i = wiersze - 3; i < wiersze; i += 2)
			for (int j = 0; j < kolumny; j += 2)
				plansza2[i][j] = 'C';
		for (int i = wiersze - 3; i < wiersze; i += 2)
			for (int j = 1; j < kolumny; j += 2)
				plansza2[i][j] = ' ';

		//srodkowa czesc planszy
		for (int i = 3; i < wiersze - 3; i++)
			for (int j = 0; j < kolumny; j++)
				plansza2[i][j] = ' ';


		for (int i = 0; i < wiersze; i++) {
			cout << "";
			nr++;
			cout << nr << " ";
			for (int j = 0; j < kolumny; j++) {
				cout << plansza2[i][j] << "|";
			}
			cout << endl;
		}
		cout << endl;

	}

};


void wybor_bialego_piona_1() {/*uzycie zaprzyjaznionej funkcji do klasy, funkcja kontroluje prawidlowy wybor piona,
	nie mozna wybrac piona innego niz bialy i piona, ktory nie lezy na linii ofensywnej*/

	cout << "Wybierz białego pionka, którym chcesz ruszyć (podaj kolejno wiersz i pole, na którym pionek się znajduje). " << endl;
	cout << "Wiersze: " << endl;
	cin >> bx1;
	cout << "Kolumny: " << endl;
	cin >> by1;
	bbx1 = bx1 - 1;
	bbxx1 = bx1 + 1;
	bby1 = by1 - 1;
	bbyy1 = by1 - 2;

	if ((plansza1[bbx1][bby1]=='B')&&((plansza1[bx1][by1] == 'X') || (plansza1[bx1][by1] == ' ')) && ((plansza1[bx1][bbyy1] == 'X') || (plansza1[bx1][bbyy1] == ' '))) {
	
			cout << "Wybrałeś odpowiedniego pionka." << endl;
			bbx1 = bx1 - 1;
			bby1 = by1 - 1;
			plansza1[bbx1][bby1] = 'X';
		
	}

	
	else {
		cout << "Wybrałeś nieodpowiedniego pionka, spróbuj ponownie. " << endl;
			wybor_bialego_piona_1();
	}



};
void wybor_czarnego_piona_1() {
	cout << "Wybierz czarnego pionka, którym chcesz ruszyć (podaj kolejno wiersz i pole, na którym pionek się znajduje). " << endl;
	cout << "Wiersze: " << endl;
	cin >> bx1;
	cout << "Kolumny: " << endl;
	cin >> by1;
	bbx1 = bx1 - 1;
	bbxx1 = bx1 -2;
	bby1 = by1 - 1;
	bbyy1 = by1 - 2;


	if ((plansza1[bbx1][bby1] == 'C') && ((plansza1[bbxx1][bbyy1] == 'X') || (plansza1[bbxx1][bbyy1] == ' ')) && ((plansza1[bbxx1][by1] == 'X') || (plansza1[bbxx1][by1] == ' '))) {
			bbx1 = bx1 - 1;
			bby1 = by1 - 1;
			plansza1[bbx1][bby1] = 'X';
		cout << "Wybrałeś odpowiedniego pionka." << endl;
	}
	else {
		cout << "Wybrałeś nieodpowiedniego pionka, spróbuj ponownie. " << endl;
		wybor_czarnego_piona_1();
	}

};

void ruch_bialego_gracza_1() {/*uzycie zaprzyjaznionej funkcji do klasy, funkcja kontroluje ruch bialego
		gracza, gracz nie moze sie ruszyc na inne pole, niz okreslone w regulach gry*/

	
	cout << "Wybierz pole, na które chcesz ruszyć (podaj kolejno wiersz i pole, na którym pionek ma się znajdować). " << endl;
	cout << "Wiersze: " << endl;
	cin >> x;
	cout << "Kolumny: " << endl;
	cin >> y;
	
	
	
	if (y%2!=2) {

		cout << "Wybrałeś dozwolony ruch. " << endl;

		int odp;
		cout << "Żeby zaktualizować planszę - wciśnij 1. ";
		cin >> odp;
		if (odp == 1) {
			system("cls");

			cout << "Trwa aktualizacja planszy: " << endl;

			w1 = x - 1;
			k1 = y - 1;
			plansza1[w1][k1] = 'B';

			cout << 0 << " " << 1 << " " << 2 << " " << 3 << " " << 4 << " " << 5 << " " << 6 << " " << 7 << " " << 8 << endl;

			nr = 0;
			for (int i = 0; i < 8; i++) {
				nr++;
				cout << nr << " ";
				for (int j = 0; j < 8; j++)
				{
					cout << plansza1[i][j] << "|";
				}
				cout << endl;

			}
		}

	}
	
		else {
			cout << "Wybrałeś niedozwolony ruch, spróbuj ponownie. " << endl;
			ruch_bialego_gracza_1();
		}
	
}
void ruch_czarnego_gracza_1() {
	cout << "Wybierz pole, na które chcesz ruszyć (podaj kolejno wiersz i pole, na którym pionek ma się znajdowac). " << endl;
	cout << "Wiersze: " << endl;
	cin >> x;
	cout << "Kolumny: " << endl;
	cin >> y;

	if (y % 2 == 0) {
		cout << "Wybraleś dozwolony ruch. " << endl;

		int odp;
		cout << "Żeby zaktualizować planszę - wciśnij 1. ";
		cin >> odp;
		if (odp == 1) {
			system("cls");

			cout << "Trwa aktualizacja planszy: " << endl;

			w1 = x - 1;
			k1 = y - 1;
			plansza1[w1][k1] = 'C';

			cout << 0 << " " << 1 << " " << 2 << " " << 3 << " " << 4 << " " << 5 << " " << 6 << " " << 7 << " " << 8 << endl;

			nr = 0;
			for (int i = 0; i < 8; i++) {
				nr++;
				cout << nr << " ";
				for (int j = 0; j < 8; j++)
				{
					cout << plansza1[i][j] << "|";
				}
				cout << endl;

			}


		}
	}

	else {
		cout << "Wybrałeś niedozwolony ruch, spróbuj ponownie. " << endl;
		ruch_czarnego_gracza_1();
	}
}

void wybor_bialego_piona_2() {/*uzycie zaprzyjaznionej funkcji do klasy, funkcja kontroluje prawidlowy wybor piona,
	nie mozna wybrac piona innego niz bialy i piona, ktory nie lezy na linii ofensywnej*/

	cout << "Wybierz białego pionka, którym chcesz ruszyć (podaj kolejno wiersz i pole, na którym pionek się znajduje). " << endl;
	cout << "Wiersze: " << endl;
	cin >> bx2;
	cout << "Kolumny: " << endl;
	cin >> by2;

	bbx2 = bx2 - 1;
	bbxx2 = bx2 + 1;
	bby2 = by2 - 1;
	bbyy2 = by2 - 2;

	if ((plansza2[bbx2][bby2] == 'B') && ((plansza2[bx2][by2] == 'X') || (plansza2[bx2][by2] == ' ')) && ((plansza2[bx2][bbyy2] == 'X') || (plansza2[bx2][bbyy2] == ' '))) {

		cout << "Wybrałeś odpowiedniego pionka." << endl;
		bbx1 = bx2 - 1;
		bby1 = by2 - 1;
		plansza2[bbx2][bby2] = 'X';

	}
	
	
	else {
		cout << "Wybrałeś nieodpowiedniego pionka, spróbuj ponownie. " << endl;
		wybor_bialego_piona_2();
	}



}


void ruch_bialego_gracza_2() {/*uzycie zaprzyjaznionej funkcji do klasy, funkcja kontroluje ruch bialego
	gracza, gracz nie moze sie ruszyc na inne pole, niz okreslone w regulach gry*/


	cout << "Wybierz pole, na które chcesz ruszyc (podaj kolejno wiersz i pole, na którym pionek ma się znajdować). " << endl;
	cout << "Wiersze: " << endl;
	cin >> xx;
	cout << "Kolumny: " << endl;
	cin >> yy;




	if (yy % 2 != 0) {
		cout << "Wybrałeś dozwolony ruch. " << endl;

		int odp;
		cout << "Żeby zaktualizować planszę - wcisnij 1. ";
		cin >> odp;
		if (odp == 1) {
			system("cls");

			cout << "Trwa aktualizacja planszy: " << endl;

			w2 = xx - 1;
			k2 = yy - 1;


			for (int i = 0; i < 1; i++) {
				for (int j = 0; j < kolumny + 1; j++) {
					cout << j << " ";
				}
				cout << endl;
			}

			plansza2[w2][k2] = 'B';
			int nr = 0;
			for (int i = 0; i < wiersze; i++) {
				cout << "";
				nr++;
				cout << nr << " ";
				for (int j = 0; j < kolumny; j++) {
					cout << plansza2[i][j] << "|";
				}
				cout << endl;
			}

		}
	}

	else {
		cout << "Wybrałeś niedozwolony ruch, spróbuj ponownie. " << endl;
		ruch_bialego_gracza_2();
	}

}

void wybor_czarnego_piona_2() {/*uzycie zaprzyjaznionej funkcji do klasy, funkcja kontroluje prawidlowy wybor piona,
	nie mozna wybrac piona innego niz bialy i piona, ktory nie lezy na linii ofensywnej*/

	cout << "Wybierz czarnego pionka, którym chcesz ruszyć (podaj kolejno wiersz i pole, na którym pionek się znajduje). " << endl;
	cout << "Wiersze: " << endl;
	cin >> bx2;
	cout << "Kolumny: " << endl;
	cin >> by2;
	bbx2 = bx2 - 1;
	bbxx2 = bx2 - 2;
	bby2 = by2 - 1;
	bbyy2 = by2 - 2;


	if ((plansza2[bbx2][bby2] == 'C') && ((plansza2[bbxx2][bbyy2] == 'X') || (plansza2[bbxx2][bbyy2] == ' ')) && ((plansza2[bbxx2][by2] == 'X') || (plansza2[bbxx2][by2] == ' '))) {
		bbx2 = bx2 - 1;
		bby2 = by2 - 1;
		plansza2[bbx2][bby2] = 'X';
		cout << "Wybrałeś odpowiedniego pionka." << endl;
	}
	else {
		cout << "Wybrałeś nieodpowiedniego pionka, spróbuj ponownie. " << endl;
		wybor_czarnego_piona_2();
	}

}


void ruch_czarnego_gracza_2() {/*uzycie zaprzyjaznionej funkcji do klasy, funkcja kontroluje ruch bialego
	gracza, gracz nie moze sie ruszyc na inne pole, niz okreslone w regulach gry*/


	cout << "Wybierz pole, na które chcesz ruszyć (podaj kolejno wiersz i pole, na którym pionek ma sie znajdować). " << endl;
	cout << "Wiersze: " << endl;
	cin >> xx;
	cout << "Kolumny: " << endl;
	cin >> yy;




	if ((yy % 2 == 0) && (xx == wiersze - 3)) {
		cout << "Wybrałeś dozwolony ruch. " << endl;

		int odp;
		cout << "Żeby zaktualizować planszę wciśnij 1. ";
		cin >> odp;
		if (odp == 1) {
			system("cls");

			cout << "Trwa aktualizacja planszy: " << endl;

			w2 = xx - 1;
			k2 = yy - 1;


			for (int i = 0; i < 1; i++) {
				for (int j = 0; j < kolumny + 1; j++) {
					cout << j << " ";
				}
				cout << endl;
			}

			plansza2[w2][k2] = 'C';
			int nr = 0;
			for (int i = 0; i < wiersze; i++) {
				cout << "";
				nr++;
				cout << nr << " ";
				for (int j = 0; j < kolumny; j++) {
					cout << plansza2[i][j] << "|";
				}
				cout << endl;
			}

		}
	}

	else {
		cout << "Wybrałes niedozwolony ruch, spróbuj ponownie. " << endl;
		ruch_czarnego_gracza_2();
	}

}
int main()
{
	setlocale(LC_CTYPE, "Polish");
	Plansza plansza_1;
	Plansza plansza_2;
	cout << "\t\t\t" << "Witaj w grze WARCABY" << endl;
	cout << "Wybierz planszę do gry (możesz wybrać gotowy rozmiar (8x8 pól) lub wpisać własny)." << endl;
	int odpowiedz;
	cout << "Jeśli wybierasz gotowy rozmiar wciśnij 1, jeśli chcesz wpisać własny rozmiar wciśnij 2. " << endl;
	cin >> odpowiedz;

	switch (odpowiedz) {//opcja wyboru planszy
	case 1:
		cout << "Wybrałeś gotowy rozmiar (8x8). " << endl;
		plansza_1.gotowa_plansza_1();
		cout << "Gotowy? Gramy! Zaczyna biały gracz. " << endl;
		do {
			wybor_bialego_piona_1();
			ruch_bialego_gracza_1();
			wybor_czarnego_piona_1();
			ruch_czarnego_gracza_1();
		} while (i == 0);

		break;

	case 2:
		plansza_2.okresl_plansze_2();
		plansza_2.rysuj_plansze_2();
		cout << "Gotowy? Gramy! Zaczyna biały gracz. " << endl;
		do {
			wybor_bialego_piona_2();
			ruch_bialego_gracza_2();
			wybor_czarnego_piona_2();
			ruch_czarnego_gracza_2();
		} while (i == 0);

		for (int i = 0; i < wiersze; i++)//zwalnianie pamieci w tablicy dynamicznej
			delete[] plansza2[i];
		delete[] plansza2;

		break;

	default:
		cout << "Nie wybrałeś żadnej opcji. Gra zamknie się po wciśnięciu dowolnego klawisza." << endl;
		return 0;
	}


	return 0;
}