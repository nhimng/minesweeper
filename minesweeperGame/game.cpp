#include "game.h"
#include "helper.h"
#include <iostream>

game::game(int maxRow, int maxCol) {
	boardMaxRow = maxRow;
	boardMaxCol = maxCol;
	displayBoard = new char*[boardMaxRow];
	for (int i = 0; i < boardMaxRow; i++) {
		displayBoard[i] = new char[boardMaxCol];
	}
	status = 0;
}

void game::UpdateBoard(int rowidx, int colidx, char value) {
	if (rowidx < 0 || rowidx >= boardMaxRow || colidx < 0 || colidx >= boardMaxCol)
		return;
	displayBoard[rowidx][colidx] = value;
}

char game::getValueAt(int rowidx, int colidx) {
	if (rowidx < 0 || rowidx >= boardMaxRow || colidx < 0 || colidx >= boardMaxCol)
		return '\0';
	return displayBoard[rowidx][colidx];
}

void game::setLoss() {
	status = -1; 
	setCursorPosition(0, 0);
	std::cout << "Game Over!          ";
}

void game::setWin() {
	status = 1;
	setCursorPosition(0, 0);
	std::cout << "Winner!          ";
}

game::~game() {
	for (int i = 0; i < boardMaxRow; i++) {
		delete[] displayBoard[i];
	}
	delete[] displayBoard;
}
