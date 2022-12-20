#include <iostream>
using namespace std;


void rysuj_plansze() {
	int** plansza, w, k;
	cout << "Podaj liczbe wierszy i kolumn (najmniejsza powierzchnia planszy to 8x8). " << endl;
	cin >> w >> k;
	if (w < 8 || k < 8) {
		cout << "Wpisales za malo wierszy i(lub) kolumn, wpisz jeszcze raz: " << endl;
		rysuj_plansze();
	}
	else {
		cout << "Wpisales prawidlowe liczby wierszy i kolumn, wymiary Twojej planszy to: " << endl;
		cout << "Wiersze: " << w << endl;
		cout << "Kolumny: " << k << endl;
	}
	plansza = new int* [w];

	for (int i = 0; i < w; i++)
		plansza[i] = new int[k];

	for (int i = 0; i < w; i++)
		for (int j = 0; j < k; j++)
			plansza[i][j] = 0;

	for (int i = 0; i < w; i++) {
		cout << "O" << " ";
		cout << endl;
		for (int j = 0; j < k; j++) {
			cout << "O" << " ";
		}

	}
}


int main()
{

	rysuj_plansze();
	
}

