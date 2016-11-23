#include "King.h"

King::King():Piece(){
}

King::King(int color, int type, Position pos):Piece(color,type,pos){
}

King::~King(){}

list<Position> King::getValidMoves(chessBoard* board){
	list<Position> moves;
	Position move = pos;
	for(int i = -1; i<2; i++){
		for( int j = -1; j<2; j++){
			move.setRow(pos.getRow()+i);
			move.setCol(pos.getCol()+j);
			if((move.getRow() < 8 && move.getRow() >= 0)
					&& (move.getCol() < 8 && move.getCol() >= 0)
					&& !board->hasPiecePlayer(move.getRow(),move.getCol(),color)){
				moves.push_front(move);
			}
		}
	}
	return moves;
}

bool King::possibleAttack(Position attack){
	bool bRow = pos.getRow() == pos.getRow();
	bool bCol = pos.getCol() == pos.getCol();
	bRow = bRow || pos.getRow() == (pos.getRow() - 1);
	bRow = bRow || pos.getRow() == (pos.getRow() + 1);
	bCol = bCol || pos.getCol() == (pos.getCol() - 1);
	bCol = bCol || pos.getCol() == (pos.getCol() + 1);
	return bRow && bCol;
}
