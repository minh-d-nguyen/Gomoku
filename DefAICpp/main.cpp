/* Main function for gomoku utilities testing */
#include<iostream>
#include "gomokuAI.h"
using namespace std;

int main()
{
	gomokuAI gomokuBot;
	int numRound = 0;
	bool win = false;

	while (!win) {
		int playerNum = 1;
		int x, y;
		char pause;
		if (numRound % 2 == 0) {
			playerNum = -1;
			cin >> x >> y;
			while (x > 14 || y > 14 || x < 0 || y < 0) {
				cout << "Error!" << endl;
				cin >> x >> y;
			}
			gomokuBot.playerPlace(playerNum, (unsigned) x, (unsigned) y);
			cout << string(50, '\n');
			gomokuBot.printBoard();
			cin >> pause;
		} else {
			playerNum = 1;
			gomokuBot.makeMoveDef(playerNum);
			gomokuBot.printScore();
			cout << string(50, '\n');
			gomokuBot.printBoard();
		}

		if (gomokuBot.checkWin() != 0) {
			if (gomokuBot.checkWin() == -1) {
				cout << "x wins!" << endl;
			} else {
				cout << "o wins!" << endl;
			}
			win = true;
		}

		numRound++;
	}
}