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
#define KB_X 120
#define KB_Z 122

int submenu() {
	int choice;
	bool gameStart = true;
	while (gameStart != false) {
		cout << "--------NEW GAME--------\n";
		cout << " 1 - Small Board (10x10)\n";
		cout << " 2 - Medium Board (20x20)\n";
		cout << " 3 - Large Board (30x30)\n";
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
			cout << "Use WASD keys or arrow keys to move, XZ to select, Q to surrender.\n";
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
	while (key != KB_ESCAPE && key != KB_Q && gameOn == 0)
	{
		if (_kbhit())
		{
			key = _getch();
			//printf("key = %i \n", key);
			switch (key)
			{
			case KB_LEFT:
			case KB_A:
				//Do something
				gb->moveCursor('l');
				//printf("LEFT\n");
				break;
			case KB_RIGHT:
			case KB_D:
				//Do something   
				gb->moveCursor('r');
				//printf("RIGHT\n");
				break;
			case KB_UP:
			case KB_W:
				//printf("UP\n");
				gb->moveCursor('u');
				//Do something                     
				break;

			case KB_DOWN:
			case KB_S:
				//printf("DOWN\n");
				gb->moveCursor('d');
				//Do something                     
				break;
			case KB_X:
				gameOn = gb->makeMove('x');
				break;
			case KB_Z:
				gameOn = gb->makeMove('z');
				break;
			}
			gb->showBoard();
		}
	}
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



