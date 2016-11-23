#pragma once

#include "Piece.h"
using namespace std;

class Bishop: public Piece{
public:
	Bishop();

	Bishop(int color, int type, Position attack);

	~Bishop();

	list<Position> getValidMoves(chessBoard* board);

	bool possibleAttack(Position attack);
};
