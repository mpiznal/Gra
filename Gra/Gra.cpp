#include <iostream>
#include <fstream>
#include <locale.h>
using namespace std;


int wiersze = 0, kolumny = 0;
int w1 = 0, w2 = 0, k1 = 0, k2 = 0;
int bx = 0, by = 0;//zmienne wyboru pionka
int new_bx = 0;
int new_by = 0;
int x = 0, y = 0;//zmienne ruchu pionka
int liczba_białych_pionków = 12;
int liczba_czarnych_pionków = 12;
int i = 0, j = 0;
int nr = 0;
char plansza1[8][8] = { ' ','B',' ','B',' ','B',' ','B',
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
	friend void wybor_bialego_piona_1(int bx, int by);
	friend void wybor_czarnego_piona_1(int bx, int by);
	friend void wybor_bialego_piona_2(int bx, int by);
	friend void wybor_czarnego_piona_2(int bx, int by);

	void gotowa_plansza_1() {//wywolywanie gotowej tablicy na ekran
		cout << 0 << " " << 1 << " " << 2 << " " << 3 << " " << 4 << " " << 5 << " " << 6 << " " << 7 << " " << 8 << endl;

		for (int i = 0; i < 8; i++) {//dla wierszy
			nr++;
			cout << nr << " ";
			for (int j = 0; j < 8; j++)//dla kolumn
			{
				cout << plansza1[i][j] << "|";
			}
			cout << endl;
		}
	}

	void okresl_plansze_2() {//ograniczenie tablicy dynamicznej co do wielkości wierszy, żeby można było stosować zasady gry
		cout << "Podaj liczbę wierszy - tu możesz podać tylko liczby parzyste - i kolumn (najmniejsza powierzchnia planszy to 8x8). " << endl;
		cout << "Liczba wierszy: " << endl;
		cin >> wiersze;
		if (wiersze % 2 != 0) {
			cout << "Wpisałeś niepoprawną liczbę wierszy. Spróbuj ponownie." << endl;
			okresl_plansze_2();
		}
		else {
			cout << "Liczba kolumn: " << endl;
			cin >> kolumny;
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

		plansza2 = new char* [wiersze];//tworzenie pierwszego wymiaru tablicy dynamicznej

		for (int i = 0; i < wiersze; i++)
			plansza2[i] = new char[kolumny];//tworzenie drugiego wymiaru tablicy dynamicznej


	}

	void rysuj_plansze_2() {
		//górna część planszy - określenie pól tablicy dynamicznej
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

		//dolna czesc planszy - określenie pól tablicy dynamicznej
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

		//środkowa część planszy - określenie pól tablicy dynamicznej
		for (int i = 3; i < wiersze - 3; i += 2)
			for (int j = 0; j < kolumny; j += 2)
				plansza2[i][j] = 'X';
		for (int i = 3; i < wiersze - 3; i += 2)
			for (int j = 1; j < kolumny; j += 2)
				plansza2[i][j] = ' ';

		for (int i = 4; i < wiersze - 3; i += 2)
			for (int j = 0; j < kolumny; j += 2)
				plansza2[i][j] = ' ';
		for (int i = 4; i < wiersze - 3; i += 2)
			for (int j = 1; j < kolumny; j += 2)
				plansza2[i][j] = 'X';


		for (int i = 0; i < 1; i++) {//wywoływanie na ekran oznaczeń kolumn dla tablicy dynamicznej
			cout << "  ";
			for (int j = 1; j < kolumny + 1; j++) {
				cout << j << " ";
			}
			cout << endl;
		}

		for (int i = 0; i < wiersze; i++) {
			cout << "";
			nr++;
			cout << nr << " ";
			for (int j = 0; j < kolumny; j++) {
				cout << plansza2[i][j] << "|";//wywoływanie na ekran tablicy dynamicznej
			}

			cout << endl;
		}
		cout << endl;

	}


};


void wybor_bialego_piona_1(int bx, int by) {/*uzycie zaprzyjaznionej funkcji do klasy, funkcja kontroluje prawidlowy wybor piona,
nie mozna wybrac piona innego niz bialy i piona, ktory nie lezy na linii ofensywnej*/

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


	//dla wyboru pionka i ruchu bijącego po obu stronach
	if ((plansza1[bxminus1][byminus1] == 'B') && (plansza1[bx][by] == 'C') && (plansza1[bx][by - 2] == 'C') && (plansza1[bxplus1][byplus1] == 'X') && (plansza1[bxplus1][byminus3] == 'X')) {
		cout << "Możesz zbić przeciwnika w obie strony. Zdecyduj, którą opcję wybierasz." << endl;
		int odpowiedz;
		cout << "Jeśli wybierasz bicie w prawą stronę wciśnij 1, jeśli wybierasz bicie w lewą stronę wciśnij 2. " << endl;
		cin >> odpowiedz;
		switch (odpowiedz) {
		case 1:
			cout << "Następuje bicie piona czarnego przez piona białego." << endl;
			bxminus1 = bx - 1;
			byminus1 = by - 1;
			plansza1[bxminus1][byminus1] = 'X';
			int odp;
			cout << "Żeby zaktualizować planszę - wciśnij 1. ";
			cin >> odp;
			if (odp == 1) {
				system("cls");

				cout << "Trwa aktualizacja planszy: " << endl;
				liczba_czarnych_pionków = liczba_czarnych_pionków - 1;//pomniejszanie liczby pionków
				plansza1[bx][by] = 'X';
				plansza1[bxplus1][byplus1] = 'B';

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
				if ((plansza1[bxplus2][by] == 'C' && plansza1[bxplus3][byminus1] == 'X') || (plansza1[bxplus2][byplus2] == 'C' && plansza1[bxplus3][byplus3] == 'X')) {
					cout << "Czy chcesz bić dalej? Wciśnij 1, jeśli tak, wciśnij 2, jeśli nie." << endl;
					int o;
					cin >> o;

					if (o == 1) {
						cout << "Pamiętaj, żeby wybrać tego samego piona. " << endl;
						new_bx = bxplus1;
						new_by = byplus1;
						wybor_bialego_piona_1(new_bx, new_by);

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
			bxminus1 = bx - 1;
			byminus1 = by - 1;
			plansza1[bxminus1][byminus1] = 'X';
			int odpow;
			cout << "Żeby zaktualizować planszę - wciśnij 1. ";
			cin >> odpow;
			if (odpow == 1) {
				system("cls");

				cout << "Trwa aktualizacja planszy: " << endl;
				liczba_czarnych_pionków = liczba_czarnych_pionków - 1;
				plansza1[bx][byminus2] = 'X';
				plansza1[bxplus1][byminus3] = 'B';

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
				if ((plansza1[bxplus2][byminus4] == 'C' && plansza1[bxplus3][byminus5] == 'X') || (plansza1[bxplus2][byminus2] == 'C' && plansza1[bxplus3][byminus1] == 'X')) {
					cout << "Czy chcesz bić dalej? Wciśnij 1, jeśli tak, wciśnij 2, jeśli nie." << endl;
					int o;
					cin >> o;

					if (o == 1) {
						cout << "Pamiętaj, żeby wybrać tego samego piona. " << endl;
						new_bx = bxplus1;
						new_by = byminus3;
						wybor_bialego_piona_1(new_bx, new_by);

						break;
					}
					else if (o == 2) {
						break;
					}
				}
			}

			break;
		default: cout << "Nie wybrałeś żadnej opcji. Spróbuj ponownie" << endl;
			wybor_bialego_piona_1(bx, by);
		}


	}

	//dla wyboru pionka i ruchu bijącego w prawo
	else if ((plansza1[bxminus1][byminus1] == 'B') && ((plansza1[bx][by] == 'C') && (plansza1[bxplus1][byplus1] == 'X'))) {

		cout << "Czy chcesz zbić pionka przeciwnika w prawą stronę? Wciśnij 1, jeśli tak, wciśnij 2, jeśli chcesz i możesz ruszyć się w lewo." << endl;
		int odpowiedz = 0;
		cin >> odpowiedz;
		switch (odpowiedz) {
		case 1:
			cout << "Następuje bicie piona czarnego przez piona białego." << endl;
			bxminus1 = bx - 1;
			byminus1 = by - 1;
			plansza1[bxminus1][byminus1] = 'X';


			int odp;
			cout << "Żeby zaktualizować planszę - wciśnij 1. ";
			cin >> odp;
			if (odp == 1) {
				system("cls");
				liczba_czarnych_pionków = liczba_czarnych_pionków - 1;
				cout << "Trwa aktualizacja planszy: " << endl;

				plansza1[bx][by] = 'X';
				plansza1[bxplus1][byplus1] = 'B';
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
				if ((plansza1[bxplus2][by] == 'C' && plansza1[bxplus3][byminus1] == 'X') || (plansza1[bxplus2][byplus2] == 'C' && plansza1[bxplus3][byplus3] == 'X')) {
					cout << "Czy chcesz bić dalej? Wciśnij 1, jeśli tak, wciśnij 2, jeśli nie." << endl;
					int o;
					cin >> o;

					if (o == 1) {
						cout << "Pamiętaj, żeby wybrać tego samego piona. " << endl;
						new_bx = bxplus1;
						new_by = byplus1;
						wybor_bialego_piona_1(new_bx, new_by);

						break;
					}
					else if (o == 2) {
						break;
					}
				}

			}
			break;
		case 2:
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
			else {
				cout << "Dokonałeś niepoprawnego wyboru. Spróbuj ponownie." << endl;
				wybor_bialego_piona_1(bx, by);
			}
			break;
		default: cout << "Nie wybrałeś żadnej opcji. Spróbuj ponownie" << endl;
			wybor_bialego_piona_1(bx, by);
		}


	}
	//dla wyboru pionka i ruchu bijącego w lewo
	else if ((plansza1[bxminus1][byminus1] == 'B') && ((plansza1[bx][byminus2] == 'C') && (plansza1[bxplus1][byminus3] == 'X'))) {

		cout << "Czy chcesz zbić pionka przeciwnika w lewą stronę? Wciśnij 1, jeśli tak, wciśnij 2, jeśli chcesz i możesz ruszyć się w prawo." << endl;
		int odpowiedz = 0;
		cin >> odpowiedz;
		switch (odpowiedz) {
		case 1:
			cout << "Następuje bicie piona czarnego przez piona białego." << endl;
			bxminus1 = bx - 1;
			byminus1 = by - 1;
			plansza1[bxminus1][byminus1] = 'X';
			int odp;
			cout << "Żeby zaktualizować planszę - wciśnij 1. ";
			cin >> odp;
			if (odp == 1) {
				system("cls");

				cout << "Trwa aktualizacja planszy: " << endl;
				liczba_czarnych_pionków = liczba_czarnych_pionków - 1;
				plansza1[bx][byminus2] = 'X';
				plansza1[bxplus1][byminus3] = 'B';

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
				if ((plansza1[bxplus2][byminus4] == 'C' && plansza1[bxplus3][byminus5] == 'X') || (plansza1[bxplus2][byminus2] == 'C' && plansza1[bxplus3][byminus1] == 'X')) {
					cout << "Czy chcesz bić dalej? Wciśnij 1, jeśli tak, wciśnij 2, jeśli nie." << endl;
					int o;
					cin >> o;

					if (o == 1) {
						cout << "Pamiętaj, żeby wybrać tego samego piona. " << endl;
						new_bx = bxplus1;
						new_by = byminus3;
						wybor_bialego_piona_1(new_bx, new_by);

						break;
					}
					else if (o == 2) {
						break;
					}
				}
			}
			break;
		case 2:
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
			else {
				cout << "Dokonałeś niepoprawnego wyboru. Spróbuj ponownie." << endl;
				wybor_bialego_piona_1(bx, by);
			}
			break;
		default: cout << "Nie wybrałeś żadnej opcji. Spróbuj ponownie" << endl;
			wybor_bialego_piona_1(bx, by);
		}
	}


	//dla zwykłego wyboru pionka
	else if ((plansza1[bxminus1][byminus1] == 'B') && ((plansza1[bx][byminus2] == 'X') || (plansza1[bx][by] == 'X'))) {

		if (by <= 8) {
			cout << "Wybrałeś odpowiedniego pionka." << endl;//ograniczenie drugiego wymiaru tablicy statycznej
		}
		else {
			cout << "Wybrałeś nieprawidłowego pionka. Spróbuj ponownie." << endl;
			wybor_bialego_piona_1(bx, by);
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


		//określenie zwykłego ruchu
		if ((x - bx == 1) && (plansza1[xminus1][yminus1] == 'X') && ((y - by == 1) || (y - by == (-1)))) {
			cout << "Wybrałeś dozwolony ruch. " << endl;
			bxminus1 = bx - 1;
			byminus1 = by - 1;
			plansza1[bxminus1][byminus1] = 'X';
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
			cout << "Wybrałeś niedozwolony ruch. Spróbuj ponownie." << endl;
			wybor_bialego_piona_1(bx, by);
		}
	}

	else {
		cout << "Wybrałeś nieodpowiedniego pionka. Spróbuj ponownie." << endl;
		wybor_bialego_piona_1(bx, by);
	}


}

void wybor_czarnego_piona_1(int bx, int by) {/*uzycie zaprzyjaznionej funkcji do klasy, funkcja kontroluje prawidlowy wybor piona,
nie mozna wybrac piona innego niz bialy i piona, ktory nie lezy na linii ofensywnej*/

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

	if ((plansza1[bxminus1][byminus1] == 'C') && (plansza1[bxminus2][byminus2] == 'B') && (plansza1[bxminus2][by] == 'B') && (plansza1[bxminus3][byplus1] == 'X') && (plansza1[bxminus3][byminus3] == 'X')) {
		cout << "Możesz zbić przeciwnika w obie strony. Zdecyduj, którą opcję wybierasz." << endl;
		int odpowiedz;
		cout << "Jeśli wybierasz bicie w prawą stronę wciśnij 1, jeśli wybierasz bicie w lewą stronę wciśnij 2. " << endl;
		cin >> odpowiedz;
		switch (odpowiedz) {
		case 1:
			cout << "Następuje bicie piona białego przez piona czarnego." << endl;
			bxminus1 = bx - 1;
			byminus1 = by - 1;
			plansza1[bxminus1][byminus1] = 'X';
			int odp;
			cout << "Żeby zaktualizować planszę - wciśnij 1. ";
			cin >> odp;
			if (odp == 1) {
				system("cls");

				cout << "Trwa aktualizacja planszy: " << endl;
				liczba_białych_pionków = liczba_białych_pionków - 1;
				plansza1[bxminus2][by] = 'X';
				plansza1[bxminus3][byplus1] = 'C';

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
				if ((plansza1[bxminus4][by] == 'B' && plansza1[bxminus5][byminus1] == 'X') || (plansza1[bxminus4][byplus2] == 'B' && plansza1[bxminus5][byplus3] == 'X')) {
					cout << "Czy chcesz bić dalej? Wciśnij 1, jeśli tak, wciśnij 2, jeśli nie." << endl;
					int o;
					cin >> o;

					if (o == 1) {
						cout << "Pamiętaj, żeby wybrać tego samego piona. " << endl;
						new_bx = bxminus3;
						new_by = byplus1;
						wybor_czarnego_piona_1(new_bx, new_by);

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
			bxminus1 = bx - 1;
			byminus1 = by - 1;
			plansza1[bxminus1][byminus1] = 'X';
			int odpow;
			cout << "Żeby zaktualizować planszę - wciśnij 1. ";
			cin >> odpow;
			if (odp == 1) {
				system("cls");
				liczba_białych_pionków = liczba_białych_pionków - 1;
				cout << "Trwa aktualizacja planszy: " << endl;

				plansza1[bxminus1][byminus1] = 'X';
				plansza1[bxminus2][byminus2] = 'X';
				plansza1[bxminus3][byminus3] = 'C';

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
				if ((plansza1[bxminus4][byminus4] == 'B' && plansza1[bxminus5][byminus5] == 'X') || (plansza1[bxminus4][byminus2] == 'B' && plansza1[bxminus5][byminus1] == 'X')) {
					cout << "Czy chcesz bić dalej? Wciśnij 1, jeśli tak, wciśnij 2, jeśli nie." << endl;
					int o;
					cin >> o;

					if (o == 1) {
						cout << "Pamiętaj, żeby wybrać tego samego piona. " << endl;
						new_bx = bxminus3;
						new_by = byminus3;
						wybor_czarnego_piona_1(new_bx, new_by);

						break;
					}
					else if (o == 2) {
						break;
					}
				}
			}
			break;
		default: cout << "Nie wybrałeś żadnej opcji. Spróbuj ponownie" << endl;
			wybor_czarnego_piona_1(bx, by);
		}

	}

	else if ((plansza1[bxminus1][byminus1] == 'C') && ((plansza1[bxminus2][by] == 'B') && (plansza1[bxminus3][byplus1] == 'X'))) {

		cout << "Czy chcesz zbić pionka przeciwnika w prawą stronę? Wciśnij 1, jeśli tak, wciśnij 2, chcesz i możesz ruszyć się w lewo." << endl;
		int odpowiedz = 0;
		cin >> odpowiedz;
		switch (odpowiedz) {
		case 1:
			cout << "Następuje bicie piona białego przez piona czarnego." << endl;
			bxminus1 = bx - 1;
			byminus1 = by - 1;
			plansza1[bxminus1][byminus1] = 'X';
			int odp;
			cout << "Żeby zaktualizować planszę - wciśnij 1. ";
			cin >> odp;
			if (odp == 1) {
				system("cls");
				liczba_białych_pionków = liczba_białych_pionków - 1;
				cout << "Trwa aktualizacja planszy: " << endl;

				plansza1[bxminus2][by] = 'X';
				plansza1[bxminus3][byplus1] = 'C';

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
				if ((plansza1[bxminus4][by] == 'B' && plansza1[bxminus5][byminus1] == 'X') || (plansza1[bxminus4][byplus2] == 'B' && plansza1[bxminus5][byplus3] == 'X')) {
					cout << "Czy chcesz bić dalej? Wciśnij 1, jeśli tak, wciśnij 2, jeśli nie." << endl;
					int o;
					cin >> o;

					if (o == 1) {
						cout << "Pamiętaj, żeby wybrać tego samego piona. " << endl;
						new_bx = bxminus3;
						new_by = byplus1;
						wybor_czarnego_piona_1(new_bx, new_by);

						break;
					}
					else if (o == 2) {
						break;
					}
				}

			}
			break;
		case 2:

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
			else {
				cout << "Dokonałeś niepoprawnego wyboru. Spróbuj ponownie." << endl;
				wybor_czarnego_piona_1(bx, by);
			}
			break;
		default: cout << "Nie wybrałeś żadnej opcji. Spróbuj ponownie" << endl;
			wybor_czarnego_piona_1(bx, by);
		}
	}
	else if ((plansza1[bxminus1][byminus1] == 'C') && ((plansza1[bxminus2][byminus2] == 'B') && (plansza1[bxminus3][byminus3] == 'X'))) {

		cout << "Czy chcesz zbić pionka przeciwnika w lewą stronę? Wciśnij 1, jeśli tak, wciśnij 2, jeśli chcesz i możesz ruszyć się w prawo." << endl;
		int odpowiedz = 0;
		cin >> odpowiedz;
		switch (odpowiedz) {
		case 1:
			cout << "Następuje bicie piona białego przez piona czarnego." << endl;
			bxminus1 = bx - 1;
			byminus1 = by - 1;
			plansza1[bxminus1][byminus1] = 'X';
			int odp;
			cout << "Żeby zaktualizować planszę - wciśnij 1. ";
			cin >> odp;
			if (odp == 1) {
				system("cls");

				cout << "Trwa aktualizacja planszy: " << endl;
				liczba_białych_pionków = liczba_białych_pionków - 1;
				plansza1[bxminus1][byminus1] = 'X';
				plansza1[bxminus2][byminus2] = 'X';
				plansza1[bxminus3][byminus3] = 'C';

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
				if ((plansza1[bxminus4][byminus4] == 'B' && plansza1[bxminus5][byminus5] == 'X') || (plansza1[bxminus4][byminus2] == 'B' && plansza1[bxminus5][byminus1] == 'X')) {
					cout << "Czy chcesz bić dalej? Wciśnij 1, jeśli tak, wciśnij 2, jeśli nie." << endl;
					int o;
					cin >> o;

					if (o == 1) {
						cout << "Pamiętaj, żeby wybrać tego samego piona. " << endl;
						new_bx = bxminus3;
						new_by = byminus3;
						wybor_czarnego_piona_1(new_bx, new_by);

						break;
					}
					else if (o == 2) {
						break;
					}
				}
			}
			break;
		case 2:

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
			else {
				cout << "Dokonałeś niepoprawnego wyboru. Spróbuj ponownie." << endl;
				wybor_czarnego_piona_1(bx, by);
			}

			break;
		default: cout << "Nie wybrałeś żadnej opcji. Spróbuj ponownie" << endl;
			wybor_czarnego_piona_1(bx, by);
		}
	}
	else if ((plansza1[bxminus1][byminus1] == 'C') && ((plansza1[bxminus2][byminus2] == 'X') || (plansza1[bxminus2][by] == 'X'))) {
		if (by <= 8) {
			cout << "Wybrałeś odpowiedniego pionka." << endl;
		}
		else {
			cout << "Wybrałeś nieprawidłowego pionka. Spróbuj ponownie." << endl;
			wybor_czarnego_piona_1(bx, by);
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



		if ((bx - x == 1) && (plansza1[xminus1][yminus1] == 'X') && ((y - by == 1) || (y - by == (-1)))) {
			cout << "Wybrałeś dozwolony ruch. " << endl;
			bxminus1 = bx - 1;
			byminus1 = by - 1;
			plansza1[bxminus1][byminus1] = 'X';
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
			cout << "Wybrałeś niedozwolony ruch. Spróbuj ponownie." << endl;
			wybor_czarnego_piona_1(bx, by);
		}
	}

	else {
		cout << "Wybrałeś nieodpowiedniego pionka. Spróbuj ponownie." << endl;
		wybor_czarnego_piona_1(bx, by);
	}


}


void wybor_bialego_piona_2(int bx, int by) {/*uzycie zaprzyjaznionej funkcji do klasy, funkcja kontroluje prawidlowy wybor piona,
nie mozna wybrac piona innego niz bialy i piona, ktory nie lezy na linii ofensywnej*/

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

	if ((plansza2[bxminus1][byminus1] == 'B') && (plansza2[bx][by] == 'C') && (plansza2[bx][by - 2] == 'C') && (plansza2[bxplus1][byplus1] == 'X') && (plansza2[bxplus1][byminus3] == 'X')) {
		cout << "Możesz zbić przeciwnika w obie strony. Zdecyduj, którą opcję wybierasz." << endl;
		int odpowiedz;
		cout << "Jeśli wybierasz bicie w prawą stronę wciśnij 1, jeśli wybierasz bicie w lewą stronę wciśnij 2. " << endl;
		cin >> odpowiedz;
		switch (odpowiedz) {
		case 1:
			cout << "Następuje bicie piona czarnego przez piona białego." << endl;
			bxminus1 = bx - 1;
			byminus1 = by - 1;
			plansza2[bxminus1][byminus1] = 'X';
			int odp;
			cout << "Żeby zaktualizować planszę - wciśnij 1. ";
			cin >> odp;
			if (odp == 1) {
				system("cls");

				cout << "Trwa aktualizacja planszy: " << endl;
				liczba_czarnych_pionków = liczba_czarnych_pionków - 1;
				plansza2[bx][by] = 'X';
				plansza2[bxplus1][byplus1] = 'B';

				for (int i = 0; i < 1; i++) {
					for (int j = 0; j < kolumny + 1; j++) {
						cout << j << " ";
					}
					cout << endl;
				}
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
				if ((plansza2[bxplus2][by] == 'C' && plansza2[bxplus3][byminus1] == 'X') || (plansza2[bxplus2][byplus2] == 'C' && plansza2[bxplus3][byplus3] == 'X')) {
					cout << "Czy chcesz bić dalej? Wciśnij 1, jeśli tak, wciśnij 2, jeśli nie." << endl;
					int o;
					cin >> o;

					if (o == 1) {
						cout << "Pamiętaj, żeby wybrać tego samego piona. " << endl;
						new_bx = bxplus1;
						new_by = byplus1;
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
			bxminus1 = bx - 1;
			byminus1 = by - 1;
			plansza2[bxminus1][byminus1] = 'X';
			int odpow;
			cout << "Żeby zaktualizować planszę - wciśnij 1. ";
			cin >> odpow;
			if (odpow == 1) {
				system("cls");

				cout << "Trwa aktualizacja planszy: " << endl;
				liczba_czarnych_pionków = liczba_czarnych_pionków - 1;
				plansza2[bx][byminus2] = 'X';
				plansza2[bxplus1][byminus3] = 'B';

				for (int i = 0; i < 1; i++) {
					for (int j = 0; j < kolumny + 1; j++) {
						cout << j << " ";
					}
					cout << endl;
				}
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
				if ((plansza2[bxplus2][byminus4] == 'C' && plansza2[bxplus3][byminus5] == 'X') || (plansza2[bxplus2][byminus2] == 'C' && plansza2[bxplus3][byminus1] == 'X')) {
					cout << "Czy chcesz bić dalej? Wciśnij 1, jeśli tak, wciśnij 2, jeśli nie." << endl;
					int o;
					cin >> o;

					if (o == 1) {
						cout << "Pamiętaj, żeby wybrać tego samego piona. " << endl;
						new_bx = bxplus1;
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

	else if ((plansza2[bxminus1][byminus1] == 'B') && ((plansza2[bx][by] == 'C') && (plansza2[bxplus1][byplus1] == 'X'))) {

		cout << "Czy chcesz zbić pionka przeciwnika w prawą stronę? Wciśnij 1, jeśli tak, wciśnij 2, jeśli chcesz i możesz ruszyć się w lewo." << endl;
		int odpowiedz = 0;
		cin >> odpowiedz;
		switch (odpowiedz) {
		case 1:
			cout << "Następuje bicie piona czarnego przez piona białego." << endl;
			bxminus1 = bx - 1;
			byminus1 = by - 1;
			plansza2[bxminus1][byminus1] = 'X';
			int odp;
			cout << "Żeby zaktualizować planszę - wciśnij 1. ";
			cin >> odp;
			if (odp == 1) {
				system("cls");
				liczba_czarnych_pionków = liczba_czarnych_pionków - 1;
				cout << "Trwa aktualizacja planszy: " << endl;

				plansza2[bx][by] = 'X';
				plansza2[bxplus1][byplus1] = 'B';

				for (int i = 0; i < 1; i++) {
					for (int j = 0; j < kolumny + 1; j++) {
						cout << j << " ";
					}
					cout << endl;
				}
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
				if ((plansza2[bxplus2][by] == 'C' && plansza2[bxplus3][byminus1] == 'X') || (plansza2[bxplus2][byplus2] == 'C' && plansza2[bxplus3][byplus3] == 'X')) {
					cout << "Czy chcesz bić dalej? Wciśnij 1, jeśli tak, wciśnij 2, jeśli nie." << endl;
					int o;
					cin >> o;

					if (o == 1) {
						cout << "Pamiętaj, żeby wybrać tego samego piona. " << endl;
						new_bx = bxplus1;
						new_by = byplus1;
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

			if ((plansza2[bxminus1][byminus1] == 'B') && (plansza2[bx][byminus2] == 'X')) {

				plansza2[bxminus1][byminus1] = 'X';
				plansza2[bx][byminus2] = 'B';
				int odp;
				cout << "Żeby zaktualizować planszę - wciśnij 1. ";
				cin >> odp;
				if (odp == 1) {
					system("cls");

					cout << "Trwa aktualizacja planszy: " << endl;
					for (int i = 0; i < 1; i++) {
						for (int j = 0; j < kolumny + 1; j++) {
							cout << j << " ";
						}
						cout << endl;
					}
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
				cout << "Dokonałeś niepoprawnego wyboru. Spróbuj ponownie." << endl;
				wybor_bialego_piona_2(bx, by);
			}
			break;
		default: cout << "Nie wybrałeś żadnej opcji. Spróbuj ponownie" << endl;
			wybor_bialego_piona_2(bx, by);
		}
	}
	else if ((plansza2[bxminus1][byminus1] == 'B') && ((plansza2[bx][byminus2] == 'C') && (plansza2[bxplus1][byminus3] == 'X'))) {

		cout << "Czy chcesz zbić pionka przeciwnika w lewą stronę? Wciśnij 1, jeśli tak, wciśnij 2, jeśli chcesz i możesz ruszyć się w lewo." << endl;
		int odpowiedz = 0;
		cin >> odpowiedz;
		switch (odpowiedz) {
		case 1:
			cout << "Następuje bicie piona czarnego przez piona białego." << endl;
			bxminus1 = bx - 1;
			byminus1 = by - 1;
			plansza2[bxminus1][byminus1] = 'X';
			int odp;
			cout << "Żeby zaktualizować planszę - wciśnij 1. ";
			cin >> odp;
			if (odp == 1) {
				system("cls");

				cout << "Trwa aktualizacja planszy: " << endl;
				liczba_czarnych_pionków = liczba_czarnych_pionków - 1;
				plansza2[bx][byminus2] = 'X';
				plansza2[bxplus1][byminus3] = 'B';
				for (int i = 0; i < 1; i++) {
					for (int j = 0; j < kolumny + 1; j++) {
						cout << j << " ";
					}
					cout << endl;
				}
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
				if ((plansza2[bxplus2][byminus4] == 'C' && plansza2[bxplus3][byminus5] == 'X') || (plansza2[bxplus2][byminus2] == 'C' && plansza2[bxplus3][byminus1] == 'X')) {
					cout << "Czy chcesz bić dalej? Wciśnij 1, jeśli tak, wciśnij 2, jeśli nie." << endl;
					int o;
					cin >> o;

					if (o == 1) {
						cout << "Pamiętaj, żeby wybrać tego samego piona. " << endl;
						new_bx = bxplus1;
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
		case 2:

			if ((plansza2[bxminus1][byminus1] == 'B') && (plansza2[bx][by] == 'X')) {

				plansza2[bxminus1][byminus1] = 'X';
				plansza2[bx][by] = 'B';
				int odp;
				cout << "Żeby zaktualizować planszę - wciśnij 1. ";
				cin >> odp;
				if (odp == 1) {
					system("cls");
					cout << "Trwa aktualizacja planszy: " << endl;
					for (int i = 0; i < 1; i++) {
						for (int j = 0; j < kolumny + 1; j++) {
							cout << j << " ";
						}
						cout << endl;
					}
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
				cout << "Dokonałeś niepoprawnego wyboru. Spróbuj ponownie." << endl;
				wybor_bialego_piona_2(bx, by);
			}
			break;
		default: cout << "Nie wybrałeś żadnej opcji. Spróbuj ponownie" << endl;
			wybor_bialego_piona_1(bx, by);
		}
	}
	else if ((plansza2[bxminus1][byminus1] == 'B') && ((plansza2[bx][byminus2] == 'X') || (plansza1[bx][by] == 'X'))) {

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



		if ((x - bx == 1) && (plansza2[xminus1][yminus1] == 'X') && ((y - by == 1) || (y - by == (-1)))) {
			cout << "Wybrałeś dozwolony ruch. " << endl;
			bxminus1 = bx - 1;
			byminus1 = by - 1;
			plansza2[bxminus1][byminus1] = 'X';
			int odp;
			cout << "Żeby zaktualizować planszę - wciśnij 1. ";
			cin >> odp;
			if (odp == 1) {
				system("cls");

				cout << "Trwa aktualizacja planszy: " << endl;

				w1 = x - 1;
				k1 = y - 1;
				plansza2[w1][k1] = 'B';

				for (int i = 0; i < 1; i++) {
					for (int j = 0; j < kolumny + 1; j++) {
						cout << j << " ";
					}
					cout << endl;
				}
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
			cout << "Wybrałeś niedozwolony ruch. Spróbuj ponownie." << endl;
			wybor_bialego_piona_2(bx, by);
		}
	}



	else {
		cout << "Wybrałeś nieodpowiedniego pionka. Spróbuj ponownie." << endl;
		wybor_bialego_piona_2(bx, by);
	}


}

void wybor_czarnego_piona_2(int bx, int by) {/*uzycie zaprzyjaznionej funkcji do klasy, funkcja kontroluje prawidlowy wybor piona,
nie mozna wybrac piona innego niz bialy i piona, ktory nie lezy na linii ofensywnej*/

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

	if ((plansza2[bxminus1][byminus1] == 'C') && (plansza2[bxminus2][byminus2] == 'B') && (plansza2[bxminus2][by] == 'B') && (plansza2[bxminus3][byplus1] == 'X') && (plansza2[bxminus3][byminus3] == 'X')) {
		cout << "Możesz zbić przeciwnika w obie strony. Zdecyduj, którą opcję wybierasz." << endl;
		int odpowiedz;
		cout << "Jeśli wybierasz bicie w prawą stronę wciśnij 1, jeśli wybierasz bicie w lewą stronę wciśnij 2. " << endl;
		cin >> odpowiedz;
		switch (odpowiedz) {
		case 1:
			bxminus1 = bx - 1;
			byminus1 = by - 1;
			plansza2[bxminus1][byminus1] = 'X';
			int odp;
			cout << "Żeby zaktualizować planszę - wciśnij 1. ";
			cin >> odp;
			if (odp == 1) {
				system("cls");

				cout << "Trwa aktualizacja planszy: " << endl;

				plansza2[bxminus2][by] = 'X';
				plansza2[bxminus3][byplus1] = 'C';

				for (int i = 0; i < 1; i++) {
					for (int j = 0; j < kolumny + 1; j++) {
						cout << j << " ";
					}
					cout << endl;
				}
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
				if ((plansza2[bxminus4][by] == 'B' && plansza2[bxminus5][byminus1] == 'X') || (plansza2[bxminus4][byplus2] == 'B' && plansza2[bxminus5][byplus3] == 'X')) {
					cout << "Czy chcesz bić dalej? Wciśnij 1, jeśli tak, wciśnij 2, jeśli nie." << endl;
					int o;
					cin >> o;

					if (o == 1) {
						cout << "Pamiętaj, żeby wybrać tego samego piona. " << endl;
						new_bx = bxminus3;
						new_by = byplus1;
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
			bxminus1 = bx - 1;
			byminus1 = by - 1;
			plansza2[bxminus1][byminus1] = 'X';
			int odpow;
			cout << "Żeby zaktualizować planszę - wciśnij 1. ";
			cin >> odpow;
			if (odp == 1) {
				system("cls");

				cout << "Trwa aktualizacja planszy: " << endl;
				liczba_białych_pionków = liczba_białych_pionków - 1;
				plansza2[bxminus1][byminus1] = 'X';
				plansza2[bxminus2][byminus2] = 'X';
				plansza2[bxminus3][byminus3] = 'C';

				for (int i = 0; i < 1; i++) {
					for (int j = 0; j < kolumny + 1; j++) {
						cout << j << " ";
					}
					cout << endl;
				}
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
				if ((plansza2[bxminus4][byminus4] == 'B' && plansza2[bxminus5][byminus5] == 'X') || (plansza2[bxminus4][byminus2] == 'B' && plansza2[bxminus5][byminus1] == 'X')) {
					cout << "Czy chcesz bić dalej? Wciśnij 1, jeśli tak, wciśnij 2, jeśli nie." << endl;
					int o;
					cin >> o;

					if (o == 1) {
						cout << "Pamiętaj, żeby wybrać tego samego piona. " << endl;
						new_bx = bxminus3;
						new_by = byminus3;
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
	else if ((plansza2[bxminus1][byminus1] == 'C') && ((plansza2[bxminus2][by] == 'B') && (plansza2[bxminus3][byplus1] == 'X'))) {

		cout << "Czy chcesz zbić pionka przeciwnika w prawą stronę? Wciśnij 1, jeśli tak, wciśnij 2, jeśli nie." << endl;
		int odpowiedz = 0;
		cin >> odpowiedz;
		switch (odpowiedz) {
		case 1:
			cout << "Następuje bicie piona białego przez piona czarnego." << endl;
			bxminus1 = bx - 1;
			byminus1 = by - 1;
			plansza2[bxminus1][byminus1] = 'X';
			int odp;
			cout << "Żeby zaktualizować planszę - wciśnij 1. ";
			cin >> odp;
			if (odp == 1) {
				system("cls");

				cout << "Trwa aktualizacja planszy: " << endl;
				liczba_białych_pionków = liczba_białych_pionków - 1;
				plansza2[bxminus2][by] = 'X';
				plansza2[bxminus3][byplus1] = 'C';

				for (int i = 0; i < 1; i++) {
					for (int j = 0; j < kolumny + 1; j++) {
						cout << j << " ";
					}
					cout << endl;
				}
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
				if ((plansza2[bxminus4][by] == 'B' && plansza2[bxminus5][byminus1] == 'X') || (plansza2[bxminus4][byplus2] == 'B' && plansza2[bxminus5][byplus3] == 'X')) {
					cout << "Czy chcesz bić dalej? Wciśnij 1, jeśli tak, wciśnij 2, jeśli nie." << endl;
					int o;
					cin >> o;

					if (o == 1) {
						cout << "Pamiętaj, żeby wybrać tego samego piona. " << endl;
						new_bx = bxminus3;
						new_by = byplus1;
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

			if ((plansza2[bxminus1][byminus1] == 'C') && (plansza2[bxminus2][byminus2] == 'X')) {

				plansza2[bxminus1][byminus1] = 'X';
				plansza2[bxminus2][byminus2] = 'C';
				int odp;
				cout << "Żeby zaktualizować planszę - wciśnij 1. ";
				cin >> odp;
				if (odp == 1) {
					system("cls");
					cout << "Trwa aktualizacja planszy." << endl;
					for (int i = 0; i < 1; i++) {
						for (int j = 0; j < kolumny + 1; j++) {
							cout << j << " ";
						}
						cout << endl;
					}
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
				cout << "Dokonałeś niepoprawnego wyboru. Spróbuj ponownie." << endl;
				wybor_czarnego_piona_2(bx, by);
			}
			break;
		default: cout << "Nie wybrałeś żadnej opcji. Spróbuj ponownie" << endl;
			wybor_czarnego_piona_2(bx, by);

		}
	}
	else if ((plansza2[bxminus1][byminus1] == 'C') && ((plansza2[bxminus2][byminus2] == 'B') && (plansza2[bxminus3][byminus3] == 'X'))) {

		cout << "Czy chcesz zbić pionka przeciwnika w lewą stronę? Wciśnij 1, jeśli tak, wciśnij 2, jeśli nie." << endl;
		int odpowiedz = 0;
		cin >> odpowiedz;
		switch (odpowiedz) {
		case 1:
			cout << "Następuje bicie piona białego przez piona czarnego." << endl;
			bxminus1 = bx - 1;
			byminus1 = by - 1;
			plansza2[bxminus1][byminus1] = 'X';
			int odp;
			cout << "Żeby zaktualizować planszę - wciśnij 1. ";
			cin >> odp;
			if (odp == 1) {
				system("cls");

				cout << "Trwa aktualizacja planszy: " << endl;
				liczba_białych_pionków = liczba_białych_pionków - 1;
				plansza2[bxminus1][byminus1] = 'X';
				plansza2[bxminus2][byminus2] = 'X';
				plansza2[bxminus3][byminus3] = 'C';

				for (int i = 0; i < 1; i++) {
					for (int j = 0; j < kolumny + 1; j++) {
						cout << j << " ";
					}
					cout << endl;
				}
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
				if ((plansza2[bxminus4][byminus4] == 'B' && plansza2[bxminus5][byminus5] == 'X') || (plansza2[bxminus4][byminus2] == 'B' && plansza2[bxminus5][byminus1] == 'X')) {
					cout << "Czy chcesz bić dalej? Wciśnij 1, jeśli tak, wciśnij 2, jeśli nie." << endl;
					int o;
					cin >> o;

					if (o == 1) {
						cout << "Pamiętaj, żeby wybrać tego samego piona. " << endl;
						new_bx = bxminus3;
						new_by = byminus3;
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

			if ((plansza2[bxminus1][byminus1] == 'C') && (plansza2[bxminus2][by] == 'X')) {

				plansza2[bxminus1][byminus1] = 'X';
				plansza2[bxminus2][by] = 'C';
				int odp;
				cout << "Żeby zaktualizować planszę - wciśnij 1. ";
				cin >> odp;
				if (odp == 1) {
					system("cls");

					cout << "Trwa aktualizacja planszy: " << endl;
					for (int i = 0; i < 1; i++) {
						for (int j = 0; j < kolumny + 1; j++) {
							cout << j << " ";
						}
						cout << endl;
					}
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
				cout << "Dokonałeś niepoprawnego wyboru. Spróbuj ponownie." << endl;
				wybor_czarnego_piona_1(bx, by);
			}
			break;
		default: cout << "Nie wybrałeś żadnej opcji. Spróbuj ponownie" << endl;
			wybor_czarnego_piona_2(bx, by);
		}
	}
	else if ((plansza2[bxminus1][byminus1] == 'C') && ((plansza2[bxminus2][byminus2] == 'X') || (plansza2[bxminus2][by] == 'X'))) {

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



		if ((bx - x == 1) && (plansza2[xminus1][yminus1] == 'X') && ((y - by == 1) || (y - by == (-1)))) {
			cout << "Wybrałeś dozwolony ruch. " << endl;
			bxminus1 = bx - 1;
			byminus1 = by - 1;
			plansza2[bxminus1][byminus1] = 'X';
			int odp;
			cout << "Żeby zaktualizować planszę - wciśnij 1. ";
			cin >> odp;
			if (odp == 1) {
				system("cls");

				cout << "Trwa aktualizacja planszy: " << endl;

				w1 = x - 1;
				k1 = y - 1;
				plansza2[w1][k1] = 'C';

				for (int i = 0; i < 1; i++) {
					for (int j = 0; j < kolumny + 1; j++) {
						cout << j << " ";
					}
					cout << endl;
				}
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
			cout << "Wybrałeś niedozwolony ruch. Spróbuj ponownie." << endl;
			wybor_czarnego_piona_2(bx, by);
		}
	}

	else {
		cout << "Wybrałeś nieodpowiedniego pionka. Spróbuj ponownie." << endl;
		wybor_czarnego_piona_2(bx, by);
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
			cout << "RUCH BIAŁEGO GRACZA." << endl;
			wybor_bialego_piona_1(bx, by);
			cout << "Liczba białych pionków to: " << liczba_białych_pionków << endl;
			cout << "Liczba czarnych pionków to: " << liczba_czarnych_pionków << endl;

			if (liczba_czarnych_pionków == 0) {
				cout << "Wygrał biały gracz. Gratulacje!" << endl;
				int zakonczenie;
				cout << "Wciśnij 1, żeby zakończyć." << endl;
				cin >> zakonczenie;
				if (zakonczenie == 1) {
					system("cls");
				}

			}
			cout << "RUCH CZARNEGO GRACZA." << endl;
			wybor_czarnego_piona_1(bx, by);
			cout << "Liczba białych pionków to: " << liczba_białych_pionków << endl;
			cout << "Liczba czarnych pionków to: " << liczba_czarnych_pionków << endl;

			if (liczba_białych_pionków == 0) {
				cout << "Wygrał czarny gracz. Gratulacje!" << endl;
				int zakonczenie;
				cout << "Wciśnij 1, żeby zakończyć." << endl;
				cin >> zakonczenie;
				if (zakonczenie == 1) {
					system("cls");
				}
			}
		} while ((liczba_białych_pionków > 0) || (liczba_czarnych_pionków > 0));//określenie warunku końcowego gry




		break;

	case 2:
		plansza_2.okresl_plansze_2();
		plansza_2.rysuj_plansze_2();
		cout << "Gotowy? Gramy! Zaczyna biały gracz. " << endl;
		do {
			cout << "RUCH BIAŁEGO GRACZA." << endl;
			wybor_bialego_piona_2(bx, by);
			cout << "Liczba białych pionków to: " << liczba_białych_pionków << endl;
			cout << "Liczba czarnych pionków to: " << liczba_czarnych_pionków << endl;
			if (liczba_czarnych_pionków == 0) {
				cout << "Wygrał biały gracz. Gratulacje!" << endl;
				int zakonczenie;
				cout << "Wciśnij 1, żeby zakończyć." << endl;
				cin >> zakonczenie;
				if (zakonczenie == 1) {
					system("cls");
				}

			}
			cout << "RUCH CZARNEGO GRACZA." << endl;
			wybor_czarnego_piona_2(bx, by);
			cout << "Liczba białych pionków to: " << liczba_białych_pionków << endl;
			cout << "Liczba czarnych pionków to: " << liczba_czarnych_pionków << endl;
			if (liczba_białych_pionków == 0) {
				cout << "Wygrał czarny gracz. Gratulacje!" << endl;
				int zakonczenie;
				cout << "Wciśnij 1, żeby zakończyć." << endl;
				cin >> zakonczenie;
				if (zakonczenie == 1) {
					system("cls");
				}
			}

		} while ((liczba_białych_pionków > 0) || (liczba_czarnych_pionków > 0));//określenie warunku końcowego gry


		if (liczba_czarnych_pionków == 0) {
			cout << "Wygrał biały gracz. Gratulacje!" << endl;
		}
		if (liczba_białych_pionków == 0) {
			cout << "Wygrał czarny gracz. Gratulacje!" << endl;
		}


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