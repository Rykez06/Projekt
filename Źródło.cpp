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
void gameplay(char tab[8][8], int counter);
bool coordinatesChecker(int y, int x, char tab[8][8], char Player);
void moves(int y, int x, char tab[8][8], char Player);

bool win();
int main() {
	char board[8][8] = { {' ','O',' ','O',' ','O', ' ', 'O'},
						{'O',' ','O',' ','O',' ', 'O', ' '},
						{' ','O',' ','O',' ','O', ' ', 'O'},
						{' ',' ',' ',' ',' ',' ', ' ', ' '},
						{' ',' ',' ',' ',' ',' ', ' ', ' '},
						{'X',' ','X',' ','X',' ', 'X', ' '},
						{' ','X',' ','X',' ','X', ' ', 'X'},
						{'X',' ','X',' ','X',' ', 'X', ' '} };
	//intro();
	int RoundCounter=0;
	while (win) {
		gameplay(board, RoundCounter);
		RoundCounter++;
	}
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
			sleep(10);
		}
		y += 1;

		cout << " |" << endl;
		cout << "  +---+---+---+---+---+---+---+---+";
		cout << endl;


	}
}
void gameplay(char tab[8][8], int counter) {
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
	cout << "Podaj koordynaty pionka, ktorym chcesz sie poruszyc: ";
	cin >> coordinates;
	int letter, number;
	if (coordinates[0] >= 65 && coordinates[0] <= 72) letter = coordinates[0] - 65;
	else if (coordinates[0] >= 97 && coordinates[0] <= 104) letter = coordinates[0] - 97;
	else cout << "NIeprawidlowe koordynaty\n";
	if (coordinates[1] >= 49 && coordinates[1] <= 56) number = coordinates[1] - 49;
	else cout << "NIeprawidlowe koordynaty\n";
	cout << endl << number << "\t" << letter;
	while (!coordinatesChecker(number, letter, tab, Player)) {
		if (coordinates[0] >= 65 && coordinates[0] <= 72) letter = coordinates[0] - 65;
		else if (coordinates[0] >= 97 && coordinates[0] <= 104) letter = coordinates[0] - 97;
		else cout << "NIeprawidlowe koordynaty\n";
		if (coordinates[1] >= 49 && coordinates[1] <= 56) number = coordinates[1] - 49;
		else cout << "NIeprawidlowe koordynaty\n";
		cout << endl << number << "\t" << letter;
		if (!coordinatesChecker(number, letter, tab, Player) ){
			cout << "Podaj ponownie koordynaty: ";
			cin >> coordinates;
		}
	}cout << "Wybierz opcje:";
	moves(number, letter, tab, Player);
}

bool coordinatesChecker(int y, int x, char tab[8][8], char Player) {
	
	if (tab[y][x] == Player) return true;
	return false;
}
void moves(int y, int x, char tab[8][8], char Player) {
	if (Player == 'X') {
		if (y - 1 >= 0 && x + 1 < 8) {
			char x1 = x + 66, y1 = y + 48;
			if (tab[y - 1][x + 1] == ' ') cout << "mozliwosc ruchu w prawo na pole" <<x1<<y1<<endl;
		}
		if (y - 1 >= 0 && x - 1 >= 0) {
			char x1 = x + 64, y1 = y + 48;
			if (tab[y - 1][x - 1] == ' ') cout << "mozliwosc ruchu w lewo na pole" << x1 << y1 << endl;
		}
			

	}
	
	else {
		if (y + 1 < 8 && x + 1 < 8) {
			char x1 = x + 66, y1 = y + 50;
			if (tab[y + 1][x + 1] == ' ') cout << "mozliwosc ruchu w prawo na pole" << x1 << y1 << endl;
		}
		if (y + 1 < 8 && x - 1 >= 0) {
			char x1 = x + 64, y1 = y + 50;
			if (tab[y + 1][x - 1] == ' ') cout << "mozliwosc ruchu w lewo na pole" << x1 << y1 << endl;
		}

	}
}
bool win() {

	return false;
}