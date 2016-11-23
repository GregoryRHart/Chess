#include "Knight.h"
#include "math.h"
#include <stdlib.h>

Knight::Knight():Piece(){
}

Knight::Knight(int color, int type, Position pos):Piece(color, type, pos){
}

Knight::~Knight(){
}

list<Position> Knight::getValidMoves(chessBoard* board){
	list<Position> moves;
	Position move = pos;
	int r;
	int c;
	for(int i = 1; i<=10; i++){
		r = (i-1)/2-2;
		c = pow(-1,i)*(3-abs(r));
		if(r != 0){
			move.setRow(pos.getRow()+r);
			move.setCol(pos.getCol()+c);
			if((move.getRow() < 8 && move.getRow() >= 0)
					&& (move.getCol() < 8 && move.getCol() >= 0)
					&& !board->hasPiecePlayer(move.getRow(),move.getCol(),color)){
				moves.push_front(move);
			}
		}
	}
	return moves;
}

bool Knight::possibleAttack(Position attack){
	int rDiff = abs(pos.getRow() - attack.getRow());
	int cDiff = abs(pos.getCol() - attack.getCol());
	bool result = rDiff == 2 && cDiff == 1;
	result = result || rDiff == 1 && cDiff == 2;
	return result;
}
