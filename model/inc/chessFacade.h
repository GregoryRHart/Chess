#pragma once

#include <string>
#include <list>
#include "Position.h"
#include "chessBoard.h"
#include "Piece.h"
#include "Move.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "Pawn.h"
using namespace std;

class chessFacade{
private:
	chessBoard board;
	list<Piece*> white;
	list<Piece*> black;
	int turn;
	list<Move> history;
	list<Position> moves;

public:
	chessFacade();

	~chessFacade();

	int getTurn();

	void save(string file);

	void load(string file);

	void undoMove();

	list<Position> randomMove();

	bool hasPiece(int row, int col);

	bool hasPieceMine(int row, int col);

	bool hasPieceHis(int row, int col);

	Position getMove(int rowi, int coli, int rowf, int colf);

	list<Position> getValidMoves(int row, int col);

	int getColor(Position pos);

	int getPiece(Position pos);

	bool check();

	bool checkmate();

	bool stalemate();

	list<Position> undo();
private:
	void initPieces(list<Piece*>& pieces, int color, int row);

	void changeTurn();

	list<Position> removeCheck(list<Position> moves, Piece* piece);

	void movePiece(Position start, Position final);

	bool canMove(list<Piece*>& pieces);

	void clear();
};

