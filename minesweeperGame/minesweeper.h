#include "game.h"
class minesweeper: public game{
public:
	minesweeper(int nBombs, int maxRow, int maxCol);
	~minesweeper();
	void play(char moveType, int rowidx, int colidx);

private:
	void markBombs(int rowidx, int colidx);
	bool reveal(int rowidx, int colidx);
	void lost();
	char ** map;
	char ** bomb;
	int maxBombs;
};
