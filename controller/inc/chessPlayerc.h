#ifndef CHESS_PLAYERC
#define CHESS_PLAYERC

#include "IChessPlayer.h"
using namespace std;

class chessPlayerc: public IChessPlayer{

public: //methods
	chessPlayerc(chessFacade* facade);
	/**
	 * Indicate to the player that the user clicked on the given
	 * row and column with the mouse.
	 */
	void on_CellSelected(int row, int col, bool& selected);

	/**
	 * Handle when the timeout duration has passed.
	 */
	void on_TimerEvent();

	void makeMove(Position orig, Position final);
};

#endif
