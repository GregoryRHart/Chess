#include "chessBoard.h"
#include <iostream>
using namespace std;

chessBoard::chessBoard(){
	clear();
}

chessBoard::~chessBoard(){
}

Piece*& chessBoard::operator[](Position pos){
	return board[pos.getRow()][pos.getCol()];
}

Piece*& chessBoard::operator()(int row, int col){
	return board[row][col];
}

bool chessBoard::hasPiece(int row, int col){
	Piece* piece = board[row][col];
	if(piece != NULL){
		return true;
	}
	return false;
}

bool chessBoard::hasPiecePlayer(int row, int col, int color){
	Piece* piece = board[row][col];
	if(piece != NULL){
		return piece->getColor() == color;
	}
	return false;
}

Piece* chessBoard::move(Position start, Position final){
	Piece* piece = board[final.getRow()][final.getCol()];
	board[final.getRow()][final.getCol()] = board[start.getRow()][start.getCol()];
	board[start.getRow()][start.getCol()] = NULL;
	return piece;
}

void chessBoard::unMove(Position orig, Position final, Piece* taken){
	board[orig.getRow()][orig.getCol()] = board[final.getRow()][final.getCol()];
	board[final.getRow()][final.getCol()] = taken;
}

void chessBoard::clear(){
	for(int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			board[i][j] = NULL;
		}
	}
}
