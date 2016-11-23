#ifndef CHESS_PLAYERH
#define CHESS_PLAYERH

#include "IChessPlayer.h"

class chessPlayerh: public IChessPlayer{
private:
	int prevRow;
	int prevCol;

public: //methods
	chessPlayerh(chessFacade* facade);
	/**
	 * Indicate to the player that the user clicked on the given
	 * row and column with the mouse.
	 */
	void on_CellSelected(int row, int col, bool& selected);

	/**
	 * Handle when the timeout duration has passed.
	 */
	void on_TimerEvent();

	void makeMove(Position move);

	void highlight(list<Position> moves);

	void unHighlight();
};

#endif
