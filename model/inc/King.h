#pragma once

#include "Piece.h"
using namespace std;

class King: public Piece{
public:
	King();

	King(int color, int type, Position attack);

	~King();

	list<Position> getValidMoves(chessBoard* board);

	bool possibleAttack(Position attack);
};
