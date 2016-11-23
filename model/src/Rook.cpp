#include "Rook.h"

Rook::Rook():Piece(){
}

Rook::Rook(int color, int type, Position pos):Piece(color, type, pos){
}

Rook::~Rook(){}

list<Position> Rook::getValidMoves(chessBoard* board){
	list<Position> moves;
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
	return moves;
}

bool Rook::possibleAttack(Position attack){
	return pos.getRow() == attack.getRow() || pos.getCol() == attack.getCol();
}
