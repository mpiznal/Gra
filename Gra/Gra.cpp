#include <iostream>
using namespace std;



void rysuj_plansze() {
	int wiersze=0, kolumny=0;
	int** plansza, w, k;
	cout << "Aby narysowac plansze: podaj liczbe wierszy i kolumn (najmniejsza wymiary planszy to 8x8). " << endl;
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
	}
	w = wiersze + 1;
	k = kolumny + 1;

	plansza = new int* [w];

	for (int i = 0; i < w; i++)
		plansza[i] = new int[k];

	for (int i = 0; i < w; i++) {
		for (int j = 0; j < k; j++) {
			plansza[i][j] = 0;
		}
	}
	cout << endl;

	cout << "\t\t\t\t" << "WARCABY: " << endl;
	cout << endl;


	for (int i = 0; i < 1; i++) {
		cout << endl;
		for (int j = 0; j < kolumny; j++) {
			cout << " ";
			cout << "\t" << j + 1 << "  ";
			
		}
	}
	
	cout << endl;
	for (int i = 0; i < 1; i++) {

		for (int i = 0; i < wiersze; i++) {
			cout << i + 1 << endl;
			cout << endl;

			for (int j = kolumny; j > 0; j--) {
				cout << "\t" << "[]  ";
			}

		}
	}
};

void wyczysc_plansze() {

}


int main()
{
	cout << "Witaj w grze WARCABY!" << endl;
	rysuj_plansze();

}

