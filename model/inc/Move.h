#pragma once

#include <string>
#include "Position.h"
#include "Piece.h"
using namespace std;

class Move{
private:
	Position init;
	Position final;
	int type;
	int color;
	bool captured;
	int piece;
public:
	Move();

	Move(Position init, Position final, Piece* mine,  Piece* his);

	Move(Position init, Position final, int color, int type);

	Move(Position init, Position final, int color, int type, int piece);

	~Move();

	Position getInit();

	Position getFinal();

	int getType();

	int getColor();

	bool getCaptured();

	int getPieceCap();

	string toString();
};

//ostream& operator <<(ostream& os, const Move move);
