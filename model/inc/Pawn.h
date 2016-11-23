#pragma once

#include "Piece.h"
using namespace std;

class Pawn: public Piece{
private:
	bool moved;
public:
	Pawn();

	Pawn(int color, int type, Position attack);

	~Pawn();

	list<Position> getValidMoves(chessBoard* board);

	void move(Position final);

	bool possibleAttack(Position attack);

	void unMove(Position orig);
};
