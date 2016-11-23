#include "Pawn.h"

Pawn::Pawn():Piece(){
}

Pawn::Pawn(int color, int type, Position pos):Piece(color, type, pos){
	if(color == 0 && pos.getRow() == 6){
		moved = false;
	} else if(color == 1 && pos.getRow() == 1){
		moved = false;
	} else {
		moved = true;
	}
}

Pawn::~Pawn(){
}

list<Position> Pawn::getValidMoves(chessBoard* board){
	list<Position> moves;
	Position move = pos;

	//What direction forward is depends on the player
	if(color == 0){
		move.setRow(move.getRow()-1);
	} else {
		move.setRow(move.getRow()+1);
	}
	//If the pawn is at the end of the board there are no legal moves.
	if(move.getRow() >= 0 && move.getRow() < 8){
		//Is there a piece blocking the Pawn.
		if(!board->hasPiece(move.getRow(),move.getCol())){
			moves.push_front(move);
			//Move forward two squares
			if(color == 0){
				move.setRow(move.getRow()-1);
			} else {
				move.setRow(move.getRow()+1);
			}
			//Can the pawn move forward two squares
			if(!moved && !board->hasPiece(move.getRow(),move.getCol())){
				moves.push_front(move);
			}
			//Move it back to one square ahead
			if(color == 0){
				move.setRow(move.getRow()+1);
			} else {
				move.setRow(move.getRow()-1);
			}
		}
		//Can the pawn kill a piece
		if(pos.getCol() < 7 && board->hasPiecePlayer(move.getRow(),move.getCol() + 1,!color)){
			move.setCol(move.getCol()+1);
			moves.push_front(move);
			move.setCol(move.getCol()-1);
		}
		if(pos.getCol() > 0 && board->hasPiecePlayer(move.getRow(),move.getCol() - 1,!color)){
			move.setCol(move.getCol()-1);
			moves.push_front(move);
			move.setCol(move.getCol()+1);
		}
	}
	return moves;
}

void Pawn::move(Position final){
	Piece::move(final);
	moved = true;
}

void Pawn::unMove(Position orig){
	Piece::unMove(orig);
	if(color == 0 && pos.getRow() == 6){
		moved = false;
	} else if(color == 1 && pos.getRow() == 1){
		moved = false;
	}
}

bool Pawn::possibleAttack(Position attack){
	bool r = abs(pos.getRow() - attack.getRow()) == 1;
	bool c = abs(pos.getCol() - attack.getCol()) == 1;
	return r && c;
}

