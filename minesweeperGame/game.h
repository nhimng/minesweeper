#pragma once
class game {
public:
	game(int maxRow, int maxCol);
	~game();
	virtual void play(int moveType, int rowidx, int colidx) { };
	int getMaxRow() { return boardMaxRow; };
	int getMaxCol() { return boardMaxCol; };
	void UpdateBoard(int rowidx, int colidx, char value);
	char getValueAt(int rowidx, int colidx);
	void setLoss();
	void setWin();
	int getStatus() { return status; };

private:
	char** displayBoard;
	int boardMaxRow;
	int boardMaxCol;
	//status: 0:Ongoing, 1:Win, -1:Lost
	int status; 
};