#include "game.h"
#define KB_X 120
#define KB_Z 122

class minesweeper: public game{
public:
	minesweeper(int nBombs, int maxRow, int maxCol);
	~minesweeper();
	void play(int moveType, int rowidx, int colidx);

private:
	void markBombs(int rowidx, int colidx);
	bool reveal(int rowidx, int colidx);
	int unmarkedCell;
	void lost();
	void win();
	char ** map;
	char ** bomb;
	int maxBombs;
};
