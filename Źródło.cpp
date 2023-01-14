#include<iostream>
#include <conio.h>

#include <windows.h>

void sleep(unsigned milliseconds)
{
	Sleep(milliseconds);
}

using namespace std;

void intro();
void boardOut(char tab[8][8]);
void gameplay(char tab[8][8], int & counter, int& draw2);
int* coordinatesConverter(string word);
bool coordinatesChecker(int coordinates[2], char tab[8][8], char Player);
void moves(int coordinates[2], char tab[8][8], char Player, int & licznik);
bool win(char tab[8][8], int & draw1, int & licznik2);

int main() {
	int RoundCounter, draw, Rematch;
	//intro();
	do
	{
		char board[8][8] = { {' ','O',' ','O',' ','O', ' ', 'O'},
						{'O',' ','O',' ','O',' ', 'O', ' '},
						{' ','O',' ','O',' ','O', ' ', 'O'},
						{' ',' ',' ',' ',' ',' ', ' ', ' '},
						{' ',' ',' ',' ',' ',' ', ' ', ' '},
						{'X',' ','X',' ','X',' ', 'X', ' '},
						{' ','X',' ','X',' ','X', ' ', 'X'},
						{'X',' ','X',' ','X',' ', 'X', ' '} };
		RoundCounter = 0;
		draw = 0;
		while (win(board, draw, RoundCounter)) {
			gameplay(board, RoundCounter, draw);
			RoundCounter++;
			system("cls");
		}
		cout << "Czy chcesz powtorzyc rozgrywke?\n0 - Nie\n1 - Tak\n";
		cin >> Rematch;
		system("cls");
	} while (Rematch != 0);

	return 0;
}
void intro() {
	cout << "Witaj w grze w warcaby!" << endl;
	sleep(1200);
	system("cls");
	cout << "POWODZENIA!!";
	sleep(1200);
	system("cls");
}
void boardOut(char tab[8][8]) {
	string coordinates;
	char x = 'A';
	int y = 1;
	cout << "    ";
	for (int i = 0; i < 8; i++)
	{
		cout << x << "   ";
		x += 1;
	}cout << endl << "  +---+---+---+---+---+---+---+---+" << endl;
	for (int i = 0; i < 8; i++) {
		cout << y;
		for (int j = 0; j < 8; j++) {
			cout << " " << "| " << tab[i][j];
			sleep(1);
		}
		y += 1;

		cout << " |" << endl;
		cout << "  +---+---+---+---+---+---+---+---+";
		cout << endl;


	}
}
void gameplay(char tab[8][8], int & counter, int& draw2) {
	char Player;
	if (counter % 2 == 0) {
		Player = 'X';
		cout << "\t    Tura gracza X\n" << endl;
	}
	else {
		Player = 'O';
		cout << "\t    Tura gracza O\n" << endl;
	}
	boardOut(tab);
	string coordinates;
	cout << "Podaj koordynaty pionka, ktorym chcesz sie poruszyc lub zaproponuj remis wpisujac \"remis\": ";
	cin >> coordinates;
	if (coordinates == "remis") {
		draw2++;
		return;
	}
	while (!coordinatesChecker(coordinatesConverter(coordinates), tab, Player)) {
		cout << "Podaj ponownie koordynaty: ";
		cin >> coordinates;
	}

	moves(coordinatesConverter(coordinates), tab, Player, counter);
	win(tab,draw2,counter);
}
int* coordinatesConverter(string coordinates) {
	int tab[2];
	int letter = -1, number = 0;
	if (coordinates[0] >= 65 && coordinates[0] <= 72) letter = coordinates[0] - 65;
	else if (coordinates[0] >= 97 && coordinates[0] <= 104) letter = coordinates[0] - 97;
	else cout << "Nieprawidlowe koordynaty\n";
	if (coordinates[1] >= 49 && coordinates[1] <= 56) number = coordinates[1] - 49;
	else if (letter != -1 && (coordinates[1] < 49 || coordinates[1] > 56)) cout << "Nieprawidlowe koordynaty\n";
	//cout << endl << number << "\t" << letter;
	tab[0] = letter;
	tab[1] = number;
	return tab;
}
bool coordinatesChecker(int coordinates[2], char tab[8][8], char Player) {
	int x = coordinates[0], y = coordinates[1];
	bool flag = false;
	if (tab[y][x] != Player) {
		if (Player == 'X') {
			if (tab[y][x] == '#') {
				/*if (y - 1 >= 0 && x + 1 < 8) { //w prawo przod
					if (tab[y - 1][x + 1] == ' ') {
						flag = true;
					}
					else if (tab[y - 1][x + 1] == 'O') {
						if (tab[y - 2][x + 2] == ' ' && (y - 2 >= 0 && x + 2 < 8)) {
							flag = true;
						}

					}
				}
				if (y - 1 >= 0 && x - 1 >= 0) { // w lewo przod
					if (tab[y - 1][x - 1] == ' ') {
						flag = true;
					}
					else if (tab[y - 1][x - 1] == 'O') {
						if (tab[y - 2][x - 2] == ' ' && (y - 2 >= 0 && x - 2 >= 0)) {
							flag = true;
						}

					}
				}
				if (flag == false) cout << "Brak mozliwosci ruchu tym pionkiem.\n";*/
				return true;
			}
		}
		else if (Player == 'O') {
			if (tab[y][x] == '@') return true;
		}
		else {
			cout << "Na tym polu nie ma twojego pionka.\n";
			return false;
		}
	}
	if (Player == 'X') {
		if (y - 1 >= 0 && x + 1 < 8) { //w prawo
			if (tab[y - 1][x + 1] == ' ') {
				flag = true;
			}
			else if (tab[y - 1][x + 1] == 'O' || tab[y - 1][x + 1] == '@') {
				if (tab[y - 2][x + 2] == ' ' && (y - 2 >= 0 && x + 2 < 8)) {
					flag = true;
				}

			}
		}
		if (y - 1 >= 0 && x - 1 >= 0) { // w lewo
			if (tab[y - 1][x - 1] == ' ') {
				flag = true;
			}
			else if (tab[y - 1][x - 1] == 'O' || tab[y - 1][x - 1] == '@') {
				if (tab[y - 2][x - 2] == ' ' && (y - 2 >= 0 && x - 2 >= 0)) {
					flag = true;
				}

			}
		}
		if (flag == false) cout << "Brak mozliwosci ruchu tym pionkiem.\n";
	}

	else {
		if (y + 1 < 8 && x + 1 < 8) { // w prawo
			if (tab[y + 1][x + 1] == ' ') {
				flag = true;
			}
			else if (tab[y + 1][x + 1] == 'X' || tab[y + 1][x + 1] == '#') {
				if (tab[y + 2][x + 2] == ' ' && (y + 2 < 8 && x + 2 < 8)) {
					flag = true;
				}

			}
		}
		if (y + 1 < 8 && x - 1 >= 0) { // w lewo
			if (tab[y + 1][x - 1] == ' ') {
				flag = true;
			}
			else if (tab[y + 1][x - 1] == 'X' || tab[y + 1][x - 1] == '#') {
				if (tab[y + 2][x - 2] == ' ' && (y + 2 < 8 && x - 2 >= 0)) {
					flag = true;
				}

			}
		}
		if (flag == false) cout << "Brak mozliwosci ruchu tym pionkiem.\n";
	}
	return flag;

}
void moves(int coordinates[2], char tab[8][8], char Player, int & licznik) {

	int y = coordinates[1], x = coordinates[0], counter = 1, counterL = 0, counterP = 0, biciePX = 0, bicieLX = 0, biciePO = 0, bicieLO = 0;
	bool flag = false;
	int moveX = -1, moveY = -1, moveX2 = -1, moveY2 = -1;
	cout << "Wybierz opcje ruchu: \n";
	if (Player == 'X') {
		if (y - 1 >= 0 && x + 1 < 8) {
			char x1, y1;
			if (tab[y - 1][x + 1] == ' ') {
				x1 = x + 66;
				y1 = y + 48;
				cout << endl << counter << ". mozliwosc ruchu w prawo na pole: " << x1 << y1 << endl;
				moveX = x + 1;
				moveY = y - 1;
				counter++;
				counterP++;
			}
			else if (tab[y - 1][x + 1] == 'O') {
				if (tab[y - 2][x + 2] == ' ' && (y - 2 >= 0 && x + 2 < 8)) {
					x1 = x + 67;
					y1 = y + 47;
					cout << counter << ". mozliwosc ruchu w prawo na pole: " << x1 << y1 << endl;
					moveX = x + 2;
					moveY = y - 2;
					counter++;
					counterP++;
					biciePX++;
				}
			}
		}
		if (y - 1 >= 0 && x - 1 >= 0) {
			char x2, y2;
			if (tab[y - 1][x - 1] == ' ') {
				x2 = x + 64;
				y2 = y + 48;
				cout << counter << ". mozliwosc ruchu w lewo na pole: " << x2 << y2 << endl;
				moveX2 = x - 1;
				moveY2 = y - 1;
				counter++;
				counterL++;
			}
			else if (tab[y - 1][x - 1] == 'O') {
				if (tab[y - 2][x - 2] == ' ' && (y - 2 >= 0 && x - 2 >= 0)) {
					x2 = x + 63;
					y2 = y + 47;
					cout << counter << ". mozliwosc ruchu w lewo na pole: " << x2 << y2 << endl;
					moveX2 = x - 2;
					moveY2 = y - 2;
					counter++;
					counterL++;
					bicieLX++;
				}
			}
		}


	}

	else {
		if (y + 1 < 8 && x + 1 < 8) {
			char x1, y1;
			if (tab[y + 1][x + 1] == ' ') {
				x1 = x + 66;
				y1 = y + 50;
				cout << endl << counter << ". Mozliwosc ruchu w prawo na pole: " << x1 << y1 << endl;
				moveX = x + 1;
				moveY = y + 1;
				counter++;
				counterP++;
			}
			else if (tab[y + 1][x + 1] == 'X') {
				if (tab[y + 2][x + 2] == ' ' && (y + 2 < 8 && x + 2 < 8)) {
					x1 = x + 67;
					y1 = y + 51;
					cout << counter << ". mozliwosc ruchu w prawo na pole: " << x1 << y1 << endl;
					moveX = x + 2;
					moveY = y + 2;
					counter++;
					counterP++;
					biciePO++;
				}
			}
		}
		if (y + 1 < 8 && x - 1 >= 0) {
			char x2, y2;
			if (tab[y + 1][x - 1] == ' ') {
				x2 = x + 64;
				y2 = y + 50;
				cout << counter << ". Mozliwosc ruchu w lewo na pole: " << x2 << y2 << endl;
				moveX2 = x - 1;
				moveY2 = y + 1;
				counter++;
				counterL++;
			}
			else if (tab[y + 1][x - 1] == 'X') {
				if (tab[y + 2][x - 2] == ' ' && (y + 2 < 8 && x - 2 >= 0)) {
					x2 = x + 63;
					y2 = y + 51;
					cout << counter << ". mozliwosc ruchu w lewo na pole: " << x2 << y2 << endl;
					moveX2 = x - 2;
					moveY2 = y + 2;
					counter++;
					counterL++;
					bicieLO++;
				}
			}
		}

	}
	cout << counter << ". Wybierz inny pionek" << endl;
	if (Player == 'X') {
		if (moveY == 0 || moveY2 == 0) Player = '#';
	}

	else if (Player == 'O') {
		if (moveY == 7 || moveY2 == 7) Player = '@';
	}
	int move;
	do {
		cin >> move;
		if (move < 1 || move >counter) cout << "Nieprawidlowy ruch!\n" << "Podaj ponowanie: ";
	} while (move < 1 || move >counter);
	if (move == counter) licznik++;
	else if ((move == 1 && counterL == counterP) || (move == 1 && counterL < counterP)) {
		if(tab[y][x] == '#') Player = '#';
		if (tab[y][x] == '@') Player = '@';
		tab[y][x] = ' ';
		tab[moveY][moveX] = Player;
		if (biciePX > 0) tab[y - 1][x + 1] = ' ';
		if (biciePO > 0) tab[y + 1][x + 1] = ' ';


	}
	else {
		if (tab[y][x] == '#') Player = '#';
		if (tab[y][x] == '@') Player = '@';
		tab[y][x] = ' ';
		tab[moveY2][moveX2] = Player;
		if (bicieLX > 0) tab[y - 1][x - 1] = ' ';
		if (bicieLO > 0) tab[y + 1][x - 1] = ' ';

	}
}
bool win(char tab[8][8], int& draw1, int & licznik2) {
	int kolko = 0, krzyzyk = 0, counterPX = 0, counterLX = 0, counterPO = 0, counterLO = 0;
	int DrawOption;
	char Player;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (tab[i][j] == 'O') kolko++;
			if (tab[i][j] == 'X') krzyzyk++;
			if (tab[i][j] == '@') kolko++;
			if (tab[i][j] == '#') krzyzyk++;
		}
	}
	if (kolko == 0) {
		cout << "Wygrywa krzyzyk" << endl;
		return false;
	}
	if (krzyzyk == 0) {
		cout << "Wygrywa kolko" << endl;
		return false;
	}
	//cout << "Ilosc kolek: " << kolko << " Ilosc krzyzykow: " << krzyzyk << endl; 
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (tab[i][j] == 'X') {
				if (i - 1 >= 0 && j + 1 < 8) {//w prawo X
					if (tab[i - 1][j + 1] == 'O') {
						if (tab[i - 2][j + 2] != ' ' && (i - 2 >= 0 && j + 2 < 8)) counterPX++;
						else if (i - 2 < 0 || j + 2 >= 8) counterPX++;
					}
					else if (tab[i - 1][j + 1] == 'X')	counterPX++;

				}
				else counterPX++;
				if (i - 1 >= 0 && j - 1 >= 0) {//w lewo X
					if (tab[i - 1][j - 1] == 'O') {
						if (tab[i - 2][j - 2] != ' ' && (i - 2 >= 0 && j - 2 >= 0)) counterLX++;
						else if (i - 2 < 0 || j - 2 < 0) counterLX++;
					}
					else if (tab[i - 1][j - 1] == 'X') counterLX++;
				}
				else counterLX++;
			}
			else if (tab[i][j] == 'O') {
				if (i + 1 < 8 && j + 1 < 8) {//w prawo O
					if (tab[i + 1][j + 1] == 'X') {
						if (tab[i + 2][j + 2] != ' ' && (i + 2 < 8 && j + 2 < 8))  counterPO++;
						else if (i + 2 >= 8 || j + 2 >= 8) counterPO++;
					}
					else if (tab[i + 1][j + 1] == 'O') counterPO++;
				}
				else  counterPO++;
				if (i + 1 < 8 && j - 1 >= 0) { //w lewo O
					if (tab[i + 1][j - 1] == 'X') {
						if (tab[i + 2][j - 2] != ' ' && (i + 2 < 8 && j - 2 >= 0)) counterLO++;
						else if (i + 2 >= 8 || j - 2 < 0) counterLO++;
					}
					else if (tab[i + 1][j - 1] == 'O') counterLO++;
				}
				else  counterLO++;

			}

		}
	}
	//cout << "Dla X: Blokady w prawo: " << counterPX << ", w lewo: " << counterLX << endl << "Dla O: Blokady w prawo: " << counterPO << ", w lewo: " << counterLO << endl;
	if (counterPO == counterLO && counterPO == kolko) {
		cout << "Wygrywa krzyzyk" << endl;
		return false;
	}
	if (counterPX == counterLX && counterPX == krzyzyk) {
		cout << "Wygrywa kolko" << endl;
		return false;
	}
	if (draw1 == 1) {
		if (licznik2 % 2 == 0) cout << "\t    Tura gracza X\n" << endl;
		else cout << "\t    Tura gracza O\n" << endl;
		cout << "akceptujesz remis\?\n0 - Nie\n1 - Tak" << endl;
		cin >> DrawOption;
		if (DrawOption == 1) {
			system("cls");
			cout << "Gra konczy sie remisem, gratulacje." << endl;
			return false;
		}
		else {
			system("cls");
			licznik2++;
			draw1--;
			return true;
		}
	}
	return true;
}
