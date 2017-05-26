#include<iostream>
#include "gomokuBoard.h"
using namespace std;

// Constructor & Destructor
gomokuBoard::gomokuBoard()
{	
	size = 15;
	isEmpty = true;
	board.resize(size);
	for (unsigned i = 0; i < size; i++) {
		board[i].resize(size);
	}

	for (unsigned i = 0; i < size; i++) {
		for (unsigned j = 0; j < size; j++) {
			board[i][j] = 0;
		}
	}
}

gomokuBoard::gomokuBoard(unsigned s)
{	
	size = s;
	isEmpty = true;
	board.resize(size);
	for (unsigned i = 0; i < size; i++) {
		board[i].resize(size);
	}

	for (unsigned i = 0; i < size; i++) {
		for (unsigned j = 0; j < size; j++) {
			board[i][j] = 0;
		}
	}
}

gomokuBoard::~gomokuBoard()
{

}

// Place a new piece on the board after a move
void gomokuBoard::place(int playerNum, unsigned row, unsigned col)
{
	if (row >= size || col >= size || (playerNum != 1 && playerNum != -1)) {
		cout << "Error!" << endl;
		return;
	}

	board[row][col] = playerNum;
}

// Check if any player has won the match, return 1 or -1 for player 1 or 2
// Return 0 if game is not over
int gomokuBoard::checkWin()
{
	for (unsigned i = 0; i < size; i++) {
		for (unsigned j = 0; j < size; j++) {
			int cellResult = checkCell(i, j);
			if (cellResult != 0) {
				return cellResult;
			}
		}
	}

	return 0;
}

// Check if there is a winning pattern from a certain cell
// Return 1 or -1 for player 1 or 2 if someone has won
// Return 0 if not
int gomokuBoard::checkCell(unsigned row, unsigned col) {
	// Check the row
	if (col <= size - 5) {
		if (board[row][col + 1] == board[row][col] &&
			board[row][col + 2] == board[row][col] &&
			board[row][col + 3] == board[row][col] &&
			board[row][col + 4] == board[row][col]) {
			return board[row][col];
		}
	}

	// Check the column
	if (row <= size - 5) {
		if (board[row + 1][col] == board[row][col] &&
			board[row + 2][col] == board[row][col] &&
			board[row + 3][col] == board[row][col] &&
			board[row + 4][col] == board[row][col]) {
			return board[row][col];
		}
	}

	// Check the diagonal
	if (row <= size - 5 && col <= size - 5) {
		if (board[row + 1][col + 1] == board[row][col] &&
			board[row + 2][col + 2] == board[row][col] &&
			board[row + 3][col + 3] == board[row][col] &&
			board[row + 4][col + 4] == board[row][col]) {
			return board[row][col];
		}
	}

	return 0;
}

void gomokuBoard::printBoard()
{
	for (unsigned i = 0; i < size; i++) {
		for (unsigned j = 0; j < size; j++) {
			if (board[i][j] == 0) {
				cout << ".";
			} else if (board[i][j] == -1) {
				cout << "x";
			} else {
				cout << "o";
			}
		}
		cout << endl;
	}
}

void gomokuBoard::setEmpty(bool newVal)
{
	isEmpty = newVal;
}

bool gomokuBoard::empty()
{
	return isEmpty;
}

unsigned gomokuBoard::getSize()
{
	return size;
}

int gomokuBoard::getCellVal(unsigned row, unsigned col)
{
	if (row >= size || col >= size) {
		cout << "Out of bound" << endl;
		return - 1;
	}

	return board[row][col];
}