#include<iostream>
#include "gomokuBoard.h"
using namespace std;

// Constructor
gomokuBoard::gomokuBoard()
{	
	size = 15;
	board = new int[size][size];
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			board[i][j] = 0;
		}
	}
}

gomokuBoard::gomokuBoard(unsigned s)
{	
	size = s;
	board = new int[size][size];
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			board[i][j] = 0;
		}
	}
}

gomokuBoard::~gomokuBoard()
{
	delete[] board;
}

// Place a new piece on the board after a move
void place(int playerNum, unsigned row, unsigned col)
{
	if (row >= size || col >= size || (playerNum != 1 && playerNum != -1))
		return;

	board[row*size + col] = playerNum;
}

int checkWin()
{

}