#pragma once

#include "StringUtil.h"
#include "URLInputStream.h"
#include "HTMLTokenizer.h"
#include "HTMLToken.h"
#include "Move.h"
#include "chessBoard.h"
#include "Piece.h"
#include <list>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class XMLHandler{
public:
	//Default constructor
	XMLHandler();

	//I shouldn't have to explicitly delete anything.
	~XMLHandler();

	static void save(string fileName, list<Move>& history, chessBoard& board);

	static void load(string fileName, list<Move>& history, chessBoard& board,
			list<Piece*>& white, list<Piece*>& black);

private:
	static void printBoard(ofstream& outFile, chessBoard& board);

	static void printHistory(ofstream& outFile, list<Move>& history);

	static string printPiece(Piece* piece);

	static string printMove(Move move);

	static string convertType(int type);

	static string convertColor(int color);

	static void loadBoard(HTMLTokenizer& tokenizer, chessBoard& board,
			list<Piece*>& white, list<Piece*>& black);

	static void loadHistory(HTMLTokenizer& tokenizer, list<Move>& history);

	static void loadMove(HTMLTokenizer& tokenizer, list<Move>& history);

	static void loadPiece(HTMLToken current, chessBoard& board,
			list<Piece*>& white, list<Piece*>& black);

	static void loadPiece(HTMLToken current, int& row, int& col, int& color, int& piece);

	static int convertType(string type);

	static int convertColor(string color);
};


