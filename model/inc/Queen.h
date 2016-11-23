#pragma once

#include "Piece.h"
using namespace std;

class Queen: public Piece{
public:
	Queen();

	Queen(int color, int type, Position attack);

	~Queen();

	list<Position> getValidMoves(chessBoard* board);

	bool possibleAttack(Position attack);
private:
	void rookMoves(list<Position>& moves, chessBoard* board);

	void bishopMoves(list<Position>& moves, chessBoard* board);
};
