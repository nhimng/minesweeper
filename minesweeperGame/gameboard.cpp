#include "gameboard.h"
#include <iostream>
#include "helper.h"
#include <algorithm> 


gameboard::gameboard() {
	cursorRow = 0;
	cursorCol = 0;
	maxRow = 40;
	maxCol = 40;
	gameScreen = new char*[maxRow];
	for (int i = 0; i < maxRow; i++) {
		gameScreen[i] = new char[maxCol];
		for (int j = 0; j < maxCol; j++) {
			gameScreen[i][j] = ' ';
		}
	}
}
gameboard::gameboard(game* newgame) {
	gameptr = newgame;
	cursorRow = 0;
	cursorCol = 0;
	maxRow = 50;
	maxCol = 50;
	gameScreen = new char*[maxRow];
	for (int i = 0; i < std::min(gameptr->getMaxRow(),maxRow); i++) {
		gameScreen[i] = new char[maxCol];
		for (int j = 0; j < std::min(gameptr->getMaxCol(), maxCol); j++) {
			gameScreen[i][j] = gameptr->getValueAt(i,j);
		}
	}
}

void gameboard::clearGame() {
	for (int i = 0; i < maxRow; i++) {
		gameScreen[i] = new char[maxCol];
		for (int j = 0; j < maxCol; j++) {
			gameScreen[i][j] = ' ';
		}
	}
}

gameboard::~gameboard() {
	for (int i = 0; i < maxRow; i++) {
		delete[] gameScreen[i];
	}
	delete[] gameScreen;
}
void gameboard::newGame(game* newgame) {
	clearGame();
	gameptr = newgame;
	gameScreen = new char*[maxRow];
	for (int i = 0; i < std::min(gameptr->getMaxRow(), maxRow); i++) {
		gameScreen[i] = new char[maxCol];
		for (int j = 0; j < std::min(gameptr->getMaxCol(), maxCol); j++) {
			char t = gameptr->getValueAt(i, j);
			gameScreen[i][j] = t;
			setCursorPosition(i + ROW_OFSET, j);
			std::cout << t;
		}
	}

}
int gameboard::makeMove(int moveType) {
	gameptr->play(moveType, cursorRow, cursorCol);
	return (gameptr->getStatus());
}

void gameboard::moveCursor(char direction) {
	int maxRowIdx = std::min(gameptr->getMaxRow(), maxRow) - 1;
	int maxColIdx = std::min(gameptr->getMaxCol(), maxCol) - 1;
	switch (direction) {
		case 'u':
			if (cursorRow > 0) {
				cursorRow--;
			}
			break;
		case 'l':
			if (cursorCol > 0) {
				cursorCol--;
			}
			break;
		case 'd':
			if (cursorRow < maxRowIdx) {
				cursorRow++;
			}
			break;
		case 'r':
			if (cursorCol < maxColIdx) {
				cursorCol++;
			}
			break;
	}
	setCursorPosition(cursorRow + 2, cursorCol);
}

void gameboard::showBoard() {
	int gameRow = gameptr->getMaxRow();
	int gameCol = gameptr->getMaxCol();
	for (int i = 0; i < std::min(gameRow, maxRow); i++) {
		for (int j = 0; j < std::min(gameCol, maxCol); j++) {
			char t = gameptr->getValueAt(i, j);
			if (t == gameScreen[i][j])
				continue;
			setCursorPosition(i + ROW_OFSET, j);
			std::cout << t;
			gameScreen[i][j] = t;
		}
	}
	std::cout.flush();
	setCursorPosition(cursorRow + ROW_OFSET, cursorCol);
	return;
}
