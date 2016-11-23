#include "chessFacade.h"
#include "XMLHandler.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

chessFacade::chessFacade():board(),turn(0){
	initPieces(white,0,6);
	initPieces(black,1,0);
}

chessFacade::~chessFacade(){
	clear();
}

int chessFacade::getTurn(){
	return turn;
}

void chessFacade::save(string file){
	XMLHandler::save(file, history, board);
}

void chessFacade::load(string file){
	file = "file://" + file;
	clear();
	XMLHandler::load(file, history, board, white, black);
	Move current = history.front();
	turn = !current.getColor();
} 

list<Position> chessFacade::randomMove(){
	list<Position> moves;
	Position orig;
	Position final;
	Piece* piece;
	int idx;
	srand(time(0));
	// This bit of code is strange because appearently you can only access the ends
	// of the list.  So I have to iterator to the index I want.
	while(moves.empty()){
		if(turn == 0){
			idx = rand() % white.size();
			list<Piece*>::iterator it = white.begin();
			for(int i=0; i<idx;i++, it++){}
			piece = *it;
		} else {
			idx = rand() % black.size();
			list<Piece*>::iterator it = black.begin();
			for(int i=0; i<idx;i++, it++){}
			piece = *it;
		}
		orig = piece->getPosition();
		moves = getValidMoves(orig.getRow(), orig.getCol());
		if(!moves.empty()){
			idx = rand() % moves.size();
			// Same thing as above.
			list<Position>::iterator it = moves.begin();
			for(int i=0; i<idx;i++, it++){}
			final = *it;

			moves.clear();
			moves.push_front(final);
			moves.push_front(orig);
			movePiece(orig, final);
		}
	}
	return moves;
}

bool chessFacade::hasPieceMine(int row, int col){
	if(turn == 0){
		return board.hasPiecePlayer(row, col, 0);
	}
	return board.hasPiecePlayer(row, col, 1);
}

bool chessFacade::hasPieceHis(int row, int col){
	if(turn == 0){
		return board.hasPiecePlayer(row, col, 1);
	}
	return board.hasPiecePlayer(row, col, 0);

}

bool chessFacade::hasPiece(int row, int col){
	return board.hasPiece(row, col);
}

Position chessFacade::getMove(int rowi, int coli, int rowf, int colf){
	Position start(rowi,coli);
	Position move(rowi,coli);
	Position temp;
	while(!moves.empty()){
		temp = moves.front();
		if(temp.getRow() == rowf && temp.getCol() == colf){
			move = temp;
			movePiece(start, move);
			break;
		}
		moves.pop_front();
	}
	return move;
}

list<Position> chessFacade::getValidMoves(int row, int col){
	Piece* piece = board(row,col);
	moves = piece->getValidMoves(&board);
	moves = removeCheck(moves, piece);
	return moves;
}

int chessFacade::getColor(Position pos){
	Piece* piece = board[pos];
	if(piece != NULL){
		return piece->getColor();
	}
	return 10;
}

int chessFacade::getPiece(Position pos){
	Piece* piece = board[pos];
	if(piece != NULL){
		return piece->getType();
	}
	return 10;
}

void chessFacade::initPieces(list<Piece*>& pieces, int color, int row){
	Position pos(row+1,4);
	if(color != 0){
		pos.setRow(row);
	}
	Piece* temp = new King(color,4,pos);
	board[pos] = temp;
	pieces.push_front(temp);
	pos.setCol(3);
	temp = new Queen(color,5,pos);
	board[pos] = temp;
	pieces.push_front(temp);
	pos.setCol(2);
	temp = new Bishop(color,3,pos);
	board[pos] = temp;
	pieces.push_front(temp);
	pos.setCol(5);
	temp = new Bishop(color,3,pos);
	board[pos] = temp;
	pieces.push_front(temp);
	pos.setCol(1);
	temp = new Knight(color,2,pos);
	board[pos] = temp;
	pieces.push_front(temp);
	pos.setCol(6);
	temp = new Knight(color,2,pos);
	board[pos] = temp;
	pieces.push_front(temp);
	pos.setCol(0);
	temp = new Rook(color,1,pos);
	board[pos] = temp;
	pieces.push_front(temp);
	pos.setCol(7);
	temp = new Rook(color,1,pos);
	board[pos] = temp;
	pieces.push_front(temp);
	pos.setRow(row);
	if(color != 0){
		pos.setRow(row+1);
	}
	for(int i=0; i<8; i++){
		pos.setCol(i);
		temp = new Pawn(color,0,pos);
		board[pos] = temp;
		pieces.push_front(temp);
	}
}

list<Position> chessFacade::removeCheck(list<Position> moves, Piece* piece){
	list<Position> temp = moves;
	Piece* taken;
	Position orig = piece->getPosition();
	Position move;
	while(!temp.empty()){
		move = temp.front();
		piece->move(move);
		taken = board.move(orig, move);
		if(taken != NULL){
			if(taken->getColor() == 0){
				white.remove(taken);
			} else{
				black.remove(taken);
			}
		}
		if(check()){
			moves.remove(move);
		}
		if(taken != NULL){
			if(taken->getColor() == 0){
				white.push_front(taken);
			} else{
				black.push_front(taken);
			}
		}
		piece->unMove(orig);
		board.unMove(orig, move, taken);
		temp.pop_front();
	}
	return moves;
}

bool chessFacade::check(){
	Position king;
	list<Piece*> opponent;
	if(turn == 0){
		king = white.back()->getPosition();
		opponent = black;
	} else {
		king = black.back()->getPosition();
		opponent = white;
	}
	Piece* temp;
	list<Position> moves;
	Position move;
	while(!opponent.empty()){
		temp = opponent.front();
		if(temp->possibleAttack(king)){
			moves = temp->getValidMoves(&board);
			while(!moves.empty()){
				move = moves.front();
				if(move == king){
					return true;
				}
				moves.pop_front();
			}
		}
		opponent.pop_front();
	}
	return false;
}

bool chessFacade::checkmate(){
	bool unCheck = true;
	if(turn == 0){
		unCheck = canMove(white);
	} else {
		unCheck = canMove(black);
	}
	return check() && !unCheck;
}

bool chessFacade::stalemate(){
	bool movePossible = true;
	if(turn == 0){
		movePossible = canMove(white);
	} else {
		movePossible = canMove(black);
	}
	if(white.size() == 1 && black.size() == 1){
		movePossible = false;
	}
	return !check() && !movePossible;
}

void chessFacade::movePiece(Position start, Position final){
	Piece* piece = board[start];
	Piece* rmPiece = board[final];
	Move temp(start, final, piece, rmPiece);
	history.push_front(temp);
	if(rmPiece != NULL){
		if(turn == 0){
			black.remove(rmPiece);
			delete rmPiece;
		} else {
			white.remove(rmPiece);
			delete rmPiece;
		}
	}
	piece->move(final);
	board.move(start, final);
	turn = !turn;
}

list<Position> chessFacade::undo(){
	list<Position> moves;
	if(!history.empty()){
		Move move = history.front();
		Position orig = move.getInit();
		Position final = move.getFinal();
		Piece* taken;
		Piece* piece = board[final];
		if(move.getCaptured()){
			switch(move.getPieceCap()){
			case 0:
				taken = new Pawn(!piece->getColor(),0,final);
				break;
			case 1:
				taken = new Rook(!piece->getColor(),1,final);
				break;
			case 2:
				taken = new Knight(!piece->getColor(),2,final);
				break;
			case 3:
				taken = new Bishop(!piece->getColor(),3,final);
				break;
			case 4:
				taken = new King(!piece->getColor(),4,final);
				break;
			case 5:
				taken = new Queen(!piece->getColor(),5,final);
				break;
			}
		} else {
			taken = NULL;
		}
		piece->unMove(orig);
		board.unMove(orig, final, taken);
		history.pop_front();
		moves.push_front(orig);
		moves.push_front(final);
		turn = !turn;
	}
	return moves;
}

bool chessFacade::canMove(list<Piece*>& pieces){
	bool result = false;
	list<Piece*>::iterator it = pieces.begin();
	list<Position> moves;
	Position pos;
	for(; it != pieces.end(); it++){
		pos = (*it)->getPosition();
		moves = getValidMoves(pos.getRow(), pos.getCol());
		if(!moves.empty()){
			return true;
		}
	}
	return result;
}

void chessFacade::clear(){
	board.clear();
	history.clear();
	Piece* temp;
	while(!white.empty()){
		temp = white.front();
		delete temp;
		white.pop_front();
	}
	while(!black.empty()){
		temp = black.front();
		delete temp;
		black.pop_front();
	}
}
