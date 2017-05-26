/* Main function for gomoku utilities testing */
#include<iostream>
#include<curses.h>
#include "gomokuBoard.h"
using namespace std;

int main()
{
	gomokuBoard board;
	int numRound = 0;
	while (true) {
		int playerNum = 1;
		int x, y;
		if (numRound % 2 == 0) {
			playerNum = -1;
		}
		cin >> x >> y;
		while (x > 14 || y > 14 || x < 0 || y < 0) {
			cout << "Error!" << endl;
			cin >> x >> y;
		}
		board.place(playerNum, (unsigned) x, (unsigned) y);
		cout << string(50, '\n');
		board.printBoard();
		numRound++;
	}
}