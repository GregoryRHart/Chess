#include "chessPlayerc.h"

chessPlayerc::chessPlayerc(chessFacade* facade):IChessPlayer(facade){
}
/**
    chessPlayerh(chessFacade* facade);
 * Indicate to the player that the user clicked on the given
 * row and column with the mouse.
 */
void chessPlayerc::on_CellSelected(int row, int col, bool& selected){}

/**
 * Handle when the timeout duration has passed.
 */
void chessPlayerc::on_TimerEvent(){
	list<Position> moves = facade->randomMove();
	Position orig = moves.front();
	Position final = moves.back();
	makeMove(orig, final);
	endTurn();
}

void chessPlayerc::makeMove(Position orig, Position final){
	view->ClearPiece(orig.getRow(), orig.getCol());
	int color = facade->getColor(final);
	int piece = facade->getPiece(final);
	ImageName image = (ImageName)(2*piece+4+color);
	view->ClearPiece(final.getRow(), final.getCol());
	view->PlacePiece(final.getRow(), final.getCol(), image);
}
