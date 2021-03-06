// minesweeperGame.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "minesweeper.h"
#include "gameboard.h"
#include "game.h"
#include <conio.h>
#include <iostream>
#include "helper.h"
using namespace std;

#define STR_ERASER  "                                                         \n"
#define KB_UP 72
#define KB_W 119
#define KB_DOWN 80
#define KB_S 115
#define KB_LEFT 75
#define KB_A 97
#define KB_RIGHT 77
#define KB_D 100
#define KB_ESCAPE 27
#define KB_Q 113

int submenu() {
	int choice;
	bool gameStart = true;
	while (gameStart != false) {
		cout << "--------NEW GAME--------\n";
		cout << " 1 - Small Board\n";
		cout << " 2 - Medium Board\n";
		cout << " 3 - Large Board\n";
		cout << " 4 - Return to Menu \n";
		cout << "------------------------\n";
		cin >> choice;
		if (choice < 1 || choice > 4) {
			cout << "Not a Valid Choice. \n";
			system("pause");
			system("cls");
		}
		else { 
			return choice; 
		}
	}
	return 0;
}

int menu() {
	int choice;
	int boardType = 0;
	bool gameStart = true;
	while (gameStart != false) {
		system("cls");
		cout << "---------MENU---------\n";
		cout << " 1 - Start a new game.\n";
		cout << " 2 - Help.\n";
		cout << " 3 - Quit.\n";
		cout << "----------------------\n";
		cin >> choice;
		switch (choice)
		{
		case 1:
			boardType = submenu();
			if (boardType < 4) {
				system("cls");
				return boardType;
			}
			// rest of code here
			break;
		case 2:
			cout << "Ahahah, you really think I will help you?\n";
			system("pause");
			cout << "...\n";
			system("pause");
			cout << "Use WASD keys or arrow keys to move, Q to surrender.\n";
			// rest of code here
			break;
		case 3:
			cout << "End of Program.\n";
			gameStart = false;
			break;
		default:
			cout << "Not a Valid Choice. \n";
			cout << "Choose again.\n";
			cin >> choice;
			break;
		}
	}
	system("cls");
	return 0;
}

int play(gameboard* gb) {
	gb->showBoard();
	int key = 0;
	char c;
	int gameOn = 0;
	int k = 0;
	while (key != KB_ESCAPE && key != KB_Q && gameOn == 0)
	{

		if (_kbhit())
		{
			setCursorPosition(0, 0);
			std::cout << STR_ERASER << STR_ERASER;
			key = _getch();
			//printf("key = %i \n", key);
			switch (key)
			{
			case 0:
			case 224:
				switch (key = _getch()) {
					case KB_LEFT:
						gb->moveCursor('l');
						break;
					case KB_RIGHT:
						gb->moveCursor('r');
						break;
					case KB_DOWN:
						gb->moveCursor('d');
						break;
					case KB_UP:
						gb->moveCursor('u');
						break;
				}
				break;
			case KB_A:
				gb->moveCursor('l');
				break;
			case KB_D:
				gb->moveCursor('r');
				break;
			case KB_W:
				gb->moveCursor('u');                  
				break;
			case KB_S:
				gb->moveCursor('d');                    
				break;
			default:
				gameOn = gb->makeMove(key);
				break;
			}
			gb->showBoard();
		}
	}
	setCursorPosition(0, 0);
	std::cout << STR_ERASER << STR_ERASER;
	setCursorPosition(1, 0);
	cout << "Try again? (y/n) ";
	cin >> c;
	if (c != 'y' && c != 'Y') {
		return menu();
	}
	else
	{
		system("cls");
		return 9;
	}
}

int main()
{
	int nRow = 0;
	int nCol = 0;
	int tryAgain = -1;
	gameboard* gb = new gameboard();
	game * gameptr;
	int gameStart = menu();
	while (gameStart != 0) {
		setCursorPosition(0, 0);
		std::cout << "*New Game!*";
		switch (gameStart) {
		case 1:
			nRow = 10;
			nCol = 10;
			break;
		case 2:
			nRow = 20;
			nCol = 20;
			break;
		case 3:
			nRow = 30;
			nCol = 30;
			break;
		}
		gameptr = new minesweeper((nRow*nCol)/10, nRow, nCol);
		gb->newGame(gameptr);
		tryAgain = play(gb);
		if (tryAgain != 9) {
			gameStart = tryAgain;
		}
		delete gameptr;
	}
	return 0;
}



