// this is a psudcode version of what I want the final win condition algorithim to be
#include <ioStream>
#include <string>
using namespace std;
// these are just to load things I may need 
// will write the psudocode comments first then the actual code I think would work
// first create 2 variables one an int named red and the other an int named Yellow
// then create 3 diffrent variables each named red horizontal red vertical and red diagonal
// then create 3 variables with the same name convention only this time swap the word red with the word blue
// these 6 variables probably should be arrays so that if 
//2 diffrent blue tokens in a vertical position are added at opposite sides of board the total for vertical
//Yellow would be 1 and 1 not 2 total because you could accidentally win if that occurs 
//I would then have an if statment and an else if stament 
// the the 2 statments would be identical with only 1 thing changing between them
// for example if stament 1 might say if yellow vertical or yellow horizontal or Yellow diagonal = 4 
// that the blue team wins it would check every slot in the arrays for a value of 4 stored within and report back
//it would be exactly the same for red team
// after that the game would print to screen which team won the game and its as simple as that
// the game would also need text for the potential of a tie although very unlikely 
//after all slots on board get filled stating the game ended in a stalemate or something to that extent
// create 2 extra variables for ties or maybe just use red and yellow master variables 
//if both red and blue total in at 21 the game is a tie.
int yellow = 0;
int yellowVertical[21];
int yellowHorizontal[21];
int yellowDiagonal[21];
int red = 0;
int redVertical[21];
int redHorizontal[21];
int redDiagonal[21];
// in the actual game there is an a value placed in each slot that is full so we need to look to see if every slot has been filled by either a 1 or 2 with 0 meaning empty 
int main() {



	if (red == 21 && yellow == 21) {
		cout << "its a tie"; 
	}
	else if (yellowDiagonal[0] == 4 || yellowHorizontal[0] == 4 || yellowVertical[0] == 4 || yellowDiagonal[1] == 4 || yellowHorizontal[1] == 4 || yellowVertical[1] == 4 || yellowDiagonal[2] == 4 || yellowHorizontal[2] == 4 || yellowVertical[2] == 4 || yellowDiagonal[3] == 4 || yellowHorizontal[3] == 4 || yellowVertical[3] == 4 || yellowDiagonal[4] == 4 || yellowHorizontal[4] == 4 || yellowVertical[4] == 4 || yellowDiagonal[5] == 4 || yellowHorizontal[5] == 4 || yellowVertical[5] == 4 || yellowDiagonal[6] == 4 || yellowHorizontal[6] == 4 || yellowVertical[6] == 4 || yellowDiagonal[7] == 4 || yellowHorizontal[7] == 4 || yellowVertical[7] == 4 || yellowDiagonal[8] == 4 || yellowHorizontal[8] == 4 || yellowVertical[8] == 4 || yellowDiagonal[9] == 4 || yellowHorizontal[9] == 4 || yellowVertical[9] == 4 || yellowDiagonal[10] == 4 || yellowHorizontal[10] == 4 || yellowVertical[10] == 4 || yellowDiagonal[11] == 4 || yellowHorizontal[11] == 4 || yellowVertical[11] == 4 || yellowDiagonal[12] == 4 || yellowHorizontal[12] == 4 || yellowVertical[12] == 4 || yellowDiagonal[13] == 4 || yellowHorizontal[13] == 4 || yellowVertical[13] == 4 || yellowDiagonal[14] == 4 || yellowHorizontal[14] == 4 || yellowVertical[14] == 4 || yellowDiagonal[15] == 4 || yellowHorizontal[15] == 4 || yellowVertical[15] == 4 || yellowDiagonal[16] == 4 || yellowHorizontal[16] == 4 || yellowVertical[16] == 4 || yellowDiagonal[17] == 4 || yellowHorizontal[17] == 4 || yellowVertical[17] == 4 || yellowDiagonal[18] == 4 || yellowHorizontal[18] == 4 || yellowVertical[18] == 4 || yellowDiagonal[19] == 4 || yellowHorizontal[19] == 4 || yellowVertical[19] == 4 || yellowDiagonal[20] == 4 || yellowHorizontal[20] == 4 || yellowVertical[20] == 4) {
		cout << "yellow team wins";
	}
	else if (redDiagonal[0] == 4 || redHorizontal[0] == 4 || redVertical[0] == 4 || redDiagonal[1] == 4 || redHorizontal[1] == 4 || redVertical[1] == 4 || redDiagonal[2] == 4 || redHorizontal[2] == 4 || redVertical[2] == 4 || redDiagonal[3] == 4 || redHorizontal[3] == 4 || redVertical[3] == 4 || redDiagonal[4] == 4 || redHorizontal[4] == 4 || redVertical[4] == 4 || redDiagonal[5] == 4 || redHorizontal[5] == 4 || redVertical[5] == 4 ||  redDiagonal[6] == 4 || redHorizontal[6] == 4 || redVertical[6] == 4 || redDiagonal[7] == 4 || redHorizontal[7] == 4 || redVertical[7] == 4 || redDiagonal[8] == 4 || redHorizontal[8] == 4 || redVertical[8] == 4 || redDiagonal[9] == 4 || redHorizontal[9] == 4 || redVertical[9] == 4 || redDiagonal[10] == 4 || redHorizontal[10] == 4 || redVertical[10] == 4 || redDiagonal[11] == 4 || redHorizontal[11] == 4 || redVertical[11] == 4 || redDiagonal[12] == 4 || redHorizontal[12] == 4 || redVertical[12] == 4 ||  redDiagonal[13] == 4 || redHorizontal[13] == 4 || redVertical[13] == 4 || redDiagonal[14] == 4 || redHorizontal[14] == 4 || redVertical[14] == 4 || redDiagonal[15] == 4 || redHorizontal[15] == 4 || redVertical[15] == 4 || redDiagonal[16] == 4 || redHorizontal[16] == 4 || redVertical[16] == 4 || redDiagonal[17] == 4 || redHorizontal[17] == 4 || redVertical[17] == 4 || redDiagonal[18] == 4 || redHorizontal[18] == 4 || redVertical[18] == 4 || redDiagonal[19] == 4 || redHorizontal[19] == 4 || redVertical[19] == 4 || redDiagonal[20] == 4 || redHorizontal[20] == 4 || redVertical[20] == 4) {
		cout << "red team wins";
	}
}









