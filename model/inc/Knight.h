#pragma once

#include "Piece.h"
using namespace std;

class Knight: public Piece{
public:
	Knight();

	Knight(int color, int type, Position attack);

	~Knight();

	list<Position> getValidMoves(chessBoard* board);

	bool possibleAttack(Position attack);
};
