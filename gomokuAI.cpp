#include<iostream>
#include<vector>
#include "gomokuAI.h"
using namespace std;

gomokuAI::gomokuAI()
{
	cellScore.resize(15);
	for (unsigned i = 0; i < 15; i++) {
		cellScore[i].resize(15);
	}

	for (unsigned i = 0; i < 15; i++) {
		for (unsigned j = 0; j < 15; j++) {
			cellScore[i][j] = 0;
		}
	}
}

gomokuAI::~gomokuAI()
{

}

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

	for (unsigned i = 0; i < brdSize; i++) {
		for (unsigned j = 0; j < brdSize; j++) {
			unsigned currScore = moveScore(playerNum, i, j);
			if (currScore > maxScore) {
				maxScore = currScore;
				maxRow = i;
				maxCol = j;
			}
		}
	}

	cout << maxRow <<  " " << maxCol << " " << maxScore << endl;
	board.place(playerNum, maxRow, maxCol);
}

unsigned gomokuAI::moveScore(int playerNum, unsigned row, unsigned col)
{
	if (board.getCellVal(row, col) != 0) {
		return 0;
	}

	unsigned currScore = 0;

	currScore += checkBorder(row, col);
	currScore += checkDefense(playerNum, row, col);
	currScore += checkOffense(playerNum, row, col);

	cellScore[row][col] = currScore;

	return currScore;
}

unsigned gomokuAI::checkDefense(int playerNum, unsigned row, unsigned col)
{
	unsigned size = board.getSize();
	unsigned currScore = 0;
	unsigned defTwo = 20;
	unsigned defTwoBonus = 30;
	unsigned defThree = 40;
	unsigned defThreeBonus = 70;
	unsigned defFour = 240;
	unsigned defMid = 25;
	unsigned defMidBonus = 25;
	unsigned defFourMid = 60;
	unsigned defFourMidBonus = 70;

	int oppNum = -1;
	if (playerNum == -1) {
		oppNum = 1;
	}

	// Defense two
	if (row > 1) {
		if (board.getCellVal(row - 1, col) == oppNum && 
			board.getCellVal(row - 2, col) == oppNum) {
			currScore += defTwo;
			if (row > 2 && board.getCellVal(row - 3, col) == 0) {
				currScore += defTwoBonus;
			}
		}
	}

	if (row < size - 2) {
		if (board.getCellVal(row + 1, col) == oppNum && 
			board.getCellVal(row + 2, col) == oppNum) {
			currScore += defTwo;
			if (row < size - 3 && board.getCellVal(row + 3, col) == 0) {
				currScore += defTwoBonus;
			}
		}
	}

	if (col > 1) {
		if (board.getCellVal(row, col - 1) == oppNum && 
			board.getCellVal(row, col - 2) == oppNum) {
			currScore += defTwo;
			if (col > 2 && board.getCellVal(row, col - 3) == 0) {
				currScore += defTwoBonus;
			}
		}
	}

	if (col < size - 2) {
		if (board.getCellVal(row, col + 1) == oppNum && 
			board.getCellVal(row, col + 2) == oppNum) {
			currScore += defTwo;
			if (col < size - 3 && board.getCellVal(row, col + 3) == 0) {
				currScore += defTwoBonus;
			}
		}
	}

	if (row > 1 && col > 1) {
		if (board.getCellVal(row - 1, col - 1) == oppNum && 
			board.getCellVal(row - 2, col - 2) == oppNum) {
			currScore += defTwo;
			if (row > 2 && col > 2 && board.getCellVal(row - 3, col - 3) == 0) {
				currScore += defTwoBonus;
			}
		}
	}

	if (row > 1 && col < size - 2) {
		if (board.getCellVal(row - 1, col + 1) == oppNum && 
			board.getCellVal(row - 2, col + 2) == oppNum) {
			currScore += defTwo;
			if (row > 2 && col < size - 3 && board.getCellVal(row - 3, col + 3) == 0) {
				currScore += defTwoBonus;
			}
		}
	}

	if (row < size - 2 && col < size - 2) {
		if (board.getCellVal(row + 1, col + 1) == oppNum && 
			board.getCellVal(row + 2, col + 2) == oppNum) {
			currScore += defTwo;
			if (row < size - 3 && col < size - 3 && board.getCellVal(row + 3, col + 3) == 0) {
				currScore += defTwoBonus;
			}
		}
	}

	if (row < size - 2 && col > 1) {
		if (board.getCellVal(row + 1, col - 1) == oppNum && 
			board.getCellVal(row + 2, col - 2) == oppNum) {
			currScore += defTwo;
			if (row < size - 3 && col > 2 && board.getCellVal(row + 3, col - 3) == 0) {
				currScore += defTwoBonus;
			}
		}
	}

	// Defense three
	if (row > 2) {
		if (board.getCellVal(row - 1, col) == oppNum && 
			board.getCellVal(row - 2, col) == oppNum &&
			board.getCellVal(row - 3, col) == oppNum) {
			currScore += defThree;
			if (row > 3 && board.getCellVal(row - 4, col) == 0) {
				currScore += defThreeBonus;
			}
		}
	}

	if (row < size - 3) {
		if (board.getCellVal(row + 1, col) == oppNum && 
			board.getCellVal(row + 2, col) == oppNum &&
			board.getCellVal(row + 3, col) == oppNum) {
			currScore += defThree;
			if (row < size - 4 && board.getCellVal(row + 4, col) == 0) {
				currScore += defThreeBonus;
			}
		}
	}
	
	if (col > 2) {
		if (board.getCellVal(row, col - 1) == oppNum && 
			board.getCellVal(row, col - 2) == oppNum &&
			board.getCellVal(row, col - 3) == oppNum) {
			currScore += defThree;
			if (col > 3 && board.getCellVal(row, col - 4) == 0) {
				currScore += defThreeBonus;
			}
		}
	}
	
	if (col < size - 3) {
		if (board.getCellVal(row, col + 1) == oppNum && 
			board.getCellVal(row, col + 2) == oppNum &&
			board.getCellVal(row, col + 3) == oppNum) {
			currScore += defThree;
			if (col < size - 4 && board.getCellVal(row, col + 4) == 0) {
				currScore += defThreeBonus;
			}
		}
	}

	if (row > 2 && col > 2) {
		if (board.getCellVal(row - 1, col - 1) == oppNum && 
			board.getCellVal(row - 2, col - 2) == oppNum &&
			board.getCellVal(row - 3, col - 3) == oppNum) {
			currScore += defThree;
			if (row > 3 && col > 3 && board.getCellVal(row - 4, col - 4) == 0) {
				currScore += defThreeBonus;
			}
		}
	}

	if (row > 2 && col < size - 3) {
		if (board.getCellVal(row - 1, col + 1) == oppNum && 
			board.getCellVal(row - 2, col + 2) == oppNum &&
			board.getCellVal(row - 3, col + 3) == oppNum) {
			currScore += defThree;
			if (row > 3 && col < size - 4 && board.getCellVal(row - 4, col + 4) == 0) {
				currScore += defThreeBonus;
			}
		}
	}

	if (row < size - 3 && col > 2) {
		if (board.getCellVal(row + 1, col - 1) == oppNum && 
			board.getCellVal(row + 2, col - 2) == oppNum &&
			board.getCellVal(row + 3, col - 3) == oppNum) {
			currScore += defThree;
			if (row < size - 4 && col > 3 && board.getCellVal(row + 4, col - 4) == 0) {
				currScore += defThreeBonus;
			}
		}
	}

	if (row < size - 3 && col < size - 3) {
		if (board.getCellVal(row + 1, col + 1) == oppNum && 
			board.getCellVal(row + 2, col + 2) == oppNum &&
			board.getCellVal(row + 3, col + 3) == oppNum) {
			currScore += defThree;
			if (row < size - 4 && col < size - 4 && board.getCellVal(row + 4, col + 4) == 0) {
				currScore += defThreeBonus;
			}
		}
	}

	// Defense four
	if (row > 3) {
		if (board.getCellVal(row - 1, col) == oppNum && 
			board.getCellVal(row - 2, col) == oppNum &&
			board.getCellVal(row - 3, col) == oppNum &&
			board.getCellVal(row - 4, col) == oppNum) {
			currScore += defFour;
		}
	}

	if (row < size - 4) {
		if (board.getCellVal(row + 1, col) == oppNum && 
			board.getCellVal(row + 2, col) == oppNum &&
			board.getCellVal(row + 3, col) == oppNum &&
			board.getCellVal(row + 4, col) == oppNum) {
			currScore += defFour;
		}
	}

	if (col > 3) {
		if (board.getCellVal(row, col - 1) == oppNum && 
			board.getCellVal(row, col - 2) == oppNum &&
			board.getCellVal(row, col - 3) == oppNum &&
			board.getCellVal(row, col - 4) == oppNum) {
			currScore += defFour;
		}
	}

	if (col < size - 4) {
		if (board.getCellVal(row, col + 1) == oppNum && 
			board.getCellVal(row, col + 2) == oppNum &&
			board.getCellVal(row, col + 3) == oppNum &&
			board.getCellVal(row, col + 4) == oppNum) {
			currScore += defFour;
		}
	}

	if (row < size - 4 && col < size - 4) {
		if (board.getCellVal(row + 1, col + 1) == oppNum && 
			board.getCellVal(row + 2, col + 2) == oppNum &&
			board.getCellVal(row + 3, col + 3) == oppNum &&
			board.getCellVal(row + 4, col + 4) == oppNum) {
			currScore += defFour;
		}
	}

	if (row > 3 && col < size - 4) {
		if (board.getCellVal(row - 1, col + 1) == oppNum && 
			board.getCellVal(row - 2, col + 2) == oppNum &&
			board.getCellVal(row - 3, col + 3) == oppNum &&
			board.getCellVal(row - 4, col + 4) == oppNum) {
			currScore += defFour;
		}
	}

	if (row < size - 4 && col > 3) {
		if (board.getCellVal(row + 1, col - 1) == oppNum && 
			board.getCellVal(row + 2, col - 2) == oppNum &&
			board.getCellVal(row + 3, col - 3) == oppNum &&
			board.getCellVal(row + 4, col - 4) == oppNum) {
			currScore += defFour;
		}
	}

	if (row > 3 && col > 3) {
		if (board.getCellVal(row - 1, col - 1) == oppNum && 
			board.getCellVal(row - 2, col - 2) == oppNum &&
			board.getCellVal(row - 3, col - 3) == oppNum &&
			board.getCellVal(row - 4, col - 4) == oppNum) {
			currScore += defFour;
		}
	}

	// Defense Mid 3
	if (row < size - 1 && row > 0) {
		if (board.getCellVal(row - 1, col) == oppNum && 
			board.getCellVal(row + 1, col) == oppNum) {
			if (row > 1 && board.getCellVal(row - 2, col) == 0) {
				currScore += defMid;
				if (row < size - 2 && board.getCellVal(row + 2, col) == 0) {
					currScore += defMidBonus;
				}
			}
		}
	}

	if (col < size - 1 && col > 0) {
		if (board.getCellVal(row, col - 1) == oppNum && 
			board.getCellVal(row, col + 1) == oppNum) {
			if (col > 1 && board.getCellVal(row, col - 2) == 0) {
				currScore += defMid;
				if (col < size - 2 && board.getCellVal(row, col + 2) == 0) {
					currScore += defMidBonus;
				}
			}
		}
	}

	if (col < size - 1 && col > 0 && row < size - 1 && row > 0) {
		if (board.getCellVal(row - 1, col - 1) == oppNum && 
			board.getCellVal(row + 1, col + 1) == oppNum) {
			if (col > 1 && row > 1 && board.getCellVal(row - 2, col - 2) == 0) {
				currScore += defMid;
				if (col < size - 2 && row < size - 2 && board.getCellVal(row + 2, col + 2) == 0) {
					currScore += defMidBonus;
				}
			}
		}

		if (board.getCellVal(row - 1, col + 1) == oppNum && 
			board.getCellVal(row + 1, col - 1) == oppNum) {
			if (col > 1 && row < size - 2 && board.getCellVal(row + 2, col - 2) == 0) {
				currScore += defMid;
				if (col < size - 2 && row > 1 && board.getCellVal(row - 2, col + 2) == 0) {
					currScore += defMidBonus;
				}
			}
		}
	}

	// Defense Mid 4
	if (row > 0 && row < size - 2) {
		if (board.getCellVal(row - 1, col) == oppNum && 
			board.getCellVal(row + 1, col) == oppNum &&
			board.getCellVal(row + 2, col) == oppNum) {
			if (row > 1 && board.getCellVal(row - 2, col) != playerNum) {
				currScore += defFourMid;
				if (row < size - 3 && board.getCellVal(row + 3, col) != playerNum) {
					currScore += defFourMidBonus;
				}
			}

			else if (row < size - 3 && board.getCellVal(row + 3, col) != playerNum) {
				currScore += defFourMid;
				if (row > 1 && board.getCellVal(row - 2, col) != playerNum) {
					currScore += defFourMidBonus;
				}
			}
		}
	}

	if (row > 1 && row < size - 1) {
		if (board.getCellVal(row - 1, col) == oppNum && 
			board.getCellVal(row + 1, col) == oppNum &&
			board.getCellVal(row - 2, col) == oppNum) {
			if (row < size - 2 && board.getCellVal(row + 2, col) != playerNum) {
				currScore += defFourMid;
				if (row > 2 && board.getCellVal(row - 3, col) != playerNum) {
					currScore += defFourMidBonus;
				}
			}

			else if (row > 2 && board.getCellVal(row - 3, col) != playerNum) {
				currScore += defFourMid;
				if (row < size - 2 && board.getCellVal(row + 2, col) != playerNum) {
					currScore += defFourMidBonus;
				}
			}
		}
	}

	if (row > 0 && row < size - 2) {
		if (board.getCellVal(row - 1, col) == oppNum && 
			board.getCellVal(row + 1, col) == oppNum &&
			board.getCellVal(row + 2, col) == oppNum) {
			if (row > 1 && board.getCellVal(row - 2, col) != playerNum) {
				currScore += defFourMid;
				if (row < size - 3 && board.getCellVal(row + 3, col) != playerNum) {
					currScore += defFourMidBonus;
				}
			}

			else if (row < size - 3 && board.getCellVal(row + 3, col) != playerNum) {
				currScore += defFourMid;
				if (row > 1 && board.getCellVal(row - 2, col) != playerNum) {
					currScore += defFourMidBonus;
				}
			}
		}
	}

	if (col > 1 && col < size - 1) {
		if (board.getCellVal(row, col - 1) == oppNum && 
			board.getCellVal(row + 1, col + 1) == oppNum &&
			board.getCellVal(row - 2, col - 2) == oppNum) {
			if (col < size - 2 && board.getCellVal(row, col + 2) != playerNum) {
				currScore += defFourMid;
				if (col > 2 && board.getCellVal(row, col - 3) != playerNum) {
					currScore += defFourMidBonus;
				}
			}

			else if (col > 2 && board.getCellVal(row, col - 3) != playerNum) {
				currScore += defFourMid;
				if (col < size - 2 && board.getCellVal(row, col + 2) != playerNum) {
					currScore += defFourMidBonus;
				}
			}
		}
	}

	if (col > 0 && col < size - 2) {
		if (board.getCellVal(row, col - 1) == oppNum && 
			board.getCellVal(row, col + 1) == oppNum &&
			board.getCellVal(row, col + 2) == oppNum) {
			if (col > 1 && board.getCellVal(row, col - 2) != playerNum) {
				currScore += defFourMid;
				if (col < size - 3 && board.getCellVal(row, col + 3) != playerNum) {
					currScore += defFourMidBonus;
				}
			}

			else if (col < size - 3 && board.getCellVal(row, col + 3) != playerNum) {
				currScore += defFourMid;
				if (col > 1 && board.getCellVal(row, col - 2) != playerNum) {
					currScore += defFourMidBonus;
				}
			}
		}
	}

	if (col > 0 && row > 0 && col < size - 2 && row < size - 2) {
		if (board.getCellVal(row - 1, col - 1) == oppNum && 
			board.getCellVal(row + 1, col + 1) == oppNum &&
			board.getCellVal(row + 2, col + 2) == oppNum) {
			if (col > 1 && row > 1 && board.getCellVal(row - 2, col - 2) != playerNum) {
				currScore += defFourMid;
				if (col < size - 3 && row < size - 3 && 
					board.getCellVal(row + 3, col + 3) != playerNum) {
					currScore += defFourMidBonus;
				}
			}

			else if (col < size - 3 && row < size - 3 && 
					 board.getCellVal(row + 3, col + 3) != playerNum) {
				currScore += defFourMid;
				if (col > 1 && row > 1 && board.getCellVal(row - 2, col - 2) != playerNum) {
					currScore += defFourMidBonus;
				}
			}
		}
	}

	if (col > 1 && row > 1 && col < size - 1 && row < size - 1) {
		if (board.getCellVal(row - 1, col - 1) == oppNum && 
			board.getCellVal(row + 1, col + 1) == oppNum &&
			board.getCellVal(row - 2, col - 2) == oppNum) {
			if (col > 2 && row > 2 && board.getCellVal(row - 3, col - 3) != playerNum) {
				currScore += defFourMid;
				if (col < size - 2 && row < size - 2 && 
					board.getCellVal(row + 2, col + 2) != playerNum) {
					currScore += defFourMidBonus;
				}
			}

			else if (col < size - 2 && row < size - 2 && 
					 board.getCellVal(row + 2, col + 2) != playerNum) {
				currScore += defFourMid;
				if (col > 2 && row > 2 && board.getCellVal(row - 3, col - 3) != playerNum) {
					currScore += defFourMidBonus;
				}
			}
		}
	}

	if (col > 1 && row > 0 && col < size - 1 && row < size - 2) {
		if (board.getCellVal(row - 1, col + 1) == oppNum && 
			board.getCellVal(row + 1, col - 1) == oppNum &&
			board.getCellVal(row + 2, col - 2) == oppNum) {
			if (col > 2 && row < size - 3 && 
				board.getCellVal(row + 3, col - 3) != playerNum) {
				currScore += defFourMid;
				if (col < size - 2 && row > 1 && 
					board.getCellVal(row - 2, col + 2) != playerNum) {
					currScore += defFourMidBonus;
				}
			}

			else if (col < size - 2 && row > 1 && 
					 board.getCellVal(row - 2, col + 2) != playerNum) {
				currScore += defFourMid;
				if (col > 2 && row < size - 3 && 
					board.getCellVal(row + 3, col - 3) != playerNum) {
					currScore += defFourMidBonus;
				}
			}
		}
	}

	if (row > 1 && col > 0 && row < size - 1 && col < size - 2) {
		if (board.getCellVal(row + 1, col - 1) == oppNum && 
			board.getCellVal(row - 1, col + 1) == oppNum &&
			board.getCellVal(row - 2, col + 2) == oppNum) {
			if (row > 2 && col < size - 3 && 
				board.getCellVal(row - 3, col + 3) != playerNum) {
				currScore += defFourMid;
				if (row < size - 2 && col > 1 && 
					board.getCellVal(row + 2, col - 2) != playerNum) {
					currScore += defFourMidBonus;
				}
			}

			else if (row < size - 2 && col > 1 && 
					 board.getCellVal(row + 2, col - 2) != playerNum) {
				currScore += defFourMid;
				if (row > 2 && col < size - 3 && 
					board.getCellVal(row - 3, col + 3) != playerNum) {
					currScore += defFourMidBonus;
				}
			}
		}
	}

	return currScore;
}

unsigned gomokuAI::checkOffense(int playerNum, unsigned row, unsigned col)
{
	unsigned size = board.getSize();
	unsigned currScore = 0;
	unsigned offTwo = 16;
	unsigned offTwoBonus = 30;
	unsigned offThree = 36;
	unsigned offThreeBonus = 90;
	unsigned offFour = 300;
	unsigned offMid = 10;
	unsigned offMidBonus = 30;
	unsigned offFourMid = 60;
	unsigned offFourMidBonus = 90;

	int oppNum = -1;
	if (playerNum == -1) {
		oppNum = 1;
	}

	// Offense two
	if (row > 1) {
		if (board.getCellVal(row - 1, col) == playerNum && 
			board.getCellVal(row - 2, col) == playerNum) {
			currScore += offTwo;
			if (row > 2 && board.getCellVal(row - 3, col) == 0) {
				currScore += offTwoBonus;
			}
		}
	}

	if (row < size - 2) {
		if (board.getCellVal(row + 1, col) == playerNum && 
			board.getCellVal(row + 2, col) == playerNum) {
			currScore += offTwo;
			if (row < size - 3 && board.getCellVal(row + 3, col) == 0) {
				currScore += offTwoBonus;
			}
		}
	}

	if (col > 1) {
		if (board.getCellVal(row, col - 1) == playerNum && 
			board.getCellVal(row, col - 2) == playerNum) {
			currScore += offTwo;
			if (col > 2 && board.getCellVal(row, col - 3) == 0) {
				currScore += offTwoBonus;
			}
		}
	}

	if (col < size - 2) {
		if (board.getCellVal(row, col + 1) == playerNum && 
			board.getCellVal(row, col + 2) == playerNum) {
			currScore += offTwo;
			if (col < size - 3 && board.getCellVal(row, col + 3) == 0) {
				currScore += offTwoBonus;
			}
		}
	}

	if (row > 1 && col > 1) {
		if (board.getCellVal(row - 1, col - 1) == playerNum && 
			board.getCellVal(row - 2, col - 2) == playerNum) {
			currScore += offTwo;
			if (row > 2 && col > 2 && board.getCellVal(row - 3, col - 3) == 0) {
				currScore += offTwoBonus;
			}
		}
	}

	if (row > 1 && col < size - 2) {
		if (board.getCellVal(row - 1, col + 1) == playerNum && 
			board.getCellVal(row - 2, col + 2) == playerNum) {
			currScore += offTwo;
			if (row > 2 && col < size - 3 && board.getCellVal(row - 3, col + 3) == 0) {
				currScore += offTwoBonus;
			}
		}
	}

	if (row < size - 2 && col < size - 2) {
		if (board.getCellVal(row + 1, col + 1) == playerNum && 
			board.getCellVal(row + 2, col + 2) == playerNum) {
			currScore += offTwo;
			if (row < size - 3 && col < size - 3 && board.getCellVal(row + 3, col + 3) == 0) {
				currScore += offTwoBonus;
			}
		}
	}

	if (row < size - 2 && col > 1) {
		if (board.getCellVal(row + 1, col - 1) == playerNum && 
			board.getCellVal(row + 2, col - 2) == playerNum) {
			currScore += offTwo;
			if (row < size - 3 && col > 2 && board.getCellVal(row + 3, col - 3) == 0) {
				currScore += offTwoBonus;
			}
		}
	}

	// Offense three
	if (row > 2) {
		if (board.getCellVal(row - 1, col) == playerNum && 
			board.getCellVal(row - 2, col) == playerNum &&
			board.getCellVal(row - 3, col) == playerNum) {
			currScore += offThree;
			if (row > 3 && board.getCellVal(row - 4, col) == 0) {
				currScore += offThreeBonus;
			}
		}
	}

	if (row < size - 3) {
		if (board.getCellVal(row + 1, col) == playerNum && 
			board.getCellVal(row + 2, col) == playerNum &&
			board.getCellVal(row + 3, col) == playerNum) {
			currScore += offThree;
			if (row < size - 4 && board.getCellVal(row + 4, col) == 0) {
				currScore += offThreeBonus;
			}
		}
	}
	
	if (col > 2) {
		if (board.getCellVal(row, col - 1) == playerNum && 
			board.getCellVal(row, col - 2) == playerNum &&
			board.getCellVal(row, col - 3) == playerNum) {
			currScore += offThree;
			if (col > 3 && board.getCellVal(row, col - 4) == 0) {
				currScore += offThreeBonus;
			}
		}
	}
	
	if (col < size - 3) {
		if (board.getCellVal(row, col + 1) == playerNum && 
			board.getCellVal(row, col + 2) == playerNum &&
			board.getCellVal(row, col + 3) == playerNum) {
			currScore += offThree;
			if (col < size - 4 && board.getCellVal(row, col + 4) == 0) {
				currScore += offThreeBonus;
			}
		}
	}

	if (row > 2 && col > 2) {
		if (board.getCellVal(row - 1, col - 1) == playerNum && 
			board.getCellVal(row - 2, col - 2) == playerNum &&
			board.getCellVal(row - 3, col - 3) == playerNum) {
			currScore += offThree;
			if (row > 3 && col > 3 && board.getCellVal(row - 4, col - 4) == 0) {
				currScore += offThreeBonus;
			}
		}
	}

	if (row > 2 && col < size - 3) {
		if (board.getCellVal(row - 1, col + 1) == playerNum && 
			board.getCellVal(row - 2, col + 2) == playerNum &&
			board.getCellVal(row - 3, col + 3) == playerNum) {
			currScore += offThree;
			if (row > 3 && col < size - 4 && board.getCellVal(row - 4, col + 4) == 0) {
				currScore += offThreeBonus;
			}
		}
	}

	if (row < size - 3 && col > 2) {
		if (board.getCellVal(row + 1, col - 1) == playerNum && 
			board.getCellVal(row + 2, col - 2) == playerNum &&
			board.getCellVal(row + 3, col - 3) == playerNum) {
			currScore += offThree;
			if (row < size - 4 && col > 3 && board.getCellVal(row + 4, col - 4) == 0) {
				currScore += offThreeBonus;
			}
		}
	}

	if (row < size - 3 && col < size - 3) {
		if (board.getCellVal(row + 1, col + 1) == playerNum && 
			board.getCellVal(row + 2, col + 2) == playerNum &&
			board.getCellVal(row + 3, col + 3) == playerNum) {
			currScore += offThree;
			if (row < size - 4 && col < size - 4 && board.getCellVal(row + 4, col + 4) == 0) {
				currScore += offThreeBonus;
			}
		}
	}

	// Offense four
	if (row > 3) {
		if (board.getCellVal(row - 1, col) == playerNum && 
			board.getCellVal(row - 2, col) == playerNum &&
			board.getCellVal(row - 3, col) == playerNum &&
			board.getCellVal(row - 4, col) == playerNum) {
			currScore += offFour;
		}
	}

	if (row < size - 4) {
		if (board.getCellVal(row + 1, col) == playerNum && 
			board.getCellVal(row + 2, col) == playerNum &&
			board.getCellVal(row + 3, col) == playerNum &&
			board.getCellVal(row + 4, col) == playerNum) {
			currScore += offFour;
		}
	}

	if (col > 3) {
		if (board.getCellVal(row, col - 1) == playerNum && 
			board.getCellVal(row, col - 2) == playerNum &&
			board.getCellVal(row, col - 3) == playerNum &&
			board.getCellVal(row, col - 4) == playerNum) {
			currScore += offFour;
		}
	}

	if (col < size - 4) {
		if (board.getCellVal(row, col + 1) == playerNum && 
			board.getCellVal(row, col + 2) == playerNum &&
			board.getCellVal(row, col + 3) == playerNum &&
			board.getCellVal(row, col + 4) == playerNum) {
			currScore += offFour;
		}
	}

	if (col < size - 4 && row < size - 4) {
		if (board.getCellVal(row + 1, col + 1) == playerNum && 
			board.getCellVal(row + 2, col + 2) == playerNum &&
			board.getCellVal(row + 3, col + 3) == playerNum &&
			board.getCellVal(row + 4, col + 4) == playerNum) {
			currScore += offFour;
		}
	}

	if (col > 3 && row > 3) {
		if (board.getCellVal(row - 1, col - 1) == playerNum && 
			board.getCellVal(row - 2, col - 2) == playerNum &&
			board.getCellVal(row - 3, col - 3) == playerNum &&
			board.getCellVal(row - 4, col - 4) == playerNum) {
			currScore += offFour;
		}
	}

	if (col > 3 && row < size - 4) {
		if (board.getCellVal(row + 1, col - 1) == playerNum && 
			board.getCellVal(row + 2, col - 2) == playerNum &&
			board.getCellVal(row + 3, col - 3) == playerNum &&
			board.getCellVal(row + 4, col - 4) == playerNum) {
			currScore += offFour;
		}
	}

	if (col < size - 4 && row > 3) {
		if (board.getCellVal(row - 1, col + 1) == playerNum && 
			board.getCellVal(row - 2, col + 2) == playerNum &&
			board.getCellVal(row - 3, col + 3) == playerNum &&
			board.getCellVal(row - 4, col + 4) == playerNum) {
			currScore += offFour;
		}
	}

	// Offense Mid 3
	if (row < size - 1 && row > 0) {
		if (board.getCellVal(row - 1, col) == playerNum && 
			board.getCellVal(row + 1, col) == playerNum) {
			if (row > 1 && board.getCellVal(row - 2, col) == 0) {
				currScore += offMid;
				if (row < size - 2 && board.getCellVal(row + 2, col) == 0) {
					currScore += offMidBonus;
				}
			}
		}
	}

	if (col < size - 1 && col > 0) {
		if (board.getCellVal(row, col - 1) == playerNum && 
			board.getCellVal(row, col + 1) == playerNum) {
			if (col > 1 && board.getCellVal(row, col - 2) == 0) {
				currScore += offMid;
				if (col < size - 2 && board.getCellVal(row, col + 2) == 0) {
					currScore += offMidBonus;
				}
			}
		}
	}

	if (col < size - 1 && col > 0 && row < size - 1 && row > 0) {
		if (board.getCellVal(row - 1, col - 1) == playerNum && 
			board.getCellVal(row + 1, col + 1) == playerNum) {
			if (col > 1 && row > 1 && board.getCellVal(row - 2, col - 2) == 0) {
				currScore += offMid;
				if (col < size - 2 && row < size - 2 && board.getCellVal(row + 2, col + 2) == 0) {
					currScore += offMidBonus;
				}
			}
		}

		if (board.getCellVal(row - 1, col + 1) == playerNum && 
			board.getCellVal(row + 1, col - 1) == playerNum) {
			if (col > 1 && row < size - 2 && board.getCellVal(row + 2, col - 2) == 0) {
				currScore += offMid;
				if (col < size - 2 && row > 1 && board.getCellVal(row - 2, col + 2) == 0) {
					currScore += offMidBonus;
				}
			}
		}
	}

	// Offense Mid 4
	if (row > 0 && row < size - 2) {
		if (board.getCellVal(row - 1, col) == playerNum && 
			board.getCellVal(row + 1, col) == playerNum &&
			board.getCellVal(row + 2, col) == playerNum) {
			if (row > 1 && board.getCellVal(row - 2, col) != oppNum) {
				currScore += offFourMid;
				if (row < size - 3 && board.getCellVal(row + 3, col) != oppNum) {
					currScore += offFourMidBonus;
				}
			}

			else if (row < size - 3 && board.getCellVal(row + 3, col) != oppNum) {
				currScore += offFourMid;
				if (row > 1 && board.getCellVal(row - 2, col) != oppNum) {
					currScore += offFourMidBonus;
				}
			}
		}
	}

	if (row > 1 && row < size - 1) {
		if (board.getCellVal(row - 1, col) == playerNum && 
			board.getCellVal(row + 1, col) == playerNum &&
			board.getCellVal(row - 2, col) == playerNum) {
			if (row < size - 2 && board.getCellVal(row + 2, col) != oppNum) {
				currScore += offFourMid;
				if (row > 2 && board.getCellVal(row - 3, col) != oppNum) {
					currScore += offFourMidBonus;
				}
			}

			else if (row > 2 && board.getCellVal(row - 3, col) != oppNum) {
				currScore += offFourMid;
				if (row < size - 2 && board.getCellVal(row + 2, col) != oppNum) {
					currScore += offFourMidBonus;
				}
			}
		}
	}

	if (row > 0 && row < size - 2) {
		if (board.getCellVal(row - 1, col) == playerNum && 
			board.getCellVal(row + 1, col) == playerNum &&
			board.getCellVal(row + 2, col) == playerNum) {
			if (row > 1 && board.getCellVal(row - 2, col) != oppNum) {
				currScore += offFourMid;
				if (row < size - 3 && board.getCellVal(row + 3, col) != oppNum) {
					currScore += offFourMidBonus;
				}
			}

			else if (row < size - 3 && board.getCellVal(row + 3, col) != oppNum) {
				currScore += offFourMid;
				if (row > 1 && board.getCellVal(row - 2, col) != oppNum) {
					currScore += offFourMidBonus;
				}
			}
		}
	}

	if (col > 1 && col < size - 1) {
		if (board.getCellVal(row, col - 1) == playerNum && 
			board.getCellVal(row + 1, col + 1) == playerNum &&
			board.getCellVal(row - 2, col - 2) == playerNum) {
			if (col < size - 2 && board.getCellVal(row, col + 2) != oppNum) {
				currScore += offFourMid;
				if (col > 2 && board.getCellVal(row, col - 3) != oppNum) {
					currScore += offFourMidBonus;
				}
			}

			else if (col > 2 && board.getCellVal(row, col - 3) != oppNum) {
				currScore += offFourMid;
				if (col < size - 2 && board.getCellVal(row, col + 2) != oppNum) {
					currScore += offFourMidBonus;
				}
			}
		}
	}

	if (col > 0 && col < size - 2) {
		if (board.getCellVal(row, col - 1) == playerNum && 
			board.getCellVal(row, col + 1) == playerNum &&
			board.getCellVal(row, col + 2) == playerNum) {
			if (col > 1 && board.getCellVal(row, col - 2) != oppNum) {
				currScore += offFourMid;
				if (col < size - 3 && board.getCellVal(row, col + 3) != oppNum) {
					currScore += offFourMidBonus;
				}
			}

			else if (col < size - 3 && board.getCellVal(row, col + 3) != oppNum) {
				currScore += offFourMid;
				if (col > 1 && board.getCellVal(row, col - 2) != oppNum) {
					currScore += offFourMidBonus;
				}
			}
		}
	}

	if (col > 0 && row > 0 && col < size - 2 && row < size - 2) {
		if (board.getCellVal(row - 1, col - 1) == playerNum && 
			board.getCellVal(row + 1, col + 1) == playerNum &&
			board.getCellVal(row + 2, col + 2) == playerNum) {
			if (col > 1 && row > 1 && board.getCellVal(row - 2, col - 2) != oppNum) {
				currScore += offFourMid;
				if (col < size - 3 && row < size - 3 && 
					board.getCellVal(row + 3, col + 3) != oppNum) {
					currScore += offFourMidBonus;
				}
			}

			else if (col < size - 3 && row < size - 3 && 
					 board.getCellVal(row + 3, col + 3) != oppNum) {
				currScore += offFourMid;
				if (col > 1 && row > 1 && board.getCellVal(row - 2, col - 2) != oppNum) {
					currScore += offFourMidBonus;
				}
			}
		}
	}

	if (col > 1 && row > 1 && col < size - 1 && row < size - 1) {
		if (board.getCellVal(row - 1, col - 1) == playerNum && 
			board.getCellVal(row + 1, col + 1) == playerNum &&
			board.getCellVal(row - 2, col - 2) == playerNum) {
			if (col > 2 && row > 2 && board.getCellVal(row - 3, col - 3) != oppNum) {
				currScore += offFourMid;
				if (col < size - 2 && row < size - 2 && 
					board.getCellVal(row + 2, col + 2) != oppNum) {
					currScore += offFourMidBonus;
				}
			}

			else if (col < size - 2 && row < size - 2 && 
					 board.getCellVal(row + 2, col + 2) != oppNum) {
				currScore += offFourMid;
				if (col > 2 && row > 2 && board.getCellVal(row - 3, col - 3) != oppNum) {
					currScore += offFourMidBonus;
				}
			}
		}
	}

	if (col > 1 && row > 0 && col < size - 1 && row < size - 2) {
		if (board.getCellVal(row - 1, col + 1) == playerNum && 
			board.getCellVal(row + 1, col - 1) == playerNum &&
			board.getCellVal(row + 2, col - 2) == playerNum) {
			if (col > 2 && row < size - 3 && 
				board.getCellVal(row + 3, col - 3) != oppNum) {
				currScore += offFourMid;
				if (col < size - 2 && row > 1 && 
					board.getCellVal(row - 2, col + 2) != oppNum) {
					currScore += offFourMidBonus;
				}
			}

			else if (col < size - 2 && row > 1 && 
					 board.getCellVal(row - 2, col + 2) != oppNum) {
				currScore += offFourMid;
				if (col > 2 && row < size - 3 && 
					board.getCellVal(row + 3, col - 3) != oppNum) {
					currScore += offFourMidBonus;
				}
			}
		}
	}

	if (row > 1 && col > 0 && row < size - 1 && col < size - 2) {
		if (board.getCellVal(row + 1, col - 1) == playerNum && 
			board.getCellVal(row - 1, col + 1) == playerNum &&
			board.getCellVal(row - 2, col + 2) == playerNum) {
			if (row > 2 && col < size - 3 && 
				board.getCellVal(row - 3, col + 3) != oppNum) {
				currScore += offFourMid;
				if (row < size - 2 && col > 1 && 
					board.getCellVal(row + 2, col - 2) != oppNum) {
					currScore += offFourMidBonus;
				}
			}

			else if (row < size - 2 && col > 1 && 
					 board.getCellVal(row + 2, col - 2) != oppNum) {
				currScore += offFourMid;
				if (row > 2 && col < size - 3 && 
					board.getCellVal(row - 3, col + 3) != oppNum) {
					currScore += offFourMidBonus;
				}
			}
		}
	}

	return currScore;
}

unsigned gomokuAI::checkBorder(unsigned row, unsigned col)
{
	unsigned currScore = 0;
	unsigned size = board.getSize();

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

void gomokuAI::printScore()
{
	for (unsigned i = 0; i < cellScore.size(); i++) {
		for (unsigned j = 0; j < cellScore[i].size(); j++) {
			cout << cellScore[i][j] << " ";
		}
		cout << endl;
	}
}

void gomokuAI::playerPlace(int playerNum, unsigned row, unsigned col)
{
	board.place(playerNum, row, col);
}

int gomokuAI::checkWin()
{
	return board.checkWin();
}