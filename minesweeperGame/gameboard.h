#include "game.h"
#define ROW_OFSET 2

class gameboard {
public:
	gameboard();
	gameboard(game* newgame);
	~gameboard();
	void moveCursor(char direction);
	int getCursorRow() { return cursorRow; };
	int getCursorCol() { return cursorCol; };
	int makeMove(char moveType);
	void showBoard();
	char **gameScreen;
	void newGame(game* newgame);
	void clearGame();
private:
	game * gameptr;
	int cursorRow;
	int cursorCol;
	int maxRow;
	int maxCol;
};
