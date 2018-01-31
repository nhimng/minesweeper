#include "minesweeper.h"
#include <cstdlib>
#include <iostream>
#include "helper.h"
#include <windows.h>

minesweeper::minesweeper(int nBombs, int row, int col): game(row, col){
	maxBombs = nBombs;
	map = new char* [row];
	for (int i = 0; i < row; i++) {
		map[i] = new char[col];
		for (int j = 0; j < col; j++) {
			map[i][j] = '.';
			UpdateBoard(i,j,'0');
		}
	}
	bomb = new char*[maxBombs];
	int rowidx = 0;
	int colidx = 0;
	int n = 0;
	for (; n < maxBombs;)
	{
		bomb[n] = new char[2];
		srand(GetTickCount() + n);
		rowidx = ((rand() + rowidx + colidx) % row);
		colidx = ((rand() + rowidx + colidx) % col);
		if (map[rowidx][colidx] == '.') {
			map[rowidx][colidx] = 'b';
			bomb[n][0] = rowidx;
			bomb[n][1] = colidx;
			markBombs(rowidx - 1, colidx - 1);
			markBombs(rowidx - 1, colidx);
			markBombs(rowidx - 1, colidx + 1);
			markBombs(rowidx, colidx + 1);
			markBombs(rowidx + 1, colidx + 1);
			markBombs(rowidx + 1, colidx);
			markBombs(rowidx + 1, colidx - 1);
			markBombs(rowidx, colidx - 1);
			n++;
		}
	}
}

minesweeper::~minesweeper(){
	int row = getMaxRow();
	for (int i = 0; i < row; i++) {
		delete[] map[i];
	}
	delete[] map;
	map = NULL;
	for (int i = 0; i < maxBombs; i++) {
		delete[] bomb[i];
	}
	delete[] bomb;
	bomb = NULL;
}

void minesweeper::markBombs(int rowidx, int colidx) {
	int maxRows = getMaxRow();
	int maxCols = getMaxCol();
	if (rowidx < 0 || rowidx >= maxRows || colidx < 0 || colidx >= maxCols)
		return;
	char t = map[rowidx][colidx];
	if (t == '.')
		map[rowidx][colidx] = '1';
	else if (isdigit(t))
		map[rowidx][colidx] = static_cast<char>(t + 1);
}

bool minesweeper::reveal(int rowidx, int colidx) {
	int maxRows = getMaxRow();
	int maxCols = getMaxCol();
	if (rowidx < 0 || rowidx >= maxRows || colidx < 0 || colidx >= maxCols)
		return true;
	//printf("Revealing: (%d, %d) \n", rowidx + 1, colidx + 1);
	if (getValueAt(rowidx,colidx) != '0')
		return true;
	if (getValueAt(rowidx,colidx) == 'f')
		return true;
	char t = map[rowidx][colidx];
	UpdateBoard(rowidx,colidx,t);
	if (t == 'b')
		return false;
	else if (t == '.') {
		reveal(rowidx - 1, colidx - 1);
		reveal(rowidx - 1, colidx);
		reveal(rowidx - 1, colidx + 1);
		reveal(rowidx, colidx + 1);
		reveal(rowidx + 1, colidx + 1);
		reveal(rowidx + 1, colidx);
		reveal(rowidx + 1, colidx - 1);
		reveal(rowidx, colidx - 1);
		return true;
	}
	else
		return true;

}
//MoveType: 1- reveal, 2- mark
void minesweeper::play(char moveType, int rowidx, int colidx)
{
	if (getStatus() != 0)
	{
		setCursorPosition(0, 0);
		std::cout << "Game Already Over!          ";
		return;
	}
	bool isValid = true;
	switch (moveType) {
	case 'x':
		isValid = reveal(rowidx, colidx);
		break;
	case 'z' :
		if(getValueAt(rowidx, colidx) == '0')
			UpdateBoard(rowidx, colidx, 'f');
		break;
	}
	if (!isValid) {
		lost();
	}
	return;
}

void minesweeper::lost() {
	for (int i = 0; i < maxBombs; i++) {
		int rowidx = bomb[i][0];
		int colidx = bomb[i][1];
		if (getValueAt(rowidx,colidx) == 'f')
			UpdateBoard(rowidx, colidx, 'B');
		else
			UpdateBoard(rowidx, colidx, 'X');
	}
	for (int i = 0; i < getMaxRow(); i++) {
		for (int j = 0; j < getMaxCol(); j++) {
			char t = getValueAt(i, j);
			if (t != 'B' && t != 'X')
				UpdateBoard(i, j, map[i][j]);
		}
	}
	setLoss();
}
