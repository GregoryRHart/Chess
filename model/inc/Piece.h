#pragma once

#include "Position.h"
#include "chessBoard.h"
#include <stdlib.h>
#include <list>
using namespace std;

class chessBoard;

class Piece{
protected:
	int color;
	int type;
	Position pos;

public:
	Piece();

	Piece(int color, int type, Position pos);

	~Piece();

	int getColor();

	int getType();

	Position getPosition();

	void setPosition(Position pos);

	void setPosition(int row, int col);

	virtual list<Position> getValidMoves(chessBoard* board) = 0;

	virtual void move(Position final);

	virtual bool possibleAttack(Position attack) = 0;

	virtual void unMove(Position orig);
};

