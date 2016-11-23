#include "Queen.h"
#include <stdlib.h>

Queen::Queen():Piece(){
}

Queen::Queen(int color, int type, Position pos):Piece(color,type,pos){
}

Queen::~Queen(){}

list<Position> Queen::getValidMoves(chessBoard* board){
	list<Position> moves;
	rookMoves(moves, board);
	bishopMoves(moves, board);
	return moves;
}

bool Queen::possibleAttack(Position attack){
	bool result = pos.getRow() == attack.getRow();
	result = result || pos.getCol() == attack.getCol();
	int rDiff = abs(pos.getRow() - attack.getRow());
	int cDiff = abs(pos.getCol() - attack.getCol());
	result = result || rDiff == cDiff;
	return result;
}

void Queen::rookMoves(list<Position>& moves, chessBoard* board){
	Position move = pos;
	int rMin = move.getRow();
	int rMax = 8-rMin;
	int cMin = move.getCol();
	int cMax = 8-cMin;
	//Check spaces behind until a piece or the edge is reached
	for(int i = 1; i <= rMin; i++){
		move.setRow(pos.getRow()-i);
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
	//Check spaces in front until a piece or the edge is reached
	for(int i = 1; i < rMax; i++){
		move.setRow(pos.getRow()+i);
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
	move.setRow(pos.getRow());
	//Check spaces to one side until a piece or the edge is reached
	for(int i = 1; i <= cMin; i++){
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
	//Check spaces to the other side until a piece or the edge is reached
	for(int i = 1; i < cMax; i++){
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
}


void Queen::bishopMoves(list<Position>& moves, chessBoard* board){
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
}  
