#include <iostream>
using namespace std;

int wiersze, kolumny;
int x, y;
int nr = 0;
char** plansza;

void gotowa_plansza() {
	char plansza[8][8] = { 'O','B','O','B','O','B','O','B',
						  'B','O','B','O','B','O','B','O',
						  'O','B','O','B','O','B','O','B',
						  'X','O','X','O','X','O','X','O',
						  'O','X','O','X','O','X','O','X',
						  'C','O','C','O','C','O','C','O',
						  'O','C','O','C','O','C','O','C',
						  'C','O','C','O','C','O','C','O'
	};
	cout << 0 << " " << 1 << " " << 2 << " " << 3 << " " << 4 << " " << 5 << " " << 6 << " " << 7 << " " << 8 << endl;

	for (int i = 0; i < 8; i++) {
		nr++;
		cout << nr << " ";
		for (int j = 0; j < 8; j++)
		{
			cout << plansza[i][j] << "|";
		}
		cout << endl;

		
	}

}
void rysuj_plansze() {
	cout << "Podaj liczbe wierszy i kolumn (najmniejsza powierzchnia planszy to 8x8). " << endl;
	cout << "Liczba wierszy: " << endl;
	cin >> wiersze;
	cout << "Liczba kolumn: " << endl;
	cin >> kolumny;
	if (wiersze < 8 || kolumny < 8) {
		cout << "Wpisales za malo wierszy i(lub) kolumn, wpisz jeszcze raz: " << endl;
		rysuj_plansze();
	}
	else {
		cout << "Wpisales prawidlowe liczby wierszy i kolumn, wymiary Twojej planszy to: " << endl;
		cout << "Wiersze: " << wiersze << endl;
		cout << "Kolumny: " << kolumny << endl;
		cout << endl;
	}


	plansza = new char* [wiersze];

	for (int i = 0; i < wiersze; i++)
		plansza[i] = new char[kolumny];


	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < kolumny + 1; j++) {
			cout << j << " ";
		}
		cout << endl;
	}

	//gorna czesc planszy
	for (int i = 0; i < 1; i += 2)
		for (int j = 0; j < kolumny; j += 2)
			plansza[i][j] = 'O';
	for (int i = 0; i < 1; i += 2)
		for (int j = 1; j < kolumny; j += 2)
			plansza[i][j] = 'B';

	for (int i = 1; i < 2; i += 2)
		for (int j = 0; j < kolumny; j += 2)
			plansza[i][j] = 'B';
	for (int i = 1; i < 2; i += 2)
		for (int j = 1; j < kolumny; j += 2)
			plansza[i][j] = 'O';

	for (int i = 2; i < 3; i += 2)
		for (int j = 0; j < kolumny; j += 2)
			plansza[i][j] = 'O';
	for (int i = 2; i < 3; i += 2)
		for (int j = 1; j < kolumny; j += 2)
			plansza[i][j] = 'B';

	//dolna czesc planszy
	for (int i = wiersze - 1; i < wiersze; i += 2)
		for (int j = 0; j < kolumny; j += 2)
			plansza[i][j] = 'C';
	for (int i = wiersze - 1; i < wiersze; i += 2)
		for (int j = 1; j < kolumny; j += 2)
			plansza[i][j] = 'O';

	for (int i = wiersze - 2; i < wiersze; i += 2)
		for (int j = 0; j < kolumny; j += 2)
			plansza[i][j] = 'O';
	for (int i = wiersze - 2; i < wiersze; i += 2)
		for (int j = 1; j < kolumny; j += 2)
			plansza[i][j] = 'C';

	for (int i = wiersze - 3; i < wiersze; i += 2)
		for (int j = 0; j < kolumny; j += 2)
			plansza[i][j] = 'C';
	for (int i = wiersze - 3; i < wiersze; i += 2)
		for (int j = 1; j < kolumny; j += 2)
			plansza[i][j] = 'O';

	//srodkowa czesc planszy
	for (int i = 3; i < wiersze - 3; i += 2)
		for (int j = 0; j < kolumny; j += 2)
			plansza[i][j] = 'X';
	for (int i = 3; i < wiersze - 3; i += 2)
		for (int j = 1; j < kolumny; j += 2)
			plansza[i][j] = 'O';

	for (int i = 4; i < wiersze - 3; i += 2)
		for (int j = 0; j < kolumny; j += 2)
			plansza[i][j] = 'O';
	for (int i = 4; i < wiersze - 3; i += 2)
		for (int j = 1; j < kolumny; j += 2)
			plansza[i][j] = 'X';

	for (int i = 0; i < wiersze; i++) {
		cout << "";
		nr++;
		cout << nr << " ";
		for (int j = 0; j < kolumny; j++) {
			cout << plansza[i][j] << "|";
		}
		cout << endl;
	}
	cout << endl;
	
}
void wybor_bialego_piona() {
	
	cout << "Wybierz pierwszego pionka, ktorym chcesz ruszyc (podaj kolejno wiersz i pole, na ktorym pionek sie znajduje). " << endl;
	cout << "Wiersze: " << endl;
	cin >> x;
	cout << "Kolumny: " << endl;
	cin >> y;


	if ((y % 2 == 0) && (x == 3)) {
		cout << "Wybrales odpowiedniego pionka. " << endl;
	}
	else {
		cout << "Wybrales nieodpowiedniego pionka, sprobuj ponownie. " << endl;
		wybor_bialego_piona();

	}


}
void ruch_bialego_gracza() {
	
	cout << "Wybierz pole, na ktore chcesz ruszyc (podaj kolejno wiersz i pole, na ktorym pionek ma sie znajdowac). " << endl;
	cout << "Wiersze: " << endl;
	cin >> x;
	cout << "Kolumny: " << endl;
	cin >> y;


	if ((y % 2 != 0) && (x == 4)) {
		cout << "Wybrales dozwolony ruch. " << endl;
		
	}

	else {
		cout << "Wybrales niedozwolony ruch, sprobuj ponownie. " << endl;
		ruch_bialego_gracza();
	}

	int odp;
	cout << "Zeby zaktualizowac plansze wcisnij 1. ";
	cin >> odp;
	if (odp == 1) {
		system("cls");
		cout << "Trwa aktualizacja planszy: " << endl;
		
	}
	
	
};


int main()
{
	cout << "Witaj w grze WARCABY" << endl;
	cout << "Wybierz plansze do gry (mozesz wybrac gotowy rozmiar (8x8 pol) lub wpisac wlasny)." << endl;
	int odpowiedz;
	cout << "Jesli wybierasz gotowy rozmiar wcisnij 1, jesli chcesz wpisac wlasny rozmiar wcisnij 2. " << endl;
	cin >> odpowiedz;

	switch (odpowiedz) {//opcja wyboru planszy
	case 1:
		cout << "Wybrales gotowy rozmiar (8x8). " << endl;
		gotowa_plansza();
		cout << "Gotowy? Gramy! Zaczyna bialy gracz. " << endl;
		wybor_bialego_piona();
		ruch_bialego_gracza();
		
		break;

	case 2:
		rysuj_plansze();
		cout << "Gotowy? Gramy! Zaczyna bialy gracz. " << endl;
		wybor_bialego_piona();
		ruch_bialego_gracza();

		break;

	default:
		cout << "Nie wybrales zadnej opcji. Gra zamknie sie po wcisnieciu dowolnego klawisza." << endl;
		return 0;
	}

	
	return 0;
}