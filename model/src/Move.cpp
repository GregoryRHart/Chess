#include"Move.h"

Move::Move():init(),final(),type(0),color(0),captured(0),piece(0){
}

Move::Move(Position init, Position final, int color, int type):init(init),final(final),
		color(color),type(type),captured(false),piece(6){
}

Move::Move(Position init, Position final, int color, int type, int piece):init(init),final(final),
		color(color),type(type),captured(true),piece(piece){
}

Move::Move(Position init, Position final, Piece* mine, Piece* his):init(init),final(final){
	type = mine->getType();
	color = mine->getColor();
	if(his != NULL){
		captured = true;
		piece = his->getType();
	} else {
		captured = false;
		piece = 6;
	}
}

Move::~Move(){}

Position Move::getInit(){
	return init;
}

Position Move::getFinal(){
	return final;
}

int Move::getType(){
	return type;
}

int Move::getColor(){
	return color;
}

bool Move::getCaptured(){
	return captured;
}

int Move::getPieceCap(){
	return piece;
}

string Move::toString(){}

//ostream&operator<<(ostream&os,const Move move){}
