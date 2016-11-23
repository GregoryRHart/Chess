#include "Position.h"
using namespace std;

Position::Position():row(0),col(0){
}

Position::Position(int row, int col):row(row),col(col){
}

Position::~Position(){
}

Position Position::operator=(Position other){
	row = other.row;
	col = other.col;
}

int Position::getRow(){
	return row;
}

int Position::getCol(){
	return col;
}

void Position::setRow(int nRow){
	row = nRow;
}

void Position::setCol(int nCol){
	col = nCol;
}

void Position::set(int nrow, int ncol){
    row = nrow;
    col = ncol;
}

bool Position::operator==(const Position& other) const{
	return row == other.row && col == other.col;
}
