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
	unsigned currScore = 0;
	unsigned defTwo = 20;
	unsigned defTwoBonus = 30;
	unsigned defThree = 40;
	unsigned defThreeBonus = 70;
	unsigned defFour = 200;
	unsigned defMid = 10;
	unsigned defMidBonus = 40;
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
				if (col < size - 2 && board.getCellVal(row, col + 2) == 0) {
					currScore += defMidBonus;
				}
			}
		}

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