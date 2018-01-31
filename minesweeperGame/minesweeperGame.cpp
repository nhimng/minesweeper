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

int mainMenu() {
	int choice;
	bool gameStart = true;
	while (gameStart != false) {
		cout << "---------MENU---------\n";
		cout << " 1 - Start a new game.\n";
		cout << " 2 - Help.\n";
		cout << " 3 - Exit.\n";
		cout << "----------------------\n";
		cin >> choice;
		switch (choice)
		{
		case 1:
			system("cls");
			return choice;
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

void play(gameboard* gb) {
	gb->showBoard();
	int key = 0;
	bool gameOn = true;
	while (key != KB_ESCAPE && key != KB_Q && gameOn != false)
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
}

int main()
{
	int nRow = 10;
	int nCol = 10;
	gameboard* gb = new gameboard();
	game * gameptr;
	char choice;
	int gameStart = mainMenu();
	while (gameStart != 0) {
		setCursorPosition(0, 0);
		std::cout << "*New Game!*";
		gameptr = new minesweeper(15, 10, 10);
		gb->newGame(gameptr);
		play(gb);
		delete gameptr;
		setCursorPosition(0, 0);
		cout << "Game Over... Try again? (y/n) ";
		cin >> choice;
		if (choice != 'y' && choice != 'Y') {
			gameStart = 0;
		}
		system("cls");
	}
	return 0;
}



