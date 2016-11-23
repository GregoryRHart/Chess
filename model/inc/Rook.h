#pragma once

#include "Piece.h"
using namespace std;

class Rook: public Piece{
public:
	Rook();

	Rook(int color, int type, Position attack);

	~Rook();

	list<Position> getValidMoves(chessBoard* board);

	bool possibleAttack(Position attack);
};
