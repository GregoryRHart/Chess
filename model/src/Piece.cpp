#include "Piece.h"

Piece::Piece():color(0),type(0),pos(){
}

Piece::Piece(int color, int type, Position pos):color(color),type(type),pos(pos){
}

Piece::~Piece(){}

int Piece::getColor(){
	return color;
}

int Piece::getType(){
	return type;
}

Position Piece::getPosition(){
	return pos;
}

void Piece::setPosition(Position nPos){
	pos = nPos;
}

void Piece::setPosition(int row, int col){
	pos.setRow(row);
	pos.setCol(col);
}

void Piece::move(Position final){
	pos = final;
}

void Piece::unMove(Position orig){
	pos = orig;
}
