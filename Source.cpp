/*
For GDW Challenge 2, first semester, first year
Basic Connect 4 game
*/
#include<conio.h> 
#include <windows.h> 
#include <iostream>
#include <string>
#include <limits> //For input verification
#include <cstdlib> //For Random numbers in AI
#undef max //Undefines max to use cin.ignore functions
using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // For use of SetConsoleTextAttribute() 

const string Title[6] = { " _____________________________________________________ ", //Title Card
						 "|   __    _                 ___    _____              |",
						 "|  |  |  |_|___ ___     ___|  _|  |   __|___ _ _ ___  |",
						 "|  |  |__| |   | -_|   | . |  _|  |   __| . | | |  _| |",
						 "|  |_____|_|_|_|___|   |___|_|    |__|  |___|___|_|   |",
						 "|_____________________________________________________|" };

int startscreeninput = 0; //the input from the user on the start screen
int levelAI = 0; //the input for the difficuty
bool game = true; //Used to run the game's loop
int player; //Decides which player goes
int drop; //Used to place pieces
int turn = 0;//sets turn value to zero (for colour in draw board) 
const int maxColumn = 7; //Defines board columns
const int maxRow = 6; //defines board rows
int boardNum[maxColumn][maxRow]; //Board Data
string board[maxColumn][maxRow]; //Visuals
string columns[maxRow] = { "  1  ","  2  ","  3  ","  4  ","  5  ","  6  " }; //Identifies rows to the players
const string boardSpace = "[( )]"; //Each grid piece to be printed


int AiEasy(); //Returns random int for drop
//int AiProcessing(); //Rturns the int that the AI will drop
void startScreen(); //Runs start stuff
void getLevelAI(); //Tells the game which ai to run
void twoPlayer(); //2 player game loop
void OnePlayerEasy(); //Easy AI
void basicGame(int, int); //Runs the game
void updateBoard(); //Updates board
void drawBoard(); //Draws the board
void VerifyInput(); //Checks if the user input is valid


int main() {
	startScreen();
	cout << "Thanks for Playing\n";
}

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
	bool InputLoop{ true };
	int gamemode;
	while (InputLoop == true) //This input parser is only used once so I just put it in, but the one that runs during the game will be its own function.
	{
		
		cout << "Please type in either 1, 2 or 3 from the options above to coninue: ";
		
		while (1)
		{
			cin >> gamemode;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				std::cout << "Invalid input, try again" << std::endl;

			}
			else
			{
				break;
			}
		}
			if (gamemode == 1) {
			twoPlayer();
			InputLoop = false;
		}
		else if (gamemode == 2) {
			getLevelAI();
			InputLoop = false;
		}
		else if (gamemode == 3)
		{
				std::cout << "Thanks for playing!";
				exit(1);
		}
		else if (gamemode != 1 && gamemode != 2 && gamemode != 3) {
			cout << "Invalid input, try again \n";
		}
	
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
		OnePlayerEasy();
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
	basicGame(4, 1); //Fills in rows 4 & 5, really bad solution
	basicGame(5, 2);
	
	cout << endl << "Player 1 will be using O pieces, Player 2 will be using 0 pieces." << '\n' << "Going first will be Player " << player << endl << endl;
	setupBoard();
	drawBoard();
	while (game) {
		cout << endl << "Player " << player << ", pick your row: ";
		VerifyInput();
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

void OnePlayerEasy() {
	setupBoard();
	player = 1; //Sets human player first
	cout << endl << "Player 1 will be using O pieces, Player 2 will be using 0 pieces." << '\n' << "Going first will be Player " << player << endl << endl;
	setupBoard();
	drawBoard();
	
	while (game == true) {
		if (player == 1)
		{
			cout << "Pick your row" << endl;
			VerifyInput();
			cout << endl;
			basicGame(drop, player);
			updateBoard();
			drawBoard();
			player = 2;
			//checkWin
		}
		else if (player == 2)
		{
			basicGame(AiEasy(), player);
			updateBoard();
			drawBoard(); //Draws board for the player after the ai goes
			player = 1;
			//checkWin
		}
		
	}
	//AI Game, human is Player 1
}

void basicGame(int columnSelected, int playerTurn) {
	bool found = false;
	int column = columnSelected - 1;
	for (int i = maxColumn; i >= 2 && !found; i--) { //bruh

		if (boardNum[i][column] == 0) {
			boardNum[i][column] = player;
			found = true;
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
	system("CLS"); //Clears Board to reduce Clutter
	if (turn % 2 == 0) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);// changes colour to Red 
		turn++;
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);// changes colour to Yellow 
		turn++;
	}
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
/*
This functtion will be used for the easy ai, which will just place a random piece on its turn.
*/
int AiEasy()
{
	drop = rand() % 7 + 1;
	return drop;
}

//This function will do all the calculations for droping the pieces
/*int AiProcessing()
{
	//Done in pseudocode for now, waiting on wincheck code
	//Effectively runs a mini version of the game with no display and no consequence
	int AiBoardCopy[maxColumn][maxRow] = { boardNum[maxColumn][maxRow] };
	for (int i; i > 7; i++)
	{

	}

	return 0;
}
*/
void VerifyInput()
{
	while (1)
	{
		cin >> drop;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			std::cout << "Invalid input, try again" << std::endl;
		}
		else
		{
			if (!(drop > 6) && drop > 0)
			{
				break;
			}
			else
			{
				std::cout << "Invalid input, try again \n";
			}
		}
	
	}
}