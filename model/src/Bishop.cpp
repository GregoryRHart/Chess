#include "Bishop.h"
#include <stdlib.h>

Bishop::Bishop():Piece(){
}

Bishop::Bishop(int color, int type, Position pos):Piece(color, type, pos){
}

Bishop::~Bishop(){}

list<Position> Bishop::getValidMoves(chessBoard* board){
	list<Position> moves;
	Position move = pos;
	int rMin = move.getRow();
	int rMax = 7-rMin;
	int cMin = move.getCol();
	int cMax = 7-cMin;
	int lim = min(rMin,cMin);
	//Check spaces behind  and to one side until a piece or the edge is reached
	for(int i = 1; i <= lim; i++){
		move.setRow(pos.getRow()-i);
		move.setCol(pos.getCol()-i);
		if((move.getRow() < 8 && move.getRow() >= 0)
				&& (move.getCol() < 8 && move.getCol() >= 0)){

			if(board->hasPiecePlayer(move.getRow(), move.getCol(), color)){
				break;
			} else if(board->hasPiecePlayer(move.getRow(), move.getCol(), !color)){
				moves.push_front(move);
				break;
			} else {
				moves.push_front(move);
			}
		}
	}
	lim = min(rMin,cMax);
	//Check spaces behind and to the other side until a piece or the edge is reached
	for(int i = 1; i <= lim; i++){
		move.setRow(pos.getRow()-i);
		move.setCol(pos.getCol()+i);
		if((move.getRow() < 8 && move.getRow() >= 0)
				&& (move.getCol() < 8 && move.getCol() >= 0)){

			if(board->hasPiecePlayer(move.getRow(), move.getCol(), color)){
				break;
			} else if(board->hasPiecePlayer(move.getRow(), move.getCol(), !color)){
				moves.push_front(move);
				break;
			} else {
				moves.push_front(move);
			}
		}
	}
	lim = min(rMax,cMin);
	//Check spaces in front and to one side until a piece or the edge is reached
	for(int i = 1; i <= lim; i++){
		move.setRow(pos.getRow()+i);
		move.setCol(pos.getCol()-i);
		if((move.getRow() < 8 && move.getRow() >= 0)
				&& (move.getCol() < 8 && move.getCol() >= 0)){

			if(board->hasPiecePlayer(move.getRow(), move.getCol(), color)){
				break;
			} else if(board->hasPiecePlayer(move.getRow(), move.getCol(), !color)){
				moves.push_front(move);
				break;
			} else {
				moves.push_front(move);
			}
		}
	}
	lim = min(rMax,cMax);
	//Check spaces in front and to the other side until a piece or the edge is reached
	for(int i = 1; i <= lim; i++){
		move.setRow(pos.getRow()+i);
		move.setCol(pos.getCol()+i);
		if((move.getRow() < 8 && move.getRow() >= 0)
				&& (move.getCol() < 8 && move.getCol() >= 0)){

			if(board->hasPiecePlayer(move.getRow(), move.getCol(), color)){
				break;
			} else if(board->hasPiecePlayer(move.getRow(), move.getCol(), !color)){
				moves.push_front(move);
				break;
			} else {
				moves.push_front(move);
			}
		}
	}
	return moves;
} 

bool Bishop::possibleAttack(Position attack){
	int rDiff = abs(pos.getRow() - attack.getRow());
	int cDiff = abs(pos.getCol() - attack.getCol());
	return rDiff == cDiff;
} 
