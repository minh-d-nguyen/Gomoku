#include<iostream>
#include<vector>
#include "gomokuBoard.h"
using namespace std;

class gomokuAI
{
public:
	void makeMoveDef(int playerNum);
	// void makeMoveMinimax();
	void printBoard();
private:
	gomokuBoard board;
	unsigned moveScore(int playerNum, unsigned row, unsigned col);
	unsigned checkBorder(unsigned row, unsigned col);
	unsigned checkDefense(int playerNum, unsigned row, unsigned col);
	unsigned checkOffense(int playerNUm, unsigned row, unsigned col);
};