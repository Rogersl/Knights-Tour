//Logan Rogers

/*
This program takes an NxN board to find a Closed Knight's Tour.

The value of boardSize can be modified to easily try this program out for
any given boardSize.  However, bear in mind that a closed tour may only be found
for any N >= 6 that is even.  Odd values and lesser values cannot complete a closed
tour.

This program utilizes recursive backtracking and Warnsdorff's Rule to find a
closed tour.  Warnsdorff's Rule takes an initial starting position and
searches for subsequent locations with the fewest moves, moving to them.  

We use this approach to get near a closed tour.  However, achieving a closed
tour is not guaranteed with Warndorff's Rule.  This is why we also employ 
recursive backtracking.  We move back steps taken in Warndorff's Rule until
we arrive at a position to finish a closed tour.

While this may increase complexity a bit, the backtracking usually only involves
the final steps of Warnsdorff's Rule, meaning that we don't have to backtrack far
to reach our closed tour.  
*/

#include <iostream>

using namespace std;

const int boardSize = 8;
const int unvisitedFlag = -1;

bool knightTour(int startX, int startY);


//x and y represent knight's current location
//moveCount is the number of moves currently completed
//resultBoard[] represents the board, with each location holding a move number, or 0 if not mvoed to yet
//moveX[] and moveY[] are relative moves availalbe
//return true/false if resultBoard possible based on board and knight's movements
bool knightTour(const int x, const int y, const int moveCount, int resultBoard[boardSize][boardSize], const int moveX[], const int moveY[]);

//Returns true if position x,y on the board is a valid move,
//false if the position is off the board or has been used already
bool findValidMove(const int x, const int y, const int resultBoard[boardSize][boardSize]);

//Return true if the position x,y is on the board, and the position is the start position
//Used to guarantee a closed tour
bool findFinalMove(const int x, const int y, const int resultBoard[boardSize][boardSize]);

//prints the final board using cout
void printBoard(const int resultBoard[boardSize][boardSize]);

//returns the number of available moves from location x,y using findValidMove()
int countAvailableMoves(const int x, const int y, const int resultBoard[boardSize][boardSize]);

//returns an order of moves, based on the number of valid moves spawning from all available moves. 
//The result is the number of possible moves in ascending order
void warnsdorffOrder(const int x, const int y, const int resultBoard[boardSize][boardSize], int sorted[boardSize]);

int main()
{
  int startX = 0;
  int startY = 0;

  do{
    cout << "Input starting coordinates \n"
         << "Vertical Position (from 0 to 7) : ";
    cin >> startX;
    cout << "Hoirzontal Position (from 0 to 7) : ";
    cin >> startY;
    cout << endl;

    if(startX >= boardSize || startX < 0)
      cout << "Invalid X coordinate" << endl;
    if(startY >= boardSize || startY < 0)
      cout << "Invalid Y coordinate" << endl;
  }
  while(startX >= boardSize || startX < 0 || startY >= boardSize || startY < 0);
  
  knightTour(startX, startY);

  cout << "Type any input and hit the Enter key to exit." << endl;
  char x;
  cin >> x;
  return 0;
}

bool findValidMove(const int x,const int y, const int resultBoard[boardSize][boardSize])
{ 
  //check if move is onto board and if the space has already been occupied
  if(x >= 0 && x < boardSize && y >= 0 && y < boardSize && resultBoard[x][y] == -1)
    return true;
  else
    return false;
}

bool findFinalMove(const int x, const int y, const int resultBoard[boardSize][boardSize])
{
  //check if move is onto board and if the space is the same as the starting location
  if(x >= 0 && x < boardSize && y >= 0 && y < boardSize && resultBoard[x][y] == 0)
    return true;
  else
    return false;
}

void printBoard(const int resultBoard[boardSize][boardSize])
{
  for (int i = boardSize-1; i >= 0; i--)
  {
	   //for all positions in row
	   for (int j = 0; j < boardSize; j++)
	       cout << resultBoard[i][j] << ", \t";
	   cout << ("\n");
  }
}

int countAvailableMoves(const int x, const int y,const int resultBoard[boardSize][boardSize])
{
  int nextX;
  int nextY;
  int count = 0;

  //indexed moves
  int moveX[boardSize] = { 2, 1, -1, -2, -2, -1,  1,  2 };
  int moveY[boardSize] = { 1, 2,  2,  1, -1, -2, -2, -1 };

  for (int i = 0; i < boardSize; i++)
  {
	   nextX = x + moveX[i];
	   nextY = y + moveY[i];

	   if (findValidMove(nextX, nextY, resultBoard))
	   {
	     count++; 
	   }
  }

  return count;
}

void warnsdorffOrder(const int x, const int y, const int resultBoard[boardSize][boardSize], int sorted[boardSize])
{
  int j;
  int nextX;
  int nextY;
  int result[boardSize];

  //indexed moves
  int moveX[boardSize] = { 2, 1, -1, -2, -2, -1,  1,  2 };
  int moveY[boardSize] = { 1, 2,  2,  1, -1, -2, -2, -1 };

  for (int i = 0; i < boardSize; i++)
  {
	   nextX = x + moveX[i];     //simulate move
	   nextY = y + moveY[i];     //track possible moves from next location
	   result[i] = countAvailableMoves(nextX, nextY, resultBoard);
  }

  int min_i;
  int min_val;

  for (int i = 0; i < boardSize; i++)
  {
	   //move j to first element != 0
	   //that location is the basis for min_imum element test
	   j = 0;
	   do
	   {
	     min_i = j;
	     min_val = result[j];
	     j++;
	   } while (min_val == -1);
	
	   for (; j < boardSize; j++)
	   {
	     //if position less than current min_imum
	     if (result[j] < min_val && result[j] != -1)
	     {
		      //record value and location of new min_imum
		      min_val = result[j];
		      min_i = j;
	     }
	   }

	   //record index of min
	   sorted[i] = min_i;
	   //delete element
	   result[min_i] = -1;
  }

  //sorted[] should be indexes of result[] such that
  //result[] is sorted min to max based on possible moves

  return;
}

bool knightTour(int startX, int startY)
{
  //initialize board
  int resultBoard[boardSize][boardSize];

  for (int x = 0; x < boardSize; x++)
  {
	   for (int y = 0; y < boardSize; y++)
	     resultBoard[x][y] = unvisitedFlag;
  }

  int moveX[boardSize] = { 2, 1, -1, -2, -2, -1,  1,  2 };
  int moveY[boardSize] = { 1, 2,  2,  1, -1, -2, -2, -1 };

  //start location (input by user)
  int knightX = startX;
  int knightY = startY;

  //knight start, mark first position
  resultBoard[knightX][knightY] = 0;

  //recursive calls
  if (knightTour(knightX, knightY, 1, resultBoard, moveX, moveY) == false)
  {
	   cout << "\nNo solution" << endl;
	   return false;
  }
  else
	   printBoard(resultBoard);

  return true;
}

bool knightTour(const int x, const int y, const int moveCount, int resultBoard[boardSize][boardSize], const int moveX[boardSize], const int moveY[boardSize])
{
  int k;
  int nextX;
  int nextY;
  int om[boardSize];

  if (moveCount == boardSize*boardSize)
  {
	   k = 0;
	   bool check = false;
	   while (!check && k < boardSize)
	   {
	     nextX = x + moveX[k];
	     nextY = y + moveY[k];
	     if (findFinalMove(nextX, nextY, resultBoard))
	     {
		    check = true;
	     }
	     k++;
	   }
	   return check;
  }

  warnsdorffOrder(x, y, resultBoard, om);

  for (int i = 0; i < boardSize; i++)
  {
	   nextX = x + moveX[om[i]];
	   nextY = y + moveY[om[i]];


	   if (findValidMove(nextX, nextY, resultBoard))
	   {
    	  resultBoard[nextX][nextY] = moveCount;
    	  if (knightTour(nextX, nextY, moveCount + 1, resultBoard, moveX, moveY) == true)
    		    return true;
    	  else
    		    resultBoard[nextX][nextY] = unvisitedFlag;
    	}
  }

  return false;
}