#include<iostream>
#include<vector>
#include "gomokuAI.h"
using namespace std;

void gomokuAI::printBoard()
{
	board.printBoard();
}

void gomokuAI::makeMoveDef(int playerNum)
{
	unsigned maxScore = 0;
	unsigned maxRow = -1;
	unsigned maxCol = -1;
	unsigned brdSize = board.getSize();

	if (board.empty()) {
		unsigned mid = brdSize/2 + 1;
		board.place(playerNum, mid, mid);
		board.setEmpty(false);
		return;
	}

	for (int i = 0; i < brdSize; i++) {
		for (int j = 0; j < brdSize; j++) {
			unsigned currScore = moveScore(i, j);
			if (currScore > maxScore) {
				maxScore = currScore;
				maxRow = i;
				maxCol = j;
			}
		}
	}

	board.place(playerNum, maxRow, maxCol);
}

unsigned gomokuAI::moveScore(int playerNum, unsigned row, unsigned col)
{
	if (board.getCellVal(row, col) != 0) {
		return -1;
	}

	unsigned currScore = 0;

	currScore += checkBorder(row, col);
	currScore += checkDefense(playerNum, row, col);
}

unsigned gomokuAI::checkDefense(int playerNum, unsigned row, unsigned col)
{
	int oppNum = -1;
	if (playerNum == -1) {
		oppNum = 1;
	}
	
}

unsigned gomokuAI::checkBorder(unsigned row, unsigned col)
{
	unsigned currScore = 0;

	if (row > 0) {
		if (board.getCellVal(row - 1, col) != 0) {
			currScore += 1;
		}
	}

	if (col > 0) {
		if (board.getCellVal(row, col - 1) != 0) {
			currScore += 1;
		}
	}

	if (col < size - 1) {
		if (board.getCellVal(row, col + 1) != 0) {
			currScore += 1;
		}
	}

	if (row < size - 1) {
		if (board.getCellVal(row + 1, col) != 0) {
			currScore += 1;
		}
	}

	if (row > 0 && col > 0) {
		if (board.getCellVal(row - 1, col - 1) != 0) {
			currScore += 2;
		}
	}

	if (row > 0 && col < size - 1) {
		if (board.getCellVal(row - 1, col + 1) != 0) {
			currScore += 2;
		}
	}

	if (row < size - 1 && col > 0) {
		if (board.getCellVal(row + 1, col - 1) != 0) {
			currScore += 2;
		}
	}

	if (row < size - 1 && col < size - 1) {
		if (board.getCellVal(row + 1, col + 1) != 0) {
			currScore += 2;
		}
	}

	return currScore;
}