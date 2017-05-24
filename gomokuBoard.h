#include<iostream>
#include<vector>
using namespace std;

class gomokuBoard {
public:
	int checkWin();
	void place(int playerNum, unsigned row, unsigned col);
	unsigned gomokuBoard::getSize();
	void printBoard();
	bool empty();
	void setEmpty(bool newVal);
	unsigned getSize();
	int getCellVal(unsigned row, unsigned col);
	gomokuBoard();
	gomokuBoard(unsigned s);
	~gomokuBoard();
private:
	int *board;
	unsigned size;
	int checkCell(unsigned row, unsigned col);
	bool isEmpty;
}