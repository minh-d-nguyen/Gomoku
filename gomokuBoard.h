#include<iostream>
#include<vector>
using namespace std;

class gomokuBoard {
public:
	int checkWin();
	void place(int playerNum, unsigned row, unsigned col);
	gomokuBoard();
	gomokuBoard(unsigned s);
	~gomokuBoard();
private:
	int *board;
	unsigned size;
}