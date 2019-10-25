
#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

const string Title[6] = {" _____________________________________________________ ",
						 "|   __    _                 ___    _____              |",
						 "|  |  |  |_|___ ___     ___|  _|  |   __|___ _ _ ___  |",
						 "|  |  |__| |   | -_|   | . |  _|  |   __| . | | |  _| |",
						 "|  |_____|_|_|_|___|   |___|_|    |__|  |___|___|_|   |",
						 "|_____________________________________________________|"};

int startscreeninput = 0; //the input from the user on the start screen
int levelAI = 0; //the input for the difficuty
bool game = true;
int player;

const int maxColumn = 7;
const int maxRow = 6;
int boardNum[maxColumn][maxRow];
string board[maxColumn][maxRow];
string columns[maxRow] = { "  1  ","  2  ","  3  ","  4  ","  5  ","  6  " };
const string boardSpace = "[( )]";


void getLevelAI();
void twoPlayer();
void onePlayer();
void basicGame(int, int);
void updateBoard();
void drawBoard();

void startScreenOutput() {

	for (int i = 0; i < 6; i++) {
		cout << Title[i] << endl;
	}
	cout << endl;

	cout << "	      1 = Two Player\n";
	cout << "	      2 = Single Player vs AI\n";
	cout << "	      3 = EXIT\n";
	cout << endl;
}

void startScreen() {
	startScreenOutput();

	int gamemode;
	cout << "Please type in either 1, 2 or 3 from the options above to coninue: ";
	cin >> gamemode;

	if (gamemode == 1) {
		twoPlayer();
	}
	else if (gamemode == 2) {
		getLevelAI();
	}
	else if (gamemode != 1 && gamemode != 2 && gamemode != 3) {
		cout << "INVALID ENTRY";
	}
}

void getLevelAI() {
	cout << "Please select the difficulty of the AI\n";
	cout << "1 = EASY\n";
	cout << "2 = MEDIUM\n";
	cout << "3 = HARD\n";
	cin >> levelAI;
	
	if (levelAI == 1) {
		//play against the easy AI
	}
	else if (levelAI == 2) {
		//play against the medium AI
	}
	else if (levelAI == 3) {
		//play against the hard AI
	}
	else
		cout << "INVALID ENTRY";

}

void setupBoard() {
	for (int i = 0; i < maxColumn; i++) {
		for (int j = 0; j < maxRow; j++) {
			boardNum[i][j] = 0;
			board[i][j] = boardSpace;
		}
	}
}

void twoPlayer() {
	player = (rand() % 2) + 1;
	cout << endl << "Player 1 will be using O pieces, Player 2 will be using 0 pieces." << '\n' << "Going first will be Player " << player << endl << endl;
	setupBoard();
	drawBoard();

	while (game) {
		cout << endl << "Player " << player << ", pick your row: ";
		int drop;
		cin >> drop;
		cout << endl;
		basicGame(drop, player);
		updateBoard();
		drawBoard();
		//check win condition
		switch (player) { //update current player
		case 1: player = 2; break;
		case 2: player = 1; break;
		}
	}
}

void onePlayer() {
	setupBoard();
	//AI Game, human is Player 1
}

void basicGame(int columnSelected, int playerTurn) {
	int column = columnSelected - 1;
	for (int i = maxColumn; i >= 0; i--) {

		if (boardNum[i][column] == 0) {
			boardNum[i][column] = player;
			break;
		}
	}
	//start at bottom of column, if its already occupied, go up to the next one

}

void updateBoard() {
	for (int i = 0; i < maxColumn; i++) {
		for (int j = 0; j < maxRow; j++) {
			if (boardNum[i][j] == 1) {
				board[i][j] = "[(O)]";
			}
			else if (boardNum[i][j] == 2) {
				board[i][j] = "[(X)]";
			}
		}
	}
}

void drawBoard() {
	for (int i = 0; i < maxColumn; i++) {
		cout << columns[i];
	}
	cout << "\n";

	for (int i = 0; i < maxColumn; i++) {
		for (int j = 0; j < maxRow; j++) {
			cout << board[i][j];
		}
		cout << "\n";
	}
}

int main() {
	startScreen();
	cout << "Thanks for Playing\n";
}