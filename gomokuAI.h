#include<iostream>
#include<vector>
#include "gomokuBoard.h"
using namespace std;

class gomokuAI
{
public:
	void makeMoveDef(int playerNum);
	void playerPlace(int playerNum, unsigned row, unsigned col);
	// void makeMoveMinimax();
	void printBoard();
	void printScore();
	int checkWin();
	gomokuAI();
	~gomokuAI();
private:
	gomokuBoard board;
	vector<vector<unsigned> > cellScore;
	unsigned moveScore(int playerNum, unsigned row, unsigned col);
	unsigned checkBorder(unsigned row, unsigned col);
	unsigned checkDefense(int playerNum, unsigned row, unsigned col);
	unsigned checkOffense(int playerNUm, unsigned row, unsigned col);
};