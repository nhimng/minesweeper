#include "game.h"
class gameboard {
public:
	gameboard();
	gameboard(game* newgame);
	~gameboard();
	void moveCursor(char direction);
	int getCursorRow() { return cursorRow; };
	int getCursorCol() { return cursorCol; };
	bool makeMove(char moveType);
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
