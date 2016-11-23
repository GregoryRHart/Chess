#pragma once

#include "Piece.h"
#include "Position.h"
using namespace std;

class Piece;

class chessBoard{
private:
	Piece* board[8][8];

public:
	chessBoard();

	~chessBoard();

	Piece*& operator[](Position pos);

	Piece*& operator()(int row, int col);

	bool hasPiece(int row, int col);

	bool hasPiecePlayer(int row, int col, int color);

	Piece* move(Position start, Position final);

	void unMove(Position orig, Position final, Piece* taken);

	void clear();
};

