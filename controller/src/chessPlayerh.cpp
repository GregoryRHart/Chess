#include "chessPlayerh.h"
#include <iostream>
using namespace std;

chessPlayerh::chessPlayerh(chessFacade* facade):IChessPlayer(facade){
}
/**
 * Indicate to the player that the user clicked on the given
 * row and column with the mouse.
 */
void chessPlayerh::on_CellSelected(int row, int col, bool& selected){
	if(selected){
		Position move = facade->getMove(prevRow, prevCol, row, col);
		if(prevRow == move.getRow() && prevCol == move.getCol()){
			unHighlight();
		} else {
			makeMove(move);
			unHighlight();
			endTurn();
		}
		selected = false;
	} else {
		if(facade->hasPieceMine(row, col)){
			view->HighlightSquare(row, col, BLUE_SQUARE);
			list<Position> moves = facade->getValidMoves(row,col);
			prevRow = row;
			prevCol = col;
			highlight(moves);
			selected = true;
		}
	}
}

/**
 * Handle when the timeout duration has passed.
 */
void chessPlayerh::on_TimerEvent(){}

void chessPlayerh::makeMove(Position move){
	view->ClearPiece(prevRow,prevCol);
	int color = facade->getColor(move);
	int piece = facade->getPiece(move);
	ImageName image = (ImageName)(2*piece+4+color);
	view->ClearPiece(move.getRow(), move.getCol());
	view->PlacePiece(move.getRow(), move.getCol(), image);
}

void chessPlayerh::highlight(list<Position> moves){
	Position temp;
	while(!moves.empty()){
		temp = moves.front();
		view->HighlightSquare(temp.getRow(), temp.getCol(),GREEN_SQUARE);
		moves.pop_front();
	}
}

void chessPlayerh::unHighlight(){
	for(int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			view->UnHighlightSquare(i,j);
		}
	}
}
