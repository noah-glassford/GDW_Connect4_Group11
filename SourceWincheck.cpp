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
bool FullRow; //Used to get a new input if the row is full
const int maxColumn = 6; //Defines board columns
const int maxRow = 7; //defines board rows
int boardNum[6][7];//Board Data
string board[maxColumn][maxRow]; //Visuals
string columns[7] = { "  1  ","  2  ","  3  ","  4  ","  5  ","  6  ", "  7  " }; //Identifies rows to the players
const string boardSpace = "[( )]"; //Each grid piece to be printed


int AiEasy(); //Returns random int for drop
void WinCheck(); //For wincheck
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

void startScreen() 
{
	startScreenOutput();
	bool InputLoop{ true };
	int gamemode;
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
	for (int i = 0; i <= 5; i++) {
		for (int j = 0; j <= 6; j++) {
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
	while (game) 
	{
			cout << endl << "Player " << player << ", pick your row: ";
			VerifyInput();
			cout << endl;
			basicGame(drop, player);
			updateBoard();
			WinCheck();
		
		drawBoard();
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
			WinCheck();
		}
		else if (player == 2)
		{
			
			updateBoard();
			drawBoard(); //Draws board for the player after the ai goes
			player = 1;
			WinCheck();
		}
		
	}
	//AI Game, human is Player 1
}

void basicGame(int columnSelected, int playerTurn)
{	
	for (int i = 6; i >= 0; i--) 
		{  
			if (boardNum[i][drop - 1] == 0) {
				boardNum[i][drop - 1] = player;
				break;
			}
		}
	
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
	//system("CLS"); //Clears Board to reduce Clutter
	if (turn % 2 == 0) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);// changes colour to Red 
		turn++;
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);// changes colour to Yellow 
		turn++;
	}
	for (int i = 0; i < 7; i++) {
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
		if (((drop <= 7)) && drop > 0 )
		{
			cout << "valid input";
			break;
			}	
			else
			{
			std::cout << "Invalid input, try again \n";
			}
		}
	}


void WinCheck()
{
	//Vertical
	for (int y = 0; y < maxColumn; y++)
	{
		for (int x = 0; x < maxRow; x++)
		{
			if (boardNum[y][x] == 1 && boardNum[y + 1][x] == 1 && boardNum[y + 2][x] == 1 && boardNum[y + 3][x] == 1)
			{
				cout << "Player 1 wins";
				game = false;
			}
			else if (boardNum[y][x] == 2 && boardNum[y + 1][x] == 2 && boardNum[y + 2][x] == 2 && boardNum[y + 3][x] == 2)
			{
				cout << "Player 2 wins";
				game = false;
			}
		}
	}
		
	

	//  vertical plane
	for (int x = 0; x < maxRow; x++)
	{
		for (int y = 0; y < maxColumn; y++)
		{
			if (boardNum[y][x] == 1 && boardNum[y][x + 1] == 1 && boardNum[y][x + 2] == 1 && boardNum[y][x + 3] == 1)
			{
				cout << "\nPlayer 1 wins";
				game = false;
			}
			else if (boardNum[y][x] == 2 && boardNum[y][x + 1] == 2 && boardNum[y][x + 2] == 2 && boardNum[y][x + 3] == 2)
			{
				cout << "\nPlayer 2 wins";
				game = false;
			}

	//Both Diagonals
			for (int x = 0; x < (maxRow); x++)
			{
				for (int y = 0; y < (maxColumn); y++)
				{
					if ((boardNum[y][x] == 1 && boardNum[y + 1][x + 1] == 1 && boardNum[y + 2][x + 2] == 1 && boardNum[y + 3][x + 3] == 1)  //Checks both directions of vertical
						|| (boardNum[y + 3][x] == 1 && boardNum[y + 2][x + 1] == 1 && boardNum[y + 1][x + 2] == 1 && boardNum[y][x + 3] == 1))
					{
						cout << "\nPlayer 1 wins";
						game = false;
					}
					else if ((boardNum[y][x] == 1 && boardNum[y + 1][x + 1] == 1 && boardNum[y + 2][x + 2] == 1 && boardNum[y + 3][x + 3] == 1)  //Checks both directions of vertical
						|| (boardNum[y + 3][x] == 2 && boardNum[y + 2][x + 1] == 2 && boardNum[y + 1][x + 2] == 2 && boardNum[y][x + 3] == 2))
					{
						cout << "\nPlayer 2 wins";
						game = false;
					}
				}
			}
		}
	}
}