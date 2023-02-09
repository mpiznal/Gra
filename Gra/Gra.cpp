#include <iostream>
#include <fstream>
#include <locale.h>
#include <cstdlib>
#include <stdexcept>
#include <limits>
#include <string>

using namespace std;



int bx = 0, by = 0;//ZMIENNE WYBORU PIONKA
int x = 0, y = 0;//ZMIENNE RUCHU PIONKA
int new_bx = 0, new_by = 0;//ZMIENNE BICIA WIELOKROTNEGO

int liczba_białych_pionków = 12;//OKREŚLENIE ILOŚCI POCZĄTKOWEJ PIONKÓW
int liczba_czarnych_pionków = 12;//OKREŚLENIE ILOŚCI POCZĄTKOWEJ PIONKÓW

int wiersze = 0, kolumny = 0;//ZMIENNE OKREŚLANIA ROZMIARÓW PLANSZY

int w1 = 0, w2 = 0, k1 = 0, k2 = 0;//ZMIENNE DO OKREŚLENIA POZYCJI PIONKA PO RUCHU
int i = 0, j = 0;//ZMIENNE DO OKREŚLANIA POZYCJI PIONKÓW
int nr = 0;//DODATKOWA ZMIENNA DO RYSOWANIA PLANSZY

int numer_ruchu = 1;//ZMIENNA OKREŚLAJĄCA NUMER RUCHU

//OKREŚLENIE WYGLĄDU GOTOWEJ PLANSZY
char plansza1[8][8] = { ' ','B',' ','B',' ','B',' ','B',
  'B',' ','B',' ','B',' ','B',' ',
  ' ','B',' ','B',' ','B',' ','B',
  'X',' ','X',' ','X',' ','X',' ',
  ' ','X',' ','X',' ','X',' ','X',
  'C',' ','C',' ','C',' ','C',' ',
  ' ','C',' ','C',' ','C',' ','C',
  'C',' ','C',' ','C',' ','C',' '
};

//OKREŚLENIE DYNAMICZNEJ PLANSZY
char** plansza2;


class Plansza {
public:
	//OKREŚLENIE FUNKCJI ZAPRZYJAŹNIONYCH
	friend void wybor_bialego_piona_1(int bx, int by);
	friend void biala_dama_1();

	friend void wybor_czarnego_piona_1(int bx, int by);
	friend void czarna_dama_1();

	friend void wybor_bialego_piona_2(int bx, int by);
	friend void wybor_czarnego_piona_2(int bx, int by);
	friend void zapis_do_pliku_1(int i, int j);
	friend void zapis_do_pliku_2(int i, int j);



	void gotowa_plansza_1() {//WYWOŁANIE GOTOWEJ PLANSZY NA EKRAN
		cout << 0 << " " << 1 << " " << 2 << " " << 3 << " " << 4 << " " << 5 << " " << 6 << " " << 7 << " " << 8 << endl;

		for (int i = 0; i < 8; i++) {//RYSOWANIE WIERSZY
			nr++;
			cout << nr << " ";
			for (int j = 0; j < 8; j++)//RYSOWANIE KOLUMN
			{
				cout << plansza1[i][j] << "|";
			}
			cout << endl;
		}

	}

	void okresl_plansze_2() {//OKREŚLANIE ROZMIARÓW DYNAMICZNEJ PLANSZY

		cout << "Podaj liczbę wierszy - tu możesz podać tylko liczby parzyste - i kolumn (najmniejsza powierzchnia planszy to 8x8). " << endl;
		cout << "Liczba wierszy: " << endl;
		cin >> wiersze;
		cout << "Liczba kolumn: " << endl;
		cin >> kolumny;

		int wierszeplus2 = wiersze + 2;
		int kolumnyplus2 = kolumny + 2;

		if (cin.fail()) {//ZAPOBIEGANIE WPISYWANIU BŁĘDNYCH DANYCH PRZEZ UŻYTKOWNIKA	
			cin.clear();
			cin.ignore();
			system("cls");
			cout << "Podałeś niepoprawne dane. Spróbuj ponownie." << endl;
			okresl_plansze_2();
		}

		//OKREŚLANIE POPRAWNYCH ROZMIARÓW DYNAMICZNEJ PLANSZY
		else if (wiersze % 2 != 0) {
			cout << "Wpisałeś niepoprawną liczbę wierszy. Spróbuj ponownie." << endl;
			okresl_plansze_2();
		}
		else {

			if (wiersze < 8 || kolumny < 8) {
				cout << "Wpisałeś za mało wierszy i(lub) kolumn, wpisz jeszcze raz: " << endl;
				okresl_plansze_2();
			}
			else {
				cout << "Wpisałeś prawidłowe liczby wierszy i kolumn, wymiary Twojej planszy to: " << endl;
				cout << "Wiersze: " << wiersze << endl;
				cout << "Kolumny: " << kolumny << endl;
				cout << endl;
			}
		}



		plansza2 = new char* [wierszeplus2];//TWORZENIE PIERWSZEGO WYMIARU DYNAMICZNEJ PLANSZY

		for (int i = 0; i < wierszeplus2; i++)
			plansza2[i] = new char[kolumnyplus2];//TWORZENIE DRUGIEGO WYMIARU DYNAMICZNEJ PLANSZY


	}

	void rysuj_plansze_2() {//WYWOŁANIE DYNAMICZNEJ PLANSZY NA EKRAN


		//GÓRNA CZĘŚĆ PLANSZY - OKREŚLENIE PÓL
		for (int i = 1; i < 2; i += 2)
			for (int j = 1; j < kolumny + 1; j += 2)
				plansza2[i][j] = ' ';
		for (int i = 1; i < 2; i += 2)
			for (int j = 2; j < kolumny + 1; j += 2)
				plansza2[i][j] = 'B';

		for (int i = 2; i < 3; i += 2)
			for (int j = 1; j < kolumny + 1; j += 2)
				plansza2[i][j] = 'B';
		for (int i = 2; i < 3; i += 2)
			for (int j = 2; j < kolumny + 1; j += 2)
				plansza2[i][j] = ' ';

		for (int i = 3; i < 4; i += 2)
			for (int j = 1; j < kolumny + 1; j += 2)
				plansza2[i][j] = ' ';
		for (int i = 3; i < 4; i += 2)
			for (int j = 2; j < kolumny + 1; j += 2)
				plansza2[i][j] = 'B';

		//DOLNA CZĘŚĆ PLANSZY - OKREŚLENIE PÓL
		for (int i = wiersze; i < wiersze + 1; i += 2)
			for (int j = 1; j < kolumny + 1; j += 2)
				plansza2[i][j] = 'C';
		for (int i = wiersze; i < wiersze + 1; i += 2)
			for (int j = 2; j < kolumny + 1; j += 2)
				plansza2[i][j] = ' ';

		for (int i = wiersze - 1; i < wiersze + 1; i += 2)
			for (int j = 1; j < kolumny + 1; j += 2)
				plansza2[i][j] = ' ';
		for (int i = wiersze - 1; i < wiersze + 1; i += 2)
			for (int j = 2; j < kolumny + 2; j += 2)
				plansza2[i][j] = 'C';

		for (int i = wiersze - 2; i < wiersze + 1; i += 2)
			for (int j = 1; j < kolumny + 1; j += 2)
				plansza2[i][j] = 'C';
		for (int i = wiersze - 2; i < wiersze + 1; i += 2)
			for (int j = 2; j < kolumny + 1; j += 2)
				plansza2[i][j] = ' ';

		//ŚRODKOWA CZĘŚĆ PLANSZY - OKREŚLENIE PÓL
		for (int i = 4; i < wiersze - 2; i += 2)
			for (int j = 1; j < kolumny + 1; j += 2)
				plansza2[i][j] = 'X';
		for (int i = 4; i < wiersze - 2; i += 2)
			for (int j = 2; j < kolumny + 1; j += 2)
				plansza2[i][j] = ' ';

		for (int i = 5; i < wiersze - 2; i += 2)
			for (int j = 1; j < kolumny + 1; j += 2)
				plansza2[i][j] = ' ';
		for (int i = 5; i < wiersze - 2; i += 2)
			for (int j = 2; j < kolumny + 1; j += 2)
				plansza2[i][j] = 'X';



		for (int i = 0; i < 1; i++) {
			cout << "   ";
			for (int j = 1; j < kolumny + 1; j++) {
				plansza2[i][j] = NULL;
				cout << j << " ";
			}
			cout << endl;

		}



		for (int i = 1; i < wiersze + 1; i++) {
			cout << "";
			nr++;
			cout << nr << "  ";
			for (int j = 1; j < kolumny + 1; j++) {
				cout << plansza2[i][j] << "|";//WYWOŁANIE NA EKRAN DYNAMICZNEJ PLANSZY

			}
			cout << endl;

		}



	}


};


void wybor_bialego_piona_1(int bx, int by) {/*UŻYCIE ZAPRZYJAŹNIONEJ FUNKCJI DO KLASY PLANSZA.
	UŻYCIE TEJ FUNKCJI ZAPOBIEGA BŁĘDNEGO WYBRANIU PIONA BIAŁEGO I BŁĘDNEMU RUCHOWI WYBRANYM PIONEM*/

	if (cin.fail()) {//ZAPOBIEGANIE WPISYWANIU BŁĘDNYCH DANYCH PRZEZ UŻYTKOWNIKA (CHAR LUB INNYCH ZNAKÓW)	
		cin.clear();
		cin.ignore();
	}

	cout << "Wybierz białego pionka, którym chcesz ruszyć (podaj kolejno wiersz i pole, na którym pionek się znajduje). " << endl;
	cout << "Wiersze: " << endl;
	cin >> bx;
	cout << "Kolumny: " << endl;
	cin >> by;



	int bxminus1 = bx - 1;
	int byminus1 = by - 1;
	int bxplus1 = bx + 1;
	int byplus1 = by + 1;
	int bxminus2 = bx - 2;
	int byminus2 = by - 2;
	int bxplus2 = bx + 2;
	int byplus2 = by + 2;
	int bxminus3 = bx - 3;
	int byminus3 = by - 3;
	int bxplus3 = bx + 3;
	int byplus3 = by + 3;
	int bxminus4 = bx - 4;
	int byminus4 = by - 4;
	int bxplus4 = bx + 4;
	int byplus4 = by + 4;
	int bxminus5 = bx - 5;
	int byminus5 = by - 5;
	int bxplus5 = bx + 5;
	int byplus5 = by + 5;

	//1.
	//WYBÓR PIONA BIAŁEGO, KTÓRY MA MOŻLIWOŚĆ BICIA PIONA PRZECIWNIKA PO OBU STRONACH
	if ((plansza1[bxminus1][byminus1] == 'B') && (plansza1[bx][by] == 'C') && (plansza1[bx][by - 2] == 'C') && (plansza1[bxplus1][byplus1] == 'X') && (plansza1[bxplus1][byminus3] == 'X')) {
		cout << "Możesz zbić przeciwnika w obie strony. Zdecyduj, którą opcję wybierasz." << endl;
		int odpowiedz;
		cout << "Jeśli wybierasz bicie w prawą stronę wciśnij 1, jeśli wybierasz bicie w lewą stronę wciśnij 2. " << endl;
		cin >> odpowiedz;//MOŻLIWOŚĆ DOKONANIA WYBORU, W KTÓRĄ STRONĘ CHCE SIĘ ZBIĆ PRZECIWNIKA

		switch (odpowiedz) {
		case 1://BICIE W PRAWO
			cout << "Następuje bicie piona czarnego przez piona białego." << endl;
			//USTAWIENIE NOWYCH POZYCJI PIONÓW PO BICIU
			bxminus1 = bx - 1;
			byminus1 = by - 1;
			plansza1[bxminus1][byminus1] = 'X';
			liczba_czarnych_pionków = liczba_czarnych_pionków - 1;

			plansza1[bx][by] = 'X';
			plansza1[bxplus1][byplus1] = 'B';
			int odp;
			cout << "Żeby zaktualizować planszę - wciśnij 1. ";
			//ZMNIEJSZENIE LICZBY PIONÓW PRZECIWNIKA PO BICIU

			cin >> odp;
			if (odp == 1) {
				system("cls");

				cout << "Trwa aktualizacja planszy: " << endl;


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
				//MOŻLIWOŚĆ DALSZEGO BICIA PRZECIWNIKA LUB ZAPRZESTANIA
				if ((plansza1[bxplus2][by] == 'C' && plansza1[bxplus3][byminus1] == 'X') || (plansza1[bxplus2][byplus2] == 'C' && plansza1[bxplus3][byplus3] == 'X')) {
					cout << "Czy chcesz bić dalej? Wciśnij 1, jeśli tak, wciśnij 2, jeśli nie." << endl;
					int o;
					cin >> o;

					if (o == 1) {
						//ZAPOBIEGANIE PRZED WYBOREM INNEGO PIONA - BICIE
						cout << "Pamiętaj, żeby wybrać tego samego piona. " << endl;
						new_bx = bxplus1;
						new_by = byplus1;
						wybor_bialego_piona_1(new_bx, new_by);

						break;
					}
					else if (o == 2) {//ZAPRZESTANIE BICIA
						break;
					}
				}
			}

			break;
		case 2://BICIE W LEWO
			cout << "Następuje bicie piona czarnego przez piona białego." << endl;
			//USTAWIENIE NOWYCH POZYCJI PIONÓW PO BICIU
			bxminus1 = bx - 1;
			byminus1 = by - 1;
			plansza1[bxminus1][byminus1] = 'X';
			liczba_czarnych_pionków = liczba_czarnych_pionków - 1;
			plansza1[bx][byminus2] = 'X';
			plansza1[bxplus1][byminus3] = 'B';
			int odpow;
			cout << "Żeby zaktualizować planszę - wciśnij 1. ";
			cin >> odpow;
			//ZMNIEJSZENIE LICZBY PIONÓW PRZECIWNIKA PO BICIU

			if (odpow == 1) {
				system("cls");

				cout << "Trwa aktualizacja planszy: " << endl;


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
				//MOŻLIWOŚĆ DALSZEGO BICIA PRZECIWNIKA LUB ZAPRZESTANIA
				if ((plansza1[bxplus2][byminus4] == 'C' && plansza1[bxplus3][byminus5] == 'X') || (plansza1[bxplus2][byminus2] == 'C' && plansza1[bxplus3][byminus1] == 'X')) {
					cout << "Czy chcesz bić dalej? Wciśnij 1, jeśli tak, wciśnij 2, jeśli nie." << endl;
					int o;
					cin >> o;

					if (o == 1) {
						//ZAPOBIEGANIE PRZED WYBOREM INNEGO PIONA - BICIE
						cout << "Pamiętaj, żeby wybrać tego samego piona. " << endl;
						new_bx = bxplus1;
						new_by = byminus3;
						wybor_bialego_piona_1(new_bx, new_by);

						break;
					}
					else if (o == 2) {//ZAPRZESTANIE BICIA
						break;
					}
				}
			}

			break;
			//WYBÓR INNEJ OPCJI PRZENIESIE NAS DO PONOWNEGO WYBORU PIONA
		default: cout << "Nie wybrałeś żadnej opcji. Spróbuj ponownie" << endl;
			wybor_bialego_piona_1(bx, by);
		}


	}

	//2.
	//WYBÓR PIONA BIAŁEGO, KTÓRY MA MOŻLIWOŚĆ BICIA PIONA PRZECIWNIKA W PRAWO
	else if ((plansza1[bxminus1][byminus1] == 'B') && ((plansza1[bx][by] == 'C') && (plansza1[bxplus1][byplus1] == 'X'))) {

		//MOŻLIWOŚĆ BICIA LUB RUCHU W DRUGĄ STRONĘ (LEWO)
		cout << "Czy chcesz zbić pionka przeciwnika w prawą stronę? Wciśnij 1, jeśli tak, wciśnij 2, jeśli chcesz i możesz ruszyć się w lewo." << endl;
		int odpowiedz = 0;
		cin >> odpowiedz;
		switch (odpowiedz) {
		case 1://BICIE W PRAWO
			cout << "Następuje bicie piona czarnego przez piona białego." << endl;
			bxminus1 = bx - 1;
			byminus1 = by - 1;
			plansza1[bxminus1][byminus1] = 'X';
			//USTAWIENIE NOWYCH POZYCJI PIONÓW PO BICIU
			liczba_czarnych_pionków = liczba_czarnych_pionków - 1;
			//ZMNIEJSZENIE LICZBY PIONÓW PRZECIWNIKA
			plansza1[bx][by] = 'X';
			plansza1[bxplus1][byplus1] = 'B';
			int odp;
			cout << "Żeby zaktualizować planszę - wciśnij 1. ";
			cin >> odp;

			if (odp == 1) {
				system("cls");

				cout << "Trwa aktualizacja planszy: " << endl;


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
				//MOŻLIWOŚĆ DALSZEGO BICIA PRZECIWNIKA LUB ZAPRZESTANIA
				if ((plansza1[bxplus2][by] == 'C' && plansza1[bxplus3][byminus1] == 'X') || (plansza1[bxplus2][byplus2] == 'C' && plansza1[bxplus3][byplus3] == 'X')) {
					cout << "Czy chcesz bić dalej? Wciśnij 1, jeśli tak, wciśnij 2, jeśli nie." << endl;
					int o;
					cin >> o;

					if (o == 1) {//ZAPOBIEGANIE PRZED WYBOREM INNEGO PIONA - BICIE
						cout << "Pamiętaj, żeby wybrać tego samego piona. " << endl;
						new_bx = bxplus1;
						new_by = byplus1;
						wybor_bialego_piona_1(new_bx, new_by);

						break;
					}
					else if (o == 2) {//ZAPRZESTANIE BICIA
						break;
					}
				}

			}
			break;
		case 2://REZYGNACJA Z BICIA W PRAWO, RUCH W LEWO
			if ((plansza1[bxminus1][byminus1] == 'B') && (plansza1[bx][byminus2] == 'X')) {

				plansza1[bxminus1][byminus1] = 'X';
				plansza1[bx][byminus2] = 'B';
				int odp;
				cout << "Żeby zaktualizować planszę - wciśnij 1. ";
				cin >> odp;
				if (odp == 1) {
					system("cls");

					cout << "Trwa aktualizacja planszy: " << endl;
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
			else {//ZAPOBIEGANIE RUCHOWI W LEWO, JEŚLI GRACZ NIE MA TAKIEGO MOŻLIWOŚCI
				cout << "Dokonałeś niepoprawnego wyboru. Spróbuj ponownie." << endl;
				wybor_bialego_piona_1(bx, by);
			}
			break;
			//WYBÓR INNEJ OPCJI PRZENIESIE NAD DO PONOWNEGO WYBORU PIONA
		default: cout << "Nie wybrałeś żadnej opcji. Spróbuj ponownie" << endl;
			wybor_bialego_piona_1(bx, by);
		}


	}
	//3.
	//WYBÓR PIONA BIAŁEGO, KTÓRY MA MOŻLIWOŚĆ BICIA PIONA PRZECIWNIKA W LEWO
	else if ((plansza1[bxminus1][byminus1] == 'B') && ((plansza1[bx][byminus2] == 'C') && (plansza1[bxplus1][byminus3] == 'X'))) {

		//MOŻLIWOŚĆ BICIA LUB RUCHU W DRUGĄ STRONĘ (PRAWO)
		cout << "Czy chcesz zbić pionka przeciwnika w lewą stronę? Wciśnij 1, jeśli tak, wciśnij 2, jeśli chcesz i możesz ruszyć się w prawo." << endl;
		int odpowiedz = 0;
		cin >> odpowiedz;
		switch (odpowiedz) {
		case 1://BICIE W LEWO
			cout << "Następuje bicie piona czarnego przez piona białego." << endl;
			bxminus1 = bx - 1;
			byminus1 = by - 1;
			plansza1[bxminus1][byminus1] = 'X';
			liczba_czarnych_pionków = liczba_czarnych_pionków - 1;
			plansza1[bx][byminus2] = 'X';
			plansza1[bxplus1][byminus3] = 'B';
			//USTAWIENIE NOWYCH POZYCJI PIONÓW PO BICIU
			int odp;
			cout << "Żeby zaktualizować planszę - wciśnij 1. ";
			cin >> odp;
			//ZMNIEJSZENIE LICZBY PIONÓW PRZECIWNIKA


			if (odp == 1) {

				system("cls");

				cout << "Trwa aktualizacja planszy: " << endl;

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
				//MOŻLIWOŚĆ DALSZEGO BICIA PRZECIWNIKA LUB ZAPRZESTANIA
				if ((plansza1[bxplus2][byminus4] == 'C' && plansza1[bxplus3][byminus5] == 'X') || (plansza1[bxplus2][byminus2] == 'C' && plansza1[bxplus3][byminus1] == 'X')) {
					cout << "Czy chcesz bić dalej? Wciśnij 1, jeśli tak, wciśnij 2, jeśli nie." << endl;
					int o;
					cin >> o;

					if (o == 1) {//ZAPOBIEGANIE PRZED WYBOREM INNEGO PIONA - BICIE
						cout << "Pamiętaj, żeby wybrać tego samego piona. " << endl;
						new_bx = bxplus1;
						new_by = byminus3;
						wybor_bialego_piona_1(new_bx, new_by);

						break;
					}
					else if (o == 2) {//ZAPRZESTANIE BICIA
						break;
					}
				}
			}
			break;
		case 2://REZYGNACJA Z BICIA W LEWO, RUCH W PRAWO
			if ((plansza1[bxminus1][byminus1] == 'B') && (plansza1[bx][by] == 'X')) {

				plansza1[bxminus1][byminus1] = 'X';
				plansza1[bx][by] = 'B';
				int odp;
				cout << "Żeby zaktualizować planszę - wciśnij 1. ";
				cin >> odp;
				if (odp == 1) {
					system("cls");

					cout << "Trwa aktualizacja planszy: " << endl;
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
			else {//ZAPOBIEGANIE RUCHOW W PRAWO, JEŚLI GRACZ NIE MA TAKIEJ MOŻLIWOŚCI
				cout << "Dokonałeś niepoprawnego wyboru. Spróbuj ponownie." << endl;
				wybor_bialego_piona_1(bx, by);
			}
			break;
			//WYBÓR INNEJ OPCJI PRZENIESIE NAD DO PONOWNEGO WYBORU PIONA
		default: cout << "Nie wybrałeś żadnej opcji. Spróbuj ponownie" << endl;
			wybor_bialego_piona_1(bx, by);
		}
	}

	//4.
	//WYBÓR PIONA BIAŁEGO, KTÓRY NIE MA MOŻLIWOŚCI BICIA PRZECIWNIKA
	else if ((plansza1[bxminus1][byminus1] == 'B') && ((plansza1[bx][byminus2] == 'X') || (plansza1[bx][by] == 'X'))) {

		if (by <= 8) {
			cout << "Wybrałeś odpowiedniego pionka." << endl;
			/*OGRANICZENIE DRUGIEGO WYMIARU TABLICY STATYCZNEJ (KOLUMNY)
			BRAK TAKIEGO OGRANICZENIA SKUTKUJE DALSZYM "PRZECHODZENIEM" PRZEZ
			WIERSZE TABLICY, PO PODANIU WIĘKSZEJ ILOŚCI KOLUMN*/
		}
		else {
			cout << "Wybrałeś nieprawidłowego pionka. Spróbuj ponownie." << endl;
			wybor_bialego_piona_1(bx, by);
			//ZAPOBIEGANIE PRZED WYBOREM NIEPRAWIDŁOWEGO PIONA
		}

		cout << "Wybierz pole, na które chcesz ruszyć (podaj kolejno wiersz i pole, na którym pionek ma się znajdować). " << endl;
		cout << "Wiersze: " << endl;
		cin >> x;
		cout << "Kolumny: " << endl;
		cin >> y;

		int xplus1 = x + 1;
		int yplus1 = y + 1;
		int xminus1 = x - 1;
		int yminus1 = y - 1;
		int xplus2 = x + 2;
		int yplus2 = y + 2;
		int xminus2 = x - 2;
		int yminus2 = y - 2;


		//OKREŚLENIE WARUNKÓW POZYCJI NA PLANSZY DLA ZWYKŁEGO RUCHU PIONA BIAŁEGO
		if ((x - bx == 1) && (plansza1[xminus1][yminus1] == 'X') && ((y - by == 1) || (y - by == (-1)))) {
			cout << "Wybrałeś dozwolony ruch. " << endl;
			bxminus1 = bx - 1;
			byminus1 = by - 1;
			plansza1[bxminus1][byminus1] = 'X';
			//USTAWIENIE NOWYCH POZYCJI PIONÓW PO DOKONANIU RUCHU
			int odp;
			cout << "Żeby zaktualizować planszę - wciśnij 1. ";
			cin >> odp;
			w1 = x - 1;
			k1 = y - 1;
			plansza1[w1][k1] = 'B';
			if (odp == 1) {
				system("cls");

				cout << "Trwa aktualizacja planszy: " << endl;

				//USTAWIENIE NOWYCH POZYCJI PIONÓW PO DOKONANIU RUCHU

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
			cout << "Wybrałeś niedozwolony ruch. Spróbuj ponownie." << endl;
			wybor_bialego_piona_1(bx, by);
			//ZAPOBIEGANIE PRZED WYBOREM NIEPRAWIDŁOWEGO RUCHU
		}
	}

	//5.
	//WYBÓR NIEPRAWIDŁOWEGO PIONA BIAŁEGO
	else {
		cout << "Wybrałeś nieodpowiedniego pionka. Spróbuj ponownie." << endl;
		wybor_bialego_piona_1(bx, by);
		//ZAPOBIEGANIE PRZED WYBOREM NIEPRAWIDŁOWEGO PIONA
	}



};

void biala_dama_1() {

	if (plansza1[7][0] == 'B') {
		plansza1[7][0] = 'b';
		system("cls");
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
	else if (plansza1[7][2] == 'B') {
		plansza1[7][2] = 'b';
		system("cls");
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
	else if (plansza1[7][4] == 'B') {
		plansza1[7][4] = 'b';
		system("cls");
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
	else if (plansza1[7][6] == 'B') {
		plansza1[7][6] = 'b';
		system("cls");
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


};


void wybor_czarnego_piona_1(int bx, int by) {/*UŻYCIE ZAPRZYJAŹNIONEJ FUNKCJI DO KLASY PLANSZA.
	UŻYCIE TEJ FUNKCJI ZAPOBIEGA BŁĘDNEGO WYBRANIU PIONA BIAŁEGO I BŁĘDNEMU RUCHOWI WYBRANYM PIONEM*/

	if (cin.fail()) {//ZAPOBIEGANIE WPISYWANIU BŁĘDNYCH DANYCH PRZEZ UŻYTKOWNIKA (CHAR LUB INNYCH ZNAKÓW)	
		cin.clear();
		cin.ignore();
	}
	cout << "Wybierz czarnego pionka, którym chcesz ruszyć (podaj kolejno wiersz i pole, na którym pionek się znajduje). " << endl;
	cout << "Wiersze: " << endl;
	cin >> bx;
	cout << "Kolumny: " << endl;
	cin >> by;

	int bxminus1 = bx - 1;
	int byminus1 = by - 1;
	int bxplus1 = bx + 1;
	int byplus1 = by + 1;
	int bxminus2 = bx - 2;
	int byminus2 = by - 2;
	int bxplus2 = bx + 2;
	int byplus2 = by + 2;
	int bxminus3 = bx - 3;
	int byminus3 = by - 3;
	int bxplus3 = bx + 3;
	int byplus3 = by + 3;
	int bxminus4 = bx - 4;
	int byminus4 = by - 4;
	int bxplus4 = bx + 4;
	int byplus4 = by + 4;
	int bxminus5 = bx - 5;
	int byminus5 = by - 5;
	int bxplus5 = bx + 5;
	int byplus5 = by + 5;

	//1.
	//WYBÓR PIONA CZARNEGO, KTÓRY MA MOŻLIWOŚĆ BICIA PIONA PRZECIWNIKA PO OBU STRONACH
	if ((plansza1[bxminus1][byminus1] == 'C') && (plansza1[bxminus2][byminus2] == 'B') && (plansza1[bxminus2][by] == 'B') && (plansza1[bxminus3][byplus1] == 'X') && (plansza1[bxminus3][byminus3] == 'X')) {
		cout << "Możesz zbić przeciwnika w obie strony. Zdecyduj, którą opcję wybierasz." << endl;
		int odpowiedz;
		cout << "Jeśli wybierasz bicie w prawą stronę wciśnij 1, jeśli wybierasz bicie w lewą stronę wciśnij 2. " << endl;
		cin >> odpowiedz; //MOŻLIWOŚĆ DOKONANIA WYBORU, W KTÓRĄ STRONĘ CHCE SIĘ ZBIĆ PRZECIWNIKA

		switch (odpowiedz) {
		case 1://BICIE W PRAWO
			cout << "Następuje bicie piona białego przez piona czarnego." << endl;
			//USTAWIENIE NOWYCH POZYCJI PIONÓW PO BICIU
			bxminus1 = bx - 1;
			byminus1 = by - 1;
			plansza1[bxminus1][byminus1] = 'X';
			liczba_białych_pionków = liczba_białych_pionków - 1;
			plansza1[bxminus2][by] = 'X';
			plansza1[bxminus3][byplus1] = 'C';
			int odp;
			cout << "Żeby zaktualizować planszę - wciśnij 1. ";
			cin >> odp;
			if (odp == 1) {
				system("cls");

				cout << "Trwa aktualizacja planszy: " << endl;
				//ZMNIEJSZENIE LICZBY PIONÓW PRZECIWNIKA PO BICIU


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
				//MOŻLIWOŚĆ DALSZEGO BICIA PRZECIWNIKA LUB ZAPRZESTANIA
				if ((plansza1[bxminus4][by] == 'B' && plansza1[bxminus5][byminus1] == 'X') || (plansza1[bxminus4][byplus2] == 'B' && plansza1[bxminus5][byplus3] == 'X')) {
					cout << "Czy chcesz bić dalej? Wciśnij 1, jeśli tak, wciśnij 2, jeśli nie." << endl;
					int o;
					cin >> o;

					//ZAPOBIEGANIE PRZED WYBOREM INNEGO PIONA - BICIE
					if (o == 1) {
						cout << "Pamiętaj, żeby wybrać tego samego piona. " << endl;
						new_bx = bxminus3;
						new_by = byplus1;
						wybor_czarnego_piona_1(new_bx, new_by);

						break;
					}
					else if (o == 2) {//ZAPRZESTANIE BICIA
						break;
					}
				}
			}
			break;
		case 2://BICIE W LEWO
			cout << "Następuje bicie piona białego przez piona czarnego." << endl;
			//USTAWIENIE NOWYCH POZYCJI PIONÓW PO BICIU
			bxminus1 = bx - 1;
			byminus1 = by - 1;
			plansza1[bxminus1][byminus1] = 'X';
			//ZMNIEJSZENIE LICZBY PIONÓW PRZECIWNIKA PO BICIU
			plansza1[bxminus1][byminus1] = 'X';
			plansza1[bxminus2][byminus2] = 'X';
			plansza1[bxminus3][byminus3] = 'C';
			int odpow;
			cout << "Żeby zaktualizować planszę - wciśnij 1. ";
			cin >> odpow;
			if (odp == 1) {
				system("cls");
				liczba_białych_pionków = liczba_białych_pionków - 1;
				cout << "Trwa aktualizacja planszy: " << endl;


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
				//MOŻLIWOŚĆ DALSZEGO BICIA PRZECIWNIKA LUB ZAPRZESTANIA
				if ((plansza1[bxminus4][byminus4] == 'B' && plansza1[bxminus5][byminus5] == 'X') || (plansza1[bxminus4][byminus2] == 'B' && plansza1[bxminus5][byminus1] == 'X')) {
					cout << "Czy chcesz bić dalej? Wciśnij 1, jeśli tak, wciśnij 2, jeśli nie." << endl;
					int o;
					cin >> o;

					if (o == 1) {//ZAPOBIEGANIE PRZED WYBOREM INNEGO PIONA - BICIE
						cout << "Pamiętaj, żeby wybrać tego samego piona. " << endl;
						new_bx = bxminus3;
						new_by = byminus3;
						wybor_czarnego_piona_1(new_bx, new_by);

						break;
					}
					else if (o == 2) {//ZAPRZESTANIE BICIA
						break;
					}
				}
			}
			break;
			//WYBÓR INNEJ OPCJI PRZENIESIE NAS DO PONOWNEGO WYBORU PIONA
		default: cout << "Nie wybrałeś żadnej opcji. Spróbuj ponownie" << endl;
			wybor_czarnego_piona_1(bx, by);
		}

	}

	//2.
	//WYBÓR PIONA CZARNEGO, KTÓRY MA MOŻLIWOŚĆ BICIA PIONA PRZECIWNIKA W PRAWO
	else if ((plansza1[bxminus1][byminus1] == 'C') && ((plansza1[bxminus2][by] == 'B') && (plansza1[bxminus3][byplus1] == 'X'))) {
		//MOŻLIWOŚĆ BICIA LUB RUCHU W DRUGĄ STRONĘ (LEWO)
		cout << "Czy chcesz zbić pionka przeciwnika w prawą stronę? Wciśnij 1, jeśli tak, wciśnij 2, chcesz i możesz ruszyć się w lewo." << endl;
		int odpowiedz = 0;
		cin >> odpowiedz;
		switch (odpowiedz) {
		case 1://BICIE W PRAWO
			cout << "Następuje bicie piona białego przez piona czarnego." << endl;
			bxminus1 = bx - 1;
			byminus1 = by - 1;
			plansza1[bxminus1][byminus1] = 'X';
			liczba_białych_pionków = liczba_białych_pionków - 1;
			//ZMNIEJSZENIE LICZBY PIONÓW PRZECIWNIKA
			//USTAWIENIE NOWYCH POZYCJI PIONÓW PO BICIU
			plansza1[bxminus2][by] = 'X';
			plansza1[bxminus3][byplus1] = 'C';
			int odp;
			cout << "Żeby zaktualizować planszę - wciśnij 1. ";
			cin >> odp;
			if (odp == 1) {
				system("cls");


				cout << "Trwa aktualizacja planszy: " << endl;



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
				//MOŻLIWOŚĆ DALSZEGO BICIA PRZECIWNIKA LUB ZAPRZESTANIA
				if ((plansza1[bxminus4][by] == 'B' && plansza1[bxminus5][byminus1] == 'X') || (plansza1[bxminus4][byplus2] == 'B' && plansza1[bxminus5][byplus3] == 'X')) {
					cout << "Czy chcesz bić dalej? Wciśnij 1, jeśli tak, wciśnij 2, jeśli nie." << endl;
					int o;
					cin >> o;

					if (o == 1) {//ZAPOBIEGANIE PRZED WYBOREM INNEGO PIONA - BICIE
						cout << "Pamiętaj, żeby wybrać tego samego piona. " << endl;
						new_bx = bxminus3;
						new_by = byplus1;
						wybor_czarnego_piona_1(new_bx, new_by);

						break;
					}
					else if (o == 2) {//ZAPRZESTANIE BICIA
						break;
					}
				}

			}
			break;
		case 2://REZYGNACJA Z BICIA W PRAWO, RUCH W LEWO

			if ((plansza1[bxminus1][byminus1] == 'C') && (plansza1[bxminus2][byminus2] == 'X')) {

				plansza1[bxminus1][byminus1] = 'X';
				plansza1[bxminus2][byminus2] = 'C';
				int odp;
				cout << "Żeby zaktualizować planszę - wciśnij 1. ";
				cin >> odp;
				if (odp == 1) {
					system("cls");

					cout << "Trwa aktualizacja planszy: " << endl;
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
			else {//ZAPOBIEGANIE RUCHOWI W LEWO, JEŚLI GRACZ NIE MA TAKIEGO MOŻLIWOŚCI
				cout << "Dokonałeś niepoprawnego wyboru. Spróbuj ponownie." << endl;
				wybor_czarnego_piona_1(bx, by);
			}
			break;

		default: cout << "Nie wybrałeś żadnej opcji. Spróbuj ponownie" << endl;
			wybor_czarnego_piona_1(bx, by);
			//WYBÓR INNEJ OPCJI PRZENIESIE NAS DO PONOWNEGO WYBORU PIONA
		}
	}

	//3.
	//WYBÓR PIONA CZARNEGO, KTÓRY MA MOŻLIWOŚĆ BICIA PIONA PRZECIWNIKA W LEWO
	else if ((plansza1[bxminus1][byminus1] == 'C') && ((plansza1[bxminus2][byminus2] == 'B') && (plansza1[bxminus3][byminus3] == 'X'))) {

		//MOŻLIWOŚĆ BICIA LUB RUCHU W DRUGĄ STRONĘ (PRAWO)
		cout << "Czy chcesz zbić pionka przeciwnika w lewą stronę? Wciśnij 1, jeśli tak, wciśnij 2, jeśli chcesz i możesz ruszyć się w prawo." << endl;
		int odpowiedz = 0;
		cin >> odpowiedz;
		switch (odpowiedz) {
		case 1://BICIE W LEWO
			cout << "Następuje bicie piona białego przez piona czarnego." << endl;
			bxminus1 = bx - 1;
			byminus1 = by - 1;
			//ZMNIEJSZENIE LICZBY PIONÓW PRZECIWNIKA
			liczba_białych_pionków = liczba_białych_pionków - 1;
			plansza1[bxminus1][byminus1] = 'X';
			plansza1[bxminus2][byminus2] = 'X';
			plansza1[bxminus3][byminus3] = 'C';
			//USTAWIENIE NOWYCH POZYCJI PIONÓW PO BICIU
			int odp;
			cout << "Żeby zaktualizować planszę - wciśnij 1. ";
			cin >> odp;
			if (odp == 1) {
				system("cls");

				cout << "Trwa aktualizacja planszy: " << endl;


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
				//MOŻLIWOŚĆ DALSZEGO BICIA PRZECIWNIKA LUB ZAPRZESTANIA
				if ((plansza1[bxminus4][byminus4] == 'B' && plansza1[bxminus5][byminus5] == 'X') || (plansza1[bxminus4][byminus2] == 'B' && plansza1[bxminus5][byminus1] == 'X')) {
					cout << "Czy chcesz bić dalej? Wciśnij 1, jeśli tak, wciśnij 2, jeśli nie." << endl;
					int o;
					cin >> o;

					if (o == 1) {//ZAPOBIEGANIE PRZED WYBOREM INNEGO PIONA - BICIE
						cout << "Pamiętaj, żeby wybrać tego samego piona. " << endl;
						new_bx = bxminus3;
						new_by = byminus3;
						wybor_czarnego_piona_1(new_bx, new_by);

						break;
					}
					else if (o == 2) {//ZAPRZESTANIE BICIA
						break;
					}
				}
			}
			break;
		case 2://REZYGNACJA Z BICIA W LEWO, RUCH W PRAWO

			if ((plansza1[bxminus1][byminus1] == 'C') && (plansza1[bxminus2][by] == 'X')) {

				plansza1[bxminus1][byminus1] = 'X';
				plansza1[bxminus2][by] = 'C';
				int odp;
				cout << "Żeby zaktualizować planszę - wciśnij 1. ";
				cin >> odp;
				if (odp == 1) {
					system("cls");

					cout << "Trwa aktualizacja planszy: " << endl;
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
			else {//ZAPOBIEGANIE RUCHOWI W PRAWO, JEŚLI GRACZ NIE MA TAKIEGO MOŻLIWOŚCI
				cout << "Dokonałeś niepoprawnego wyboru. Spróbuj ponownie." << endl;
				wybor_czarnego_piona_1(bx, by);
			}

			break;
		default: cout << "Nie wybrałeś żadnej opcji. Spróbuj ponownie" << endl;
			wybor_czarnego_piona_1(bx, by);
			//WYBÓR INNEJ OPCJI PRZENIESIE NAS DO PONOWNEGO WYBORU PIONA
		}
	}

	// 4.
	//WYBÓR PIONA CZARNEGO, KTÓRY NIE MA MOŻLIWOŚCI BICIA PRZECIWNIKA
	else if ((plansza1[bxminus1][byminus1] == 'C') && ((plansza1[bxminus2][byminus2] == 'X') || (plansza1[bxminus2][by] == 'X'))) {
		if (by <= 8) {
			cout << "Wybrałeś odpowiedniego pionka." << endl;
			/*OGRANICZENIE DRUGIEGO WYMIARU TABLICY STATYCZNEJ (KOLUMNY)
			BRAK TAKIEGO OGRANICZENIA SKUTKUJE DALSZYM "PRZECHODZENIEM" PRZEZ
			WIERSZE TABLICY, PO PODANIU WIĘKSZEJ ILOŚCI KOLUMN*/
		}
		else {
			cout << "Wybrałeś nieprawidłowego pionka. Spróbuj ponownie." << endl;
			wybor_czarnego_piona_1(bx, by);
			//ZAPOBIEGANIE PRZED WYBOREM NIEPRAWIDŁOWEGO PIONA
		}
		cout << "Wybierz pole, na które chcesz ruszyć (podaj kolejno wiersz i pole, na którym pionek ma się znajdować). " << endl;
		cout << "Wiersze: " << endl;
		cin >> x;
		cout << "Kolumny: " << endl;
		cin >> y;

		int xplus1 = x + 1;
		int yplus1 = y + 1;
		int xminus1 = x - 1;
		int yminus1 = y - 1;
		int xplus2 = x + 2;
		int yplus2 = y + 2;
		int xminus2 = x - 2;
		int yminus2 = y - 2;


		//OKREŚLENIE WARUNKÓW POZYCJI NA PLANSZY DLA ZWYKŁEGO RUCHU PIONA CZARNEGO
		if ((bx - x == 1) && (plansza1[xminus1][yminus1] == 'X') && ((y - by == 1) || (y - by == (-1)))) {
			cout << "Wybrałeś dozwolony ruch. " << endl;
			bxminus1 = bx - 1;
			byminus1 = by - 1;
			plansza1[bxminus1][byminus1] = 'X';
			//USTAWIENIE NOWYCH POZYCJI PIONÓW PO DOKONANIU RUCHU
			w1 = x - 1;
			k1 = y - 1;
			plansza1[w1][k1] = 'C';
			int odp;
			cout << "Żeby zaktualizować planszę - wciśnij 1. ";
			cin >> odp;
			if (odp == 1) {
				system("cls");

				cout << "Trwa aktualizacja planszy: " << endl;
				//USTAWIENIE NOWYCH POZYCJI PIONÓW PO DOKONANIU RUCHU


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
			cout << "Wybrałeś niedozwolony ruch. Spróbuj ponownie." << endl;
			wybor_czarnego_piona_1(bx, by);
			//ZAPOBIEGANIE PRZED WYBOREM NIEPRAWIDŁOWEGO RUCHU
		}
	}

	//5.
	//WYBÓR NIEPRAWIDŁOWEGO PIONA CZARNEGO
	else {
		cout << "Wybrałeś nieodpowiedniego pionka. Spróbuj ponownie." << endl;
		wybor_czarnego_piona_1(bx, by);
	}


};
void czarna_dama_1() {

	if (plansza1[0][1] == 'C') {
		plansza1[0][1] = 'c';
		system("cls");
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
	else if (plansza1[0][3] == 'C') {
		plansza1[0][3] = 'c';
		system("cls");
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
	else if (plansza1[0][5] == 'C') {
		plansza1[0][5] = 'c';
		system("cls");
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
	else if (plansza1[0][7] == 'C') {
		plansza1[0][7] = 'c';
		system("cls");
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


};

void wybor_bialego_piona_2(int bx, int by) {/*uzycie zaprzyjaznionej funkcji do klasy, funkcja kontroluje prawidlowy wybor piona,
nie mozna wybrac piona innego niz bialy i piona, ktory nie lezy na linii ofensywnej*/
	if (cin.fail()) {
		cin.clear();
		cin.ignore();
	}

	cout << "Wybierz białego pionka, którym chcesz ruszyć (podaj kolejno wiersz i pole, na którym pionek się znajduje). " << endl;
	cout << "Wiersze: " << endl;
	cin >> bx;
	cout << "Kolumny: " << endl;
	cin >> by;

	int bxminus1 = bx - 1;
	int byminus1 = by - 1;
	int bxplus1 = bx + 1;
	int byplus1 = by + 1;
	int bxminus2 = bx - 2;
	int byminus2 = by - 2;
	int bxplus2 = bx + 2;
	int byplus2 = by + 2;
	int byminus3 = by - 3;
	int bxplus3 = bx + 3;
	int byplus3 = by + 3;
	int bxminus4 = bx - 4;
	int byminus4 = by - 4;
	int bxplus4 = bx + 4;
	int byplus4 = by + 4;
	int bxminus5 = bx - 5;
	int byminus5 = by - 5;
	int bxplus5 = bx + 5;
	int byplus5 = by + 5;



	if ((plansza2[bx][by] == 'B') && (plansza2[bxplus1][byplus1] == 'C') && (plansza2[bxplus1][byminus1] == 'C') && (plansza2[bxplus2][byplus2] == 'X') && (plansza2[bxplus2][byminus2] == 'X')) {
		cout << "Możesz zbić przeciwnika w obie strony. Zdecyduj, którą opcję wybierasz." << endl;
		int odpowiedz;
		cout << "Jeśli wybierasz bicie w prawą stronę wciśnij 1, jeśli wybierasz bicie w lewą stronę wciśnij 2. " << endl;
		cin >> odpowiedz;
		switch (odpowiedz) {
		case 1:
			cout << "Następuje bicie piona czarnego przez piona białego." << endl;
			plansza2[bx][by] = 'X';
			liczba_czarnych_pionków = liczba_czarnych_pionków - 1;
			plansza2[bxplus1][byplus1] = 'X';
			plansza2[bxplus2][byplus2] = 'B';
			int odp;
			cout << "Żeby zaktualizować planszę - wciśnij 1. ";
			cin >> odp;
			if (odp == 1) {
				system("cls");

				cout << "Trwa aktualizacja planszy: " << endl;




				for (int i = 0; i < 1; i++) {
					cout << "   ";
					for (int j = 1; j < kolumny + 1; j++) {
						plansza2[i][j] = NULL;
						cout << j << " ";
					}
					cout << endl;

				}


				nr = 0;
				for (int i = 1; i < wiersze + 1; i++) {
					cout << "";
					nr++;
					cout << nr << "  ";
					for (int j = 1; j < kolumny + 1; j++) {
						cout << plansza2[i][j] << "|";//WYWOŁANIE NA EKRAN DYNAMICZNEJ PLANSZY

					}
					cout << endl;

				}

				if ((plansza2[bxplus3][byplus1] == 'C' && plansza2[bxplus4][by] == 'X') || (plansza2[bxplus3][byplus3] == 'C' && plansza2[bxplus4][byplus4] == 'X')) {
					cout << "Czy chcesz bić dalej? Wciśnij 1, jeśli tak, wciśnij 2, jeśli nie." << endl;
					int o;
					cin >> o;

					if (o == 1) {
						cout << "Pamiętaj, żeby wybrać tego samego piona. " << endl;
						new_bx = bxplus2;
						new_by = byplus2;
						wybor_bialego_piona_2(new_bx, new_by);

						break;
					}
					else if (o == 2) {
						break;
					}
				}
			}
			break;
		case 2:
			cout << "Następuje bicie piona czarnego przez piona białego." << endl;

			plansza2[bx][by] = 'X';
			liczba_czarnych_pionków = liczba_czarnych_pionków - 1;
			plansza2[bxplus1][byminus1] = 'X';
			plansza2[bxplus2][byminus2] = 'B';

			int odpow;
			cout << "Żeby zaktualizować planszę - wciśnij 1. ";
			cin >> odpow;
			if (odpow == 1) {
				system("cls");

				cout << "Trwa aktualizacja planszy: " << endl;


				for (int i = 0; i < 1; i++) {
					cout << "   ";
					for (int j = 1; j < kolumny + 1; j++) {
						plansza2[i][j] = NULL;
						cout << j << " ";
					}
					cout << endl;

				}


				nr = 0;
				for (int i = 1; i < wiersze + 1; i++) {
					cout << "";
					nr++;
					cout << nr << "  ";
					for (int j = 1; j < kolumny + 1; j++) {
						cout << plansza2[i][j] << "|";//WYWOŁANIE NA EKRAN DYNAMICZNEJ PLANSZY

					}
					cout << endl;

				}

				if ((plansza2[bxplus4][byminus2] == 'C' && plansza2[bxplus5][byminus3] == 'X') || (plansza2[bxplus4][by] == 'C' && plansza2[bxplus5][byplus1] == 'X')) {
					cout << "Czy chcesz bić dalej? Wciśnij 1, jeśli tak, wciśnij 2, jeśli nie." << endl;
					int o;
					cin >> o;

					if (o == 1) {
						cout << "Pamiętaj, żeby wybrać tego samego piona. " << endl;
						new_bx = bxplus3;
						new_by = byminus3;
						wybor_bialego_piona_2(new_bx, new_by);

						break;
					}
					else if (o == 2) {
						break;
					}
				}
			}
			break;
		default: cout << "Nie wybrałeś żadnej opcji. Spróbuj ponownie" << endl;
			wybor_bialego_piona_2(bx, by);
		}

	}

	else if ((plansza2[bx][by] == 'B') && ((plansza2[bxplus1][byplus1] == 'C') && (plansza2[bxplus2][byplus2] == 'X'))) {

		cout << "Czy chcesz zbić pionka przeciwnika w prawą stronę? Wciśnij 1, jeśli tak, wciśnij 2, jeśli chcesz i możesz ruszyć się w lewo." << endl;
		int odpowiedz = 0;
		cin >> odpowiedz;
		switch (odpowiedz) {
		case 1:
			cout << "Następuje bicie piona czarnego przez piona białego." << endl;

			plansza2[bx][by] = 'X';
			liczba_czarnych_pionków = liczba_czarnych_pionków - 1;
			plansza2[bxplus1][byplus1] = 'X';
			plansza2[bxplus2][byplus2] = 'B';
			int odp;
			cout << "Żeby zaktualizować planszę - wciśnij 1. ";
			cin >> odp;
			if (odp == 1) {
				system("cls");

				cout << "Trwa aktualizacja planszy: " << endl;


				for (int i = 0; i < 1; i++) {
					cout << "   ";
					for (int j = 1; j < kolumny + 1; j++) {
						plansza2[i][j] = NULL;
						cout << j << " ";
					}
					cout << endl;

				}


				nr = 0;
				for (int i = 1; i < wiersze + 1; i++) {
					cout << "";
					nr++;
					cout << nr << "  ";
					for (int j = 1; j < kolumny + 1; j++) {
						cout << plansza2[i][j] << "|";//WYWOŁANIE NA EKRAN DYNAMICZNEJ PLANSZY

					}
					cout << endl;

				}

				if ((plansza2[bxplus3][byplus1] == 'C' && plansza2[bxplus4][by] == 'X') || (plansza2[bxplus3][byplus3] == 'C' && plansza2[bxplus4][byplus4] == 'X')) {
					cout << "Czy chcesz bić dalej? Wciśnij 1, jeśli tak, wciśnij 2, jeśli nie." << endl;
					int o;
					cin >> o;

					if (o == 1) {
						cout << "Pamiętaj, żeby wybrać tego samego piona. " << endl;
						new_bx = bxplus2;
						new_by = byplus2;
						wybor_bialego_piona_2(new_bx, new_by);

						break;
					}
					else if (o == 2) {
						break;
					}
				}
			}
			break;
		case 2:

			if ((plansza2[bx][by] == 'B') && (plansza2[bxplus1][byminus1] == 'X')) {

				plansza2[bx][by] = 'X';
				plansza2[bxplus1][byminus1] = 'B';
				int odp;
				cout << "Żeby zaktualizować planszę - wciśnij 1. ";
				cin >> odp;
				if (odp == 1) {
					system("cls");

					cout << "Trwa aktualizacja planszy: " << endl;

					for (int i = 0; i < 1; i++) {
						cout << "   ";
						for (int j = 1; j < kolumny + 1; j++) {
							plansza2[i][j] = NULL;
							cout << j << " ";
						}
						cout << endl;

					}


					nr = 0;
					for (int i = 1; i < wiersze + 1; i++) {
						cout << "";
						nr++;
						cout << nr << "  ";
						for (int j = 1; j < kolumny + 1; j++) {
							cout << plansza2[i][j] << "|";//WYWOŁANIE NA EKRAN DYNAMICZNEJ PLANSZY

						}
						cout << endl;

					}
				}
			}
			else {
				cout << "Dokonałeś niepoprawnego wyboru. Spróbuj ponownie." << endl;
				wybor_bialego_piona_2(bx, by);
			}
			break;
		default: cout << "Nie wybrałeś żadnej opcji. Spróbuj ponownie" << endl;
			wybor_bialego_piona_2(bx, by);
		}
	}
	else if ((plansza2[bx][by] == 'B') && ((plansza2[bxplus1][byminus1] == 'C') && (plansza2[bxplus2][byminus2] == 'X'))) {

		cout << "Czy chcesz zbić pionka przeciwnika w lewą stronę? Wciśnij 1, jeśli tak, wciśnij 2, jeśli chcesz i możesz ruszyć się w lewo." << endl;
		int odpowiedz = 0;
		cin >> odpowiedz;
		switch (odpowiedz) {
		case 1:
			cout << "Następuje bicie piona czarnego przez piona białego." << endl;

			plansza2[bx][by] = 'X';
			liczba_czarnych_pionków = liczba_czarnych_pionków - 1;
			plansza2[bxplus1][byminus1] = 'X';
			plansza2[bxplus2][byminus2] = 'B';
			int odp;
			cout << "Żeby zaktualizować planszę - wciśnij 1. ";
			cin >> odp;
			if (odp == 1) {
				system("cls");

				cout << "Trwa aktualizacja planszy: " << endl;


				for (int i = 0; i < 1; i++) {
					cout << "   ";
					for (int j = 1; j < kolumny + 1; j++) {
						plansza2[i][j] = NULL;
						cout << j << " ";
					}
					cout << endl;

				}


				nr = 0;
				for (int i = 1; i < wiersze + 1; i++) {
					cout << "";
					nr++;
					cout << nr << "  ";
					for (int j = 1; j < kolumny + 1; j++) {
						cout << plansza2[i][j] << "|";//WYWOŁANIE NA EKRAN DYNAMICZNEJ PLANSZY

					}
					cout << endl;

				}

				if ((plansza2[bxplus3][byminus3] == 'C' && plansza2[bxplus4][byminus4] == 'X') || (plansza2[bxplus3][byminus1] == 'C' && plansza2[bxplus4][by] == 'X')) {
					cout << "Czy chcesz bić dalej? Wciśnij 1, jeśli tak, wciśnij 2, jeśli nie." << endl;
					int o;
					cin >> o;

					if (o == 1) {
						cout << "Pamiętaj, żeby wybrać tego samego piona. " << endl;
						new_bx = bxplus2;
						new_by = byminus4;
						wybor_bialego_piona_2(new_bx, new_by);

						break;
					}
					else if (o == 2) {
						break;
					}
				}

			}
			break;
		case 2:

			if ((plansza2[bx][by] == 'B') && (plansza2[bxplus1][byplus1] == 'X')) {

				plansza2[bx][by] = 'X';
				plansza2[bxplus1][byplus1] = 'B';
				int odp;
				cout << "Żeby zaktualizować planszę - wciśnij 1. ";
				cin >> odp;
				if (odp == 1) {
					system("cls");
					cout << "Trwa aktualizacja planszy: " << endl;

					for (int i = 0; i < 1; i++) {
						cout << "   ";
						for (int j = 1; j < kolumny + 1; j++) {
							plansza2[i][j] = NULL;
							cout << j << " ";
						}
						cout << endl;

					}


					nr = 0;
					for (int i = 1; i < wiersze + 1; i++) {
						cout << "";
						nr++;
						cout << nr << "  ";
						for (int j = 1; j < kolumny + 1; j++) {
							cout << plansza2[i][j] << "|";//WYWOŁANIE NA EKRAN DYNAMICZNEJ PLANSZY

						}
						cout << endl;

					}

				}
			}
			else {
				cout << "Dokonałeś niepoprawnego wyboru. Spróbuj ponownie." << endl;
				wybor_bialego_piona_2(bx, by);
			}
			break;
		default: cout << "Nie wybrałeś żadnej opcji. Spróbuj ponownie" << endl;
			wybor_bialego_piona_2(bx, by);
		}
	}
	else if ((plansza2[bx][by] == 'B') && ((plansza2[bxplus1][byminus1] == 'X') || (plansza2[bxplus1][byplus1] == 'X'))) {

		cout << "Wybrałeś odpowiedniego pionka." << endl;

		cout << "Wybierz pole, na które chcesz ruszyć (podaj kolejno wiersz i pole, na którym pionek ma się znajdować). " << endl;
		cout << "Wiersze: " << endl;
		cin >> x;
		cout << "Kolumny: " << endl;
		cin >> y;

		int xplus1 = x + 1;
		int yplus1 = y + 1;
		int xminus1 = x - 1;
		int yminus1 = y - 1;
		int xplus2 = x + 2;
		int yplus2 = y + 2;
		int xminus2 = x - 2;
		int yminus2 = y - 2;



		if ((x - bx == 1) && (plansza2[x][y] == 'X') && ((y - by == 1) || (y - by == (-1)))) {
			cout << "Wybrałeś dozwolony ruch. " << endl;

			plansza2[bx][by] = 'X';
			plansza2[x][y] = 'B';
			int odp;
			cout << "Żeby zaktualizować planszę - wciśnij 1. ";
			cin >> odp;
			if (odp == 1) {
				system("cls");

				cout << "Trwa aktualizacja planszy: " << endl;





				for (int i = 0; i < 1; i++) {
					cout << "   ";
					for (int j = 1; j < kolumny + 1; j++) {
						plansza2[i][j] = NULL;
						cout << j << " ";
					}
					cout << endl;

				}


				nr = 0;
				for (int i = 1; i < wiersze + 1; i++) {
					cout << "";
					nr++;
					cout << nr << "  ";
					for (int j = 1; j < kolumny + 1; j++) {
						cout << plansza2[i][j] << "|";//WYWOŁANIE NA EKRAN DYNAMICZNEJ PLANSZY

					}
					cout << endl;

				}

			}
		}

		else {
			cout << "Wybrałeś niedozwolony ruch. Spróbuj ponownie." << endl;
			wybor_bialego_piona_2(bx, by);
		}
	}



	else {
		cout << "Wybrałeś nieodpowiedniego pionka. Spróbuj ponownie." << endl;
		wybor_bialego_piona_2(bx, by);
	}


};

void wybor_czarnego_piona_2(int bx, int by) {/*uzycie zaprzyjaznionej funkcji do klasy, funkcja kontroluje prawidlowy wybor piona,
nie mozna wybrac piona innego niz bialy i piona, ktory nie lezy na linii ofensywnej*/
	if (cin.fail()) {
		cin.clear();
		cin.ignore();
	}

	cout << "Wybierz czarnego pionka, którym chcesz ruszyć (podaj kolejno wiersz i pole, na którym pionek się znajduje). " << endl;
	cout << "Wiersze: " << endl;
	cin >> bx;
	cout << "Kolumny: " << endl;
	cin >> by;

	int bxminus1 = bx - 1;
	int byminus1 = by - 1;
	int bxplus1 = bx + 1;
	int byplus1 = by + 1;
	int bxminus2 = bx - 2;
	int byminus2 = by - 2;
	int bxplus2 = bx + 2;
	int byplus2 = by + 2;
	int bxminus3 = bx - 3;
	int byminus3 = by - 3;
	int bxplus3 = bx + 3;
	int byplus3 = by + 3;
	int bxminus4 = bx - 4;
	int byminus4 = by - 4;
	int bxplus4 = bx + 4;
	int byplus4 = by + 4;
	int bxminus5 = bx - 5;
	int byminus5 = by - 5;
	int bxplus5 = bx + 5;
	int byplus5 = by + 5;

	if ((plansza2[bx][by] == 'C') && (plansza2[bxminus1][byminus1] == 'B') && (plansza2[bxminus1][byplus1] == 'B') && (plansza2[bxminus2][byplus2] == 'X') && (plansza2[bxminus2][byminus4] == 'X')) {
		cout << "Możesz zbić przeciwnika w obie strony. Zdecyduj, którą opcję wybierasz." << endl;
		int odpowiedz;
		cout << "Jeśli wybierasz bicie w prawą stronę wciśnij 1, jeśli wybierasz bicie w lewą stronę wciśnij 2. " << endl;
		cin >> odpowiedz;
		switch (odpowiedz) {
		case 1:
			cout << "Następuje bicie piona białego przez piona czarnego." << endl;
			plansza2[bx][by] = 'X';

			plansza2[bxminus1][byplus1] = 'X';
			plansza2[bxminus2][byplus2] = 'C';
			liczba_białych_pionków = liczba_białych_pionków - 1;

			int odp;
			cout << "Żeby zaktualizować planszę - wciśnij 1. ";
			cin >> odp;
			if (odp == 1) {
				system("cls");

				cout << "Trwa aktualizacja planszy: " << endl;



				for (int i = 0; i < 1; i++) {
					cout << "   ";
					for (int j = 1; j < kolumny + 1; j++) {
						plansza2[i][j] = NULL;
						cout << j << " ";
					}
					cout << endl;

				}


				nr = 0;
				for (int i = 1; i < wiersze + 1; i++) {
					cout << "";
					nr++;
					cout << nr << "  ";
					for (int j = 1; j < kolumny + 1; j++) {
						cout << plansza2[i][j] << "|";//WYWOŁANIE NA EKRAN DYNAMICZNEJ PLANSZY

					}
					cout << endl;

				}

				if ((plansza2[bxminus3][byplus1] == 'B' && plansza2[bxminus4][by] == 'X') || (plansza2[bxminus3][byplus3] == 'B' && plansza2[bxminus4][byplus4] == 'X')) {
					cout << "Czy chcesz bić dalej? Wciśnij 1, jeśli tak, wciśnij 2, jeśli nie." << endl;
					int o;
					cin >> o;

					if (o == 1) {
						cout << "Pamiętaj, żeby wybrać tego samego piona. " << endl;
						new_bx = bxminus2;
						new_by = byplus2;
						wybor_czarnego_piona_2(new_bx, new_by);

						break;
					}
					else if (o == 2) {
						break;
					}
				}
			}
			break;
		case 2:
			cout << "Następuje bicie piona białego przez piona czarnego." << endl;

			plansza2[bx][by] = 'X';
			liczba_białych_pionków = liczba_białych_pionków - 1;
			plansza2[bx][by] = 'X';
			plansza2[bxminus1][byminus1] = 'X';
			plansza2[bxminus2][byminus2] = 'C';
			int odpow;
			cout << "Żeby zaktualizować planszę - wciśnij 1. ";
			cin >> odpow;
			if (odp == 1) {
				system("cls");

				cout << "Trwa aktualizacja planszy: " << endl;



				for (int i = 0; i < 1; i++) {
					cout << "   ";
					for (int j = 1; j < kolumny + 1; j++) {
						plansza2[i][j] = NULL;
						cout << j << " ";
					}
					cout << endl;

				}


				nr = 0;
				for (int i = 1; i < wiersze + 1; i++) {
					cout << "";
					nr++;
					cout << nr << "  ";
					for (int j = 1; j < kolumny + 1; j++) {
						cout << plansza2[i][j] << "|";//WYWOŁANIE NA EKRAN DYNAMICZNEJ PLANSZY

					}
					cout << endl;

				}

				if ((plansza2[bxminus3][byminus3] == 'B' && plansza2[bxminus4][byminus4] == 'X') || (plansza2[bxminus3][byminus1] == 'B' && plansza2[bxminus4][by] == 'X')) {
					cout << "Czy chcesz bić dalej? Wciśnij 1, jeśli tak, wciśnij 2, jeśli nie." << endl;
					int o;
					cin >> o;

					if (o == 1) {
						cout << "Pamiętaj, żeby wybrać tego samego piona. " << endl;
						new_bx = bxminus2;
						new_by = byminus2;
						wybor_czarnego_piona_2(new_bx, new_by);

						break;
					}
					else if (o == 2) {
						break;
					}
				}
			}

			break;
		default: cout << "Nie wybrałeś żadnej opcji. Spróbuj ponownie" << endl;
			wybor_czarnego_piona_2(bx, by);
		}

	}
	else if ((plansza2[bx][by] == 'C') && ((plansza2[bxminus1][byplus1] == 'B') && (plansza2[bxminus2][byplus2] == 'X'))) {

		cout << "Czy chcesz zbić pionka przeciwnika w prawą stronę? Wciśnij 1, jeśli tak, wciśnij 2, jeśli nie." << endl;
		int odpowiedz = 0;
		cin >> odpowiedz;
		switch (odpowiedz) {
		case 1:
			cout << "Następuje bicie piona białego przez piona czarnego." << endl;

			plansza2[bx][by] = 'X';
			liczba_białych_pionków = liczba_białych_pionków - 1;
			plansza2[bxminus1][byplus1] = 'X';
			plansza2[bxminus2][byplus2] = 'C';
			int odp;
			cout << "Żeby zaktualizować planszę - wciśnij 1. ";
			cin >> odp;
			if (odp == 1) {
				system("cls");

				cout << "Trwa aktualizacja planszy: " << endl;



				for (int i = 0; i < 1; i++) {
					cout << "   ";
					for (int j = 1; j < kolumny + 1; j++) {
						plansza2[i][j] = NULL;
						cout << j << " ";
					}
					cout << endl;

				}


				nr = 0;
				for (int i = 1; i < wiersze + 1; i++) {
					cout << "";
					nr++;
					cout << nr << "  ";
					for (int j = 1; j < kolumny + 1; j++) {
						cout << plansza2[i][j] << "|";//WYWOŁANIE NA EKRAN DYNAMICZNEJ PLANSZY

					}
					cout << endl;

				}

				if ((plansza2[bxminus3][byplus1] == 'B' && plansza2[bxminus4][by] == 'X') || (plansza2[bxminus3][byplus3] == 'B' && plansza2[bxminus4][byplus4] == 'X')) {
					cout << "Czy chcesz bić dalej? Wciśnij 1, jeśli tak, wciśnij 2, jeśli nie." << endl;
					int o;
					cin >> o;

					if (o == 1) {
						cout << "Pamiętaj, żeby wybrać tego samego piona. " << endl;
						new_bx = bxminus2;
						new_by = byplus2;
						wybor_czarnego_piona_2(new_bx, new_by);

						break;
					}
					else if (o == 2) {
						break;
					}
				}
			}
			break;
		case 2:

			if ((plansza2[bx][by] == 'C') && (plansza2[bxminus1][byminus1] == 'X')) {

				plansza2[bx][by] = 'X';
				plansza2[bxminus1][byminus1] = 'C';
				int odp;
				cout << "Żeby zaktualizować planszę - wciśnij 1. ";
				cin >> odp;
				if (odp == 1) {
					system("cls");
					cout << "Trwa aktualizacja planszy." << endl;

					for (int i = 0; i < 1; i++) {
						cout << "   ";
						for (int j = 1; j < kolumny + 1; j++) {
							plansza2[i][j] = NULL;
							cout << j << " ";
						}
						cout << endl;

					}


					nr = 0;
					for (int i = 1; i < wiersze + 1; i++) {
						cout << "";
						nr++;
						cout << nr << "  ";
						for (int j = 1; j < kolumny + 1; j++) {
							cout << plansza2[i][j] << "|";//WYWOŁANIE NA EKRAN DYNAMICZNEJ PLANSZY

						}
						cout << endl;

					}
				}
			}
			else {
				cout << "Dokonałeś niepoprawnego wyboru. Spróbuj ponownie." << endl;
				wybor_czarnego_piona_2(bx, by);
			}
			break;
		default: cout << "Nie wybrałeś żadnej opcji. Spróbuj ponownie" << endl;
			wybor_czarnego_piona_2(bx, by);

		}
	}
	else if ((plansza2[bx][by] == 'C') && ((plansza2[bxminus1][byminus1] == 'B') && (plansza2[bxminus2][byminus2] == 'X'))) {

		cout << "Czy chcesz zbić pionka przeciwnika w lewą stronę? Wciśnij 1, jeśli tak, wciśnij 2, jeśli nie." << endl;
		int odpowiedz = 0;
		cin >> odpowiedz;
		switch (odpowiedz) {
		case 1:
			cout << "Następuje bicie piona białego przez piona czarnego." << endl;

			plansza2[bx][by] = 'X';
			liczba_białych_pionków = liczba_białych_pionków - 1;
			plansza2[bx][by] = 'X';
			plansza2[bxminus1][byminus1] = 'X';
			plansza2[bxminus2][byminus2] = 'C';
			int odp;
			cout << "Żeby zaktualizować planszę - wciśnij 1. ";
			cin >> odp;
			if (odp == 1) {
				system("cls");

				cout << "Trwa aktualizacja planszy: " << endl;



				for (int i = 0; i < 1; i++) {
					cout << "   ";
					for (int j = 1; j < kolumny + 1; j++) {
						plansza2[i][j] = NULL;
						cout << j << " ";
					}
					cout << endl;

				}


				nr = 0;
				for (int i = 1; i < wiersze + 1; i++) {
					cout << "";
					nr++;
					cout << nr << "  ";
					for (int j = 1; j < kolumny + 1; j++) {
						cout << plansza2[i][j] << "|";//WYWOŁANIE NA EKRAN DYNAMICZNEJ PLANSZY

					}
					cout << endl;

				}

				if ((plansza2[bxminus3][byminus3] == 'B' && plansza2[bxminus4][byminus4] == 'X') || (plansza2[bxminus3][byminus1] == 'B' && plansza2[bxminus4][by] == 'X')) {
					cout << "Czy chcesz bić dalej? Wciśnij 1, jeśli tak, wciśnij 2, jeśli nie." << endl;
					int o;
					cin >> o;

					if (o == 1) {
						cout << "Pamiętaj, żeby wybrać tego samego piona. " << endl;
						new_bx = bxminus2;
						new_by = byminus2;
						wybor_czarnego_piona_2(new_bx, new_by);

						break;
					}
					else if (o == 2) {
						break;
					}
				}
			}
			break;
		case 2:

			if ((plansza2[bx][by] == 'C') && (plansza2[bxminus1][byplus1] == 'X')) {

				plansza2[bx][by] = 'X';
				plansza2[bxminus1][byplus1] = 'C';
				int odp;
				cout << "Żeby zaktualizować planszę - wciśnij 1. ";
				cin >> odp;
				if (odp == 1) {
					system("cls");

					cout << "Trwa aktualizacja planszy: " << endl;

					for (int i = 0; i < 1; i++) {
						cout << "   ";
						for (int j = 1; j < kolumny + 1; j++) {
							plansza2[i][j] = NULL;
							cout << j << " ";
						}
						cout << endl;

					}


					nr = 0;
					for (int i = 1; i < wiersze + 1; i++) {
						cout << "";
						nr++;
						cout << nr << "  ";
						for (int j = 1; j < kolumny + 1; j++) {
							cout << plansza2[i][j] << "|";//WYWOŁANIE NA EKRAN DYNAMICZNEJ PLANSZY

						}
						cout << endl;

					}
				}
			}
			else {
				cout << "Dokonałeś niepoprawnego wyboru. Spróbuj ponownie." << endl;
				wybor_czarnego_piona_2(bx, by);
			}
			break;
		default: cout << "Nie wybrałeś żadnej opcji. Spróbuj ponownie" << endl;
			wybor_czarnego_piona_2(bx, by);
		}
	}
	else if ((plansza2[bx][by] == 'C') && ((plansza2[bxminus1][byminus1] == 'X') || (plansza2[bxminus1][byplus1] == 'X'))) {

		cout << "Wybrałeś odpowiedniego pionka." << endl;

		cout << "Wybierz pole, na które chcesz ruszyć (podaj kolejno wiersz i pole, na którym pionek ma się znajdować). " << endl;
		cout << "Wiersze: " << endl;
		cin >> x;
		cout << "Kolumny: " << endl;
		cin >> y;

		int xplus1 = x + 1;
		int yplus1 = y + 1;
		int xminus1 = x - 1;
		int yminus1 = y - 1;
		int xplus2 = x + 2;
		int yplus2 = y + 2;
		int xminus2 = x - 2;
		int yminus2 = y - 2;



		if ((bx - x == 1) && (plansza2[x][y] == 'X') && ((y - by == 1) || (y - by == (-1)))) {
			cout << "Wybrałeś dozwolony ruch. " << endl;
			bxminus1 = bx - 1;
			byminus1 = by - 1;
			plansza2[bx][by] = 'X';
			plansza2[x][y] = 'C';
			int odp;
			cout << "Żeby zaktualizować planszę - wciśnij 1. ";
			cin >> odp;
			if (odp == 1) {
				system("cls");

				cout << "Trwa aktualizacja planszy: " << endl;




				for (int i = 0; i < 1; i++) {
					cout << "   ";
					for (int j = 1; j < kolumny + 1; j++) {
						plansza2[i][j] = NULL;
						cout << j << " ";
					}
					cout << endl;

				}


				nr = 0;
				for (int i = 1; i < wiersze + 1; i++) {
					cout << "";
					nr++;
					cout << nr << "  ";
					for (int j = 1; j < kolumny + 1; j++) {
						cout << plansza2[i][j] << "|";//WYWOŁANIE NA EKRAN DYNAMICZNEJ PLANSZY

					}
					cout << endl;

				}
			}
		}

		else {
			cout << "Wybrałeś niedozwolony ruch. Spróbuj ponownie." << endl;
			wybor_czarnego_piona_2(bx, by);
		}
	}

	else {
		cout << "Wybrałeś nieodpowiedniego pionka. Spróbuj ponownie." << endl;
		wybor_czarnego_piona_2(bx, by);
	}


};



void zapis_do_pliku_1(int i, int j) {

	ofstream zapis1("dane1.txt", ios::out);//OTWORZENIE PLIKU

	zapis1 << 0 << " " << 1 << " " << 2 << " " << 3 << " " << 4 << " " << 5 << " " << 6 << " " << 7 << " " << 8 << endl;
	nr = 0;
	for (int i = 0; i < 8; i++) {//RYSOWANIE WIERSZY
		nr++;
		zapis1 << nr << " ";
		for (int j = 0; j < 8; j++)//RYSOWANIE KOLUMN
		{
			zapis1 << plansza1[i][j] << "|";
		}
		zapis1 << endl;
	}

	zapis1 << "Liczba białych pionów: " << liczba_białych_pionków << endl;
	zapis1 << "Liczba czarnych pionów: " << liczba_czarnych_pionków << endl;
	zapis1 << endl;

	zapis1 << "Numer ruchu: " << numer_ruchu << endl;
	if (numer_ruchu % 2 == 0) {
		zapis1 << endl;
		zapis1 << "RUCH CZARNEGO GRACZA." << endl;
	}
	else {
		zapis1 << endl;
		zapis1 << "RUCH BIAŁEGO GRACZA." << endl;
	}

	zapis1.close(); //ZAMKNIĘCIE PLIKU



};

void zapis_do_pliku_2(int i, int j) {

	ofstream zapis2("dane2.txt");//OTWORZENIE PLIKU


	for (int i = 0; i < 1; i++) {
		zapis2 << "   ";
		for (int j = 1; j < kolumny + 1; j++) {
			plansza2[i][j] = NULL;
			zapis2 << j << " ";
		}
		zapis2 << endl;

	}


	nr = 0;
	for (int i = 1; i < wiersze + 1; i++) {
		zapis2 << "";
		nr++;
		zapis2 << nr << "  ";
		for (int j = 1; j < kolumny + 1; j++) {
			zapis2 << plansza2[i][j] << "|";//WYWOŁANIE NA EKRAN DYNAMICZNEJ PLANSZY

		}
		zapis2 << endl;

	}


	zapis2 << endl;
	zapis2 << "Liczba białych pionów: " << liczba_białych_pionków << endl;
	zapis2 << "Liczba czarnych pionów: " << liczba_czarnych_pionków << endl;
	zapis2 << endl;

	zapis2 << "Numer ruchu: " << numer_ruchu << endl;
	if (numer_ruchu % 2 == 0) {
		zapis2 << endl;
		zapis2 << "RUCH CZARNEGO GRACZA." << endl;
	}
	else {
		zapis2 << endl;
		zapis2 << "RUCH BIAŁEGO GRACZA." << endl;
	}


	zapis2.close(); //ZAMKNIĘCIE PLIKU

};


int main()
{




	setlocale(LC_CTYPE, "Polish");//UMOŻLIWIENIE WSTAWIENIE POLSKICH ZNAKÓW DIAKRYTYCZNYCH
	Plansza plansza_1;
	Plansza plansza_2;
	cout << "\t\t\t" << "Witaj w grze WARCABY" << endl;
	cout << "Wybierz planszę do gry (możesz wybrać gotowy rozmiar (8x8 pól) lub wpisać własny)." << endl;
	int odpowiedz;
X: cout << "Jeśli wybierasz gotowy rozmiar wciśnij 1, jeśli chcesz wpisać własny rozmiar wciśnij 2. " << endl;
	cin >> odpowiedz;
	if (cin.fail()) {//ZAPOBIEGANIE WPISYWANIU NIEPRAWIDŁOWYCH DANYCH PRZEZ UŻYTKOWNIKA
		cin.clear();
		cin.ignore();
	}
	switch (odpowiedz) {//MOŻLIWOŚĆ WYBORU PLANSZY
	case 1:
		cout << "Wybrałeś gotowy rozmiar (8x8). " << endl;
		cout << endl;
		plansza_1.gotowa_plansza_1();
		cout << endl;
		cout << "Gotowy? Gramy! Zaczyna biały gracz. " << endl;

		do {
			cout << endl;
			cout << "Numer ruchu: " << numer_ruchu << endl;
			cout << endl;

			cout << "RUCH BIAŁEGO GRACZA." << endl;
			wybor_bialego_piona_1(bx, by);
			biala_dama_1();
			cout << "Liczba białych pionków to: " << liczba_białych_pionków << endl;
			cout << "Liczba czarnych pionków to: " << liczba_czarnych_pionków << endl;
			numer_ruchu++;
			zapis_do_pliku_1(i, j);//ZAPISYWANIE DANYCH DO PLIKU



			if (liczba_czarnych_pionków == 0) {
				cout << "Wygrał biały gracz. Gratulacje!" << endl;
				int zakonczenie;
				cout << "Wciśnij 1, żeby zakończyć." << endl;
				cin >> zakonczenie;
				if (zakonczenie == 1) {
					system("cls");
				}

			}

			cout << endl;
			cout << "Numer ruchu: " << numer_ruchu << endl;
			cout << endl;

			cout << "RUCH CZARNEGO GRACZA." << endl;
			wybor_czarnego_piona_1(bx, by);
			czarna_dama_1();
			cout << "Liczba białych pionków to: " << liczba_białych_pionków << endl;
			cout << "Liczba czarnych pionków to: " << liczba_czarnych_pionków << endl;
			numer_ruchu++;
			zapis_do_pliku_1(i, j);//ZAPISYWANIE DANYCH DO PLIKU


			if (liczba_białych_pionków == 0) {
				cout << "Wygrał czarny gracz. Gratulacje!" << endl;
				int zakonczenie;
				cout << "Wciśnij 1, żeby zakończyć." << endl;
				cin >> zakonczenie;
				if (zakonczenie == 1) {
					system("cls");
				}

			}


		} while ((liczba_białych_pionków > 0) || (liczba_czarnych_pionków > 0));
		//OKREŚLENIE WARUNKÓW KOŃCOWYCH GRY



		break;

	case 2:
		plansza_2.okresl_plansze_2();
		cout << endl;
		plansza_2.rysuj_plansze_2();
		cout << endl;
		cout << "Gotowy? Gramy! Zaczyna biały gracz. " << endl;
		do {
			cout << endl;
			cout << "Numer ruchu: " << numer_ruchu << endl;
			cout << endl;

			cout << "RUCH BIAŁEGO GRACZA." << endl;
			wybor_bialego_piona_2(bx, by);

			cout << "Liczba białych pionków to: " << liczba_białych_pionków << endl;
			cout << "Liczba czarnych pionków to: " << liczba_czarnych_pionków << endl;
			numer_ruchu++;
			zapis_do_pliku_2(i, j);

			if (liczba_czarnych_pionków == 0) {
				cout << "Wygrał biały gracz. Gratulacje!" << endl;
				int zakonczenie;
				cout << "Wciśnij 1, żeby zakończyć." << endl;
				cin >> zakonczenie;
				if (zakonczenie == 1) {
					system("cls");
				}

			}
			cout << endl;
			cout << "Numer ruchu: " << numer_ruchu << endl;
			cout << endl;

			cout << "RUCH CZARNEGO GRACZA." << endl;
			wybor_czarnego_piona_2(bx, by);
			cout << "Liczba białych pionków to: " << liczba_białych_pionków << endl;
			cout << "Liczba czarnych pionków to: " << liczba_czarnych_pionków << endl;
			numer_ruchu++;
			zapis_do_pliku_2(i, j);

			if (liczba_białych_pionków == 0) {
				cout << "Wygrał czarny gracz. Gratulacje!" << endl;
				int zakonczenie;
				cout << "Wciśnij 1, żeby zakończyć." << endl;
				cin >> zakonczenie;
				if (zakonczenie == 1) {
					system("cls");
				}
			}


		} while ((liczba_białych_pionków > 0) || (liczba_czarnych_pionków > 0));
		//OKREŚLENIE WARUNKÓW KOŃCOWYCH GRY

		for (int i = 0; i < wiersze; i++)//ZWALNIANIE PAMIĘCI W DYNAMICZNEJ PLANSZY
			delete[] plansza2[i];
		delete[] plansza2;

		break;

	default:
		cout << "Nie wybrałeś żadnej opcji. Spróbuj ponownie." << endl;
		cout << endl;
		goto X;//POWRÓT DO WYBORU PLANSZY, GDY UŻYTKOWNIK WPISZE NIEPRAWIDŁOWE DANE

		return 0;
	}



	return 0;
}