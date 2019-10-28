/*
For GDW Challenge 2, first semester, first year
Basic Connect 4 game
*/
#include<conio.h>  
#include <windows.h>  
#include <iostream> 
#include <string> 
#include <limits>
#include <cstdlib>
#include <time.h>
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
int ColumnMaxCheck[6]{ 0 };
int Column1Count{ 0 }, Column2Count{ 0 }, Column3Count{ 0 }, Column4Count{ 0 }, Column5Count{ 0 }, Column6Count{ 0 }, Column7Count{ 0 };

int AiEasy(); //Returns random int for drop 
void WinCheck(); //For wincheck 
void startScreen(); //Runs start stuff 
void twoPlayer(); //2 player game loop 
void OnePlayerEasy(); //Easy AI 
void basicGame(int, int); //Runs the game 
void updateBoard(); //Updates board 
void drawBoard(); //Draws the board 
void VerifyInput(); //Checks if the user input is valid 
void ColumnMax();


int main() {
	
	srand(time(NULL));
	startScreen();
	std::cout << "Thanks for Playing\n";
}

void startScreenOutput() {

	for (int i = 0; i < 6; i++) {
		std::cout << Title[i] << endl;
	}
	std::cout << endl;

	std::cout << "	      1 = Two Player\n";
	std::cout << "	      2 = Single Player vs AI\n";
	std::cout << "              3 = Rules\n";
	std::cout << "	      4 = EXIT\n";
	std::cout << endl;
}

void startScreen()
{
	startScreenOutput();
	bool InputLoop{ true };
	int gamemode;
	std::cout << "Please type in either 1, 2, 3 or 4 from the options above to coninue: ";

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
		OnePlayerEasy();
		InputLoop = false;
	}
	else if (gamemode == 4)
	{
		system("CLS");
		std::cout << "Thanks for playing!";
		exit(1);
	}
	else if (gamemode == 3)
	{
		string rulemove; //Just used to cin, doesn't do anything 
		system("CLS");
		std::cout << "Here are the Rules:\n";
		std::cout << endl;
		std::cout << "Four in a row AKA Connect 4 is a game where your goal is connect 4 of your pieces \ntogether in a row.";
		std::cout << " This goal can be done by having 4 consecutive pieces in a row\nhorizontally, vertically, or diagonally.";
		std::cout << " The game will take turns allowing each\nplayer to place one piece in a turn.Your goal is to block your ";
		std::cout << "opponents 4 in a\nrow while trying to get 4 of your piece in a row first.When it is your turn, type\nin an ";
		std::cout << "integer from 1-7 which will represent which row to drop your piece in. If\nthe game is 2 player, then let ";
		std::cout << "your opponent take his turn. If you are playing\nagainst AI, the AI will automatically place their piece";
		std::cout << "after you make your move.\nThat is pretty much it.Thanks for reading and hope you enjoy the game :) ";
		std::cout << "\nPress any key to go back & enter to go back to menu \n";
		std::cin >> rulemove;
		system("CLS");
		startScreen();
	}
	else if (gamemode != 1 && gamemode != 2 && gamemode != 3 && gamemode != 4) {
		std::cout << "Invalid input, try again \n";
	}
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

	setupBoard();
	drawBoard();
	while (game)
	{
		if (player == 1)
		{
			std::cout << endl << "Player 1, you are O, pick your row: ";
		}
		else if (player == 2)
		{
			std::cout << endl << "Player 2, you are X, pick your row: ";
		}
		VerifyInput();
		std::cout << endl;
		basicGame(drop, player);
		updateBoard();
		drawBoard();
		WinCheck();
		switch (player) { //update current player 
		case 1: player = 2; break;
		case 2: player = 1; break;
		}
	}
}
void OnePlayerEasy() {
	setupBoard();
	player = 1; //Sets human player first 

	setupBoard();
	drawBoard();

	while (game == true) {
		if (player == 1)
		{
			std::cout << "Pick your row, you are O: " << endl;
			VerifyInput();
			std::cout << endl;
			basicGame(drop, player);
			updateBoard();
			drawBoard();
			player = 2;
			WinCheck();
		}
		else if (player == 2)
		{

			basicGame(AiEasy(), 2);
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

	for (int i = 5; i >= -2; i--)
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

void drawBoard() 
{
	
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
	for (int i = 0; i < 7; i++) {
		std::cout << columns[i];
	}
	std::cout << "\n";

	for (int i = 0; i < maxColumn; i++) {
		for (int j = 0; j < maxRow; j++) {
			std::cout << board[i][j];
		}
		std::cout << "\n";
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
void ColumnMax()
{
	
	if (drop == 1)
	{
		Column1Count++;
	}
	else if (drop == 2)
	{
		Column2Count++;
	}
	else if (drop == 3)
	{
		Column3Count++;
	}
	else if (drop == 4)
	{
		Column4Count++;
	}
	else if (drop == 5)
	{
		Column5Count++;
	}
	else if (drop == 6)
	{
		Column6Count++;
	}
	else if (drop == 7)
	{
		Column7Count++;
	}
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
			std::cout << "Invalid Input, try again " << std::endl;
		}
		if ((drop <= 7) && drop > 0)
		{		
			ColumnMax();
			if (drop == 1)
			{
				if (Column1Count < 7)
				{
					break;
				}
				else
				{
					std::cout << "Invalid Input, try again";
				}
			}	
			else if (drop == 2)
			{
				if (Column2Count < 7)
				{
					break;
				}
				else
				{
					std::cout << "Invalid Input, try again";
				}
			}
			else if (drop == 3)
			{
				if (Column3Count < 7)
				{
					break;
				}
				else
				{
					std::cout << "Invalid Input, try again";
				}
			}	
			else if (drop == 4)
			{
				if (Column4Count < 7)
				{
					break;
				}
				else
				{
					std::cout << "Invalid Input, try again";
				}
			}
			else if (drop == 5)
			{
				if (Column5Count < 7)
				{
					break;
				}
				else
				{
					std::cout << "Invalid Input, try again";
				}
			}
			else if (drop == 6)
			{
				if (Column6Count < 7)
				{
					break;
				}
				else
				{
					std::cout << "Invalid Input, try again";
				}
			}
			else if (drop == 7)
			{
				if (Column7Count < 7)
				{
					break;
				}
				else
				{
					std::cout << "Invalid Input, try again";
				}
			}
		}
		else
		{
			std::cout << "Invalid Input";
		}
		
	}
}

void WinCheck()
{
	string rulemove;
	//Vertical 
	for (int y = 0; y < maxColumn; y++)
	{
		for (int x = 0; x < maxRow; x++)
		{
			if (boardNum[y][x] == 1 && boardNum[y + 1][x] == 1 && boardNum[y + 2][x] == 1 && boardNum[y + 3][x] == 1)
			{
				system("CLS");
				std::cout << "  _____  _                         __            _           \n";
				std::cout << " |  __ \\| |                       /_ |          (_)          \n";
				std::cout << " | |__) | | __ _ _   _  ___ _ __   | | __      ___ _ __  ___ \n";
				std::cout << " |  ___/| |/ _` | | | |/ _ \\ '__|  | | \\ \\ /\\ / / | '_ \\/ __|\n";
				std::cout << " | |    | | (_| | |_| |  __/ |     | |  \\ V  V /| | | | \\__ \\ \n";
				std::cout << " |_|    |_|\\__,_|\\__, |\\___|_|     |_|   \\_/\\_/ |_|_| |_|___/\n";
				std::cout << "                  __/ |                                      \n";
				std::cout << "                 |___/                                       \n";
				std::cout << endl;
				std::cout << "Press any key + enter to close the game\n";
				cin >> rulemove;
				game = false;
			}
			else if (boardNum[y][x] == 2 && boardNum[y + 1][x] == 2 && boardNum[y + 2][x] == 2 && boardNum[y + 3][x] == 2)
			{
				system("CLS");
				std::cout << "  _____  _                         ___             _           \n";
				std::cout << " |  __ \\| |                       |__ \\           (_)          \n";
				std::cout << " | |__) | | __ _ _   _  ___ _ __     ) | __      ___ _ __  ___ \n";
				std::cout << " |  ___/| |/ _` | | | |/ _ \\ '__|   / /  \\ \\ /\\ / / | '_ \\/ __|\n";
				std::cout << " | |    | | (_| | |_| |  __/ |     / /_   \\ V  V /| | | | \\__ \\  \n";
				std::cout << " |_|    |_|\\__,_|\\__, |\\___|_|    |____|   \\_/\\_/ |_|_| |_|___/\n";
				std::cout << "                  __/ |                                        \n";
				std::cout << "                 |___/                                         \n";
				std::cout << endl;
				std::cout << "Press any key + enter to close the game\n";
				cin >> rulemove;
				game = false;
				break;
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
				system("CLS");
				std::cout << "  _____  _                         __            _           \n";
				std::cout << " |  __ \\| |                       /_ |          (_)          \n";
				std::cout << " | |__) | | __ _ _   _  ___ _ __   | | __      ___ _ __  ___ \n";
				std::cout << " |  ___/| |/ _` | | | |/ _ \\ '__|  | | \\ \\ /\\ / / | '_ \\/ __|\n";
				std::cout << " | |    | | (_| | |_| |  __/ |     | |  \\ V  V /| | | | \\__ \\ \n";
				std::cout << " |_|    |_|\\__,_|\\__, |\\___|_|     |_|   \\_/\\_/ |_|_| |_|___/\n";
				std::cout << "                  __/ |                                      \n";
				std::cout << "                 |___/                                       \n";
				std::cout << endl;
				std::cout << "Press any key + enter to close the game\n";
				cin >> rulemove;
				game = false;
				break;
			}
			else if (boardNum[y][x] == 2 && boardNum[y][x + 1] == 2 && boardNum[y][x + 2] == 2 && boardNum[y][x + 3] == 2)
			{
				system("CLS");
				std::cout << "  _____  _                         ___             _           \n";
				std::cout << " |  __ \\| |                       |__ \\           (_)          \n";
				std::cout << " | |__) | | __ _ _   _  ___ _ __     ) | __      ___ _ __  ___ \n";
				std::cout << " |  ___/| |/ _` | | | |/ _ \\ '__|   / /  \\ \\ /\\ / / | '_ \\/ __|\n";
				std::cout << " | |    | | (_| | |_| |  __/ |     / /_   \\ V  V /| | | | \\__ \\  \n";
				std::cout << " |_|    |_|\\__,_|\\__, |\\___|_|    |____|   \\_/\\_/ |_|_| |_|___/\n";
				std::cout << "                  __/ |                                        \n";
				std::cout << "                 |___/                                         \n";
				std::cout << "Press any key + enter to close the game\n";
				cin >> rulemove;
				game = false;
				std::cout << endl;
				break;
			}
		}
		//Both Diagonals 
		for (int x = 0; x < (maxRow); x++)
		{
			for (int y = 0; y < (maxColumn); y++)
			{
				if ((boardNum[y][x] == 1 && boardNum[y + 1][x + 1] == 1 && boardNum[y + 2][x + 2] == 1 && boardNum[y + 3][x + 3] == 1)
					|| (boardNum[y + 3][x] == 1 && boardNum[y + 2][x + 1] == 1 && boardNum[y + 1][x + 2] == 1 && boardNum[y][x + 3] == 1))
				{
					system("CLS");
					std::cout << "  _____  _                         __            _           \n";
					std::cout << " |  __ \\| |                       /_ |          (_)          \n";
					std::cout << " | |__) | | __ _ _   _  ___ _ __   | | __      ___ _ __  ___ \n";
					std::cout << " |  ___/| |/ _` | | | |/ _ \\ '__|  | | \\ \\ /\\ / / | '_ \\/ __|\n";
					std::cout << " | |    | | (_| | |_| |  __/ |     | |  \\ V  V /| | | | \\__ \\ \n";
					std::cout << " |_|    |_|\\__,_|\\__, |\\___|_|     |_|   \\_/\\_/ |_|_| |_|___/\n";
					std::cout << "                  __/ |                                      \n";
					std::cout << "                 |___/                                       \n";
					std::cout << endl;
					std::cout << "Press any key + enter to close the game\n";
					cin >> rulemove;
					game = false;
					break;
					break;
				}
			}
			for (int x = 0; x < (maxRow); x++)
			{
				for (int y = 0; y < (maxRow); y++)
				{
					if ((boardNum[y][x] == 2 && boardNum[y + 1][x + 1] == 2 && boardNum[y + 2][x + 2] == 2 && boardNum[y + 3][x + 3] == 2)
						|| (boardNum[y + 3][x] == 2 && boardNum[y + 2][x + 1] == 2 && boardNum[y + 1][x + 2] == 2 && boardNum[y][x + 3] == 2))
					{

						system("CLS");
						std::cout << "  _____  _                         ___             _           \n";
						std::cout << " |  __ \\| |                       |__ \\           (_)          \n";
						std::cout << " | |__) | | __ _ _   _  ___ _ __     ) | __      ___ _ __  ___ \n";
						std::cout << " |  ___/| |/ _` | | | |/ _ \\ '__|   / /  \\ \\ /\\ / / | '_ \\/ __|\n";
						std::cout << " | |    | | (_| | |_| |  __/ |     / /_   \\ V  V /| | | | \\__ \\  \n";
						std::cout << " |_|    |_|\\__,_|\\__, |\\___|_|    |____|   \\_/\\_/ |_|_| |_|___/\n";
						std::cout << "                  __/ |                                        \n";
						std::cout << "                 |___/                                         \n";
						std::cout << endl;
						std::cout << "Press any key + enter to close the game\n";
						cin >> rulemove;
						game = false;
						break;
						break;
					}
				}
			}
		}
	}
}