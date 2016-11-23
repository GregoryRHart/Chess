#include <iostream>
#include <string>
#include <list>
#include "UnitTest.h"
#include "Piece.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "Pawn.h"
#include "chessBoard.h"
#include "Position.h"
using namespace std;

bool pawnMove(ostream& os);
bool rookMove(ostream& os);
bool knightMove(ostream& os);
bool bishopMove(ostream& os);
bool queenMove(ostream& os);
bool kingMove(ostream& os);

int main(int argc, char* argv[]){
	bool success = true; 

	cout << "Running tests" << endl;

	cout << "\tTesting Pawn" << endl;
	success = pawnMove(cout) && success;

	cout << "\tTesting Rook" << endl;
	success = rookMove(cout) && success;

	cout << "\tTesting Knight" << endl;
	success = knightMove(cout) && success;

	cout << "\tTesting Bishop" << endl;
	success = bishopMove(cout) && success;

	cout << "\tTesting Queen" << endl;
	success = queenMove(cout) && success;

	cout << "\tTesting King" << endl;
	success = kingMove(cout) && success;

	if (success) {
		cout << "Tests Succeeded!" << endl;
	}
	else {
		cout << "Tests Failed!" << endl;
	}

	return 0;
}

bool pawnMove(ostream& os){
	bool success = true;
    chessBoard board;
    Position pos1(3,3);
    Piece* pawn1 =  new Pawn(0,0,pos1);
    Position pos2(6,6);
    Piece* pawn2 = new Pawn(0,0,pos2);
    Position pos3(2,2);
    Piece* pawn3 = new Pawn(1,0,pos3);
    Position pos4(5,6);
    Piece* pawn4 = new Pawn(0,0,pos4);   
 
    board[pos1] = pawn1;
    list<Position> moves = pawn1->getValidMoves(&board);
    TEST(moves.size() == 1);
    board[pos2] = pawn2;
    moves = pawn2->getValidMoves(&board);
    TEST(moves.size() == 2);
    board[pos3] = pawn3;
    moves = pawn1->getValidMoves(&board);
    board[pos4] = pawn4;
    moves = pawn2->getValidMoves(&board);
    TEST(moves.size() == 0);

    delete pawn1;
    delete pawn2;
    delete pawn3;
    delete pawn4;
	return success;
}

bool rookMove(ostream& os){
	bool success = true;

    chessBoard board;
    Position pos1(3,3);
    Piece* rook1 =  new Rook(0,1,pos1);
    Position pos2(3,7);
    Piece* rook2 = new Rook(1,1,pos2);
    Position pos3(2,7);
    Piece* rook3 = new Rook(1,1,pos3);
 
    board[pos1] = rook1;
    list<Position> moves = rook1->getValidMoves(&board);
    TEST(moves.size() == 14);
    board[pos2] = rook2;
    moves = rook1->getValidMoves(&board);
    TEST(moves.size() == 14);
    moves = rook2->getValidMoves(&board);
    TEST(moves.size() == 11);
    board[pos3] = rook3;
    moves = rook1->getValidMoves(&board);
    TEST(moves.size() == 14);
    moves = rook2->getValidMoves(&board);
    TEST(moves.size() == 8);
    moves = rook3->getValidMoves(&board);
    TEST(moves.size() == 9);

    delete rook1;
    delete rook2;
    delete rook3;
	return success;
}

bool knightMove(ostream& os){
	bool success = true;

    chessBoard board;
    Position pos1(3,3);
    Piece* knight1 =  new Knight(0,2,pos1);
    Position pos2(2,5);
    Piece* knight2 = new Knight(1,2,pos2);
    Position pos3(0,6);
    Piece* knight3 = new Knight(1,2,pos3);
 
    board[pos1] = knight1;
    list<Position> moves = knight1->getValidMoves(&board);
    TEST(moves.size() == 8);
    board[pos2] = knight2;
    moves = knight1->getValidMoves(&board);
    TEST(moves.size() == 8);
    moves = knight2->getValidMoves(&board);
    TEST(moves.size() == 8);
    board[pos3] = knight3;
    moves = knight1->getValidMoves(&board);
    TEST(moves.size() == 8);
    moves = knight2->getValidMoves(&board);
    TEST(moves.size() == 7);
    moves = knight3->getValidMoves(&board);
    TEST(moves.size() == 2);

    delete knight1;
    delete knight2;
    delete knight3;
	return success;
}

bool bishopMove(ostream& os){
	bool success = true;

    chessBoard board;
    Position pos1(3,3);
    Piece* bishop1 =  new Bishop(0,3,pos1);
    Position pos2(2,2);
    Piece* bishop2 = new Bishop(1,3,pos2);
    Position pos3(1,3);
    Piece* bishop3 = new Bishop(1,3,pos3);
 
    board[pos1] = bishop1;
    list<Position> moves = bishop1->getValidMoves(&board);
    TEST(moves.size() == 13);
    board[pos2] = bishop2;
    moves = bishop1->getValidMoves(&board);
    TEST(moves.size() == 11);
    moves = bishop2->getValidMoves(&board);
    TEST(moves.size() == 7);
    board[pos3] = bishop3;
    moves = bishop1->getValidMoves(&board);
    TEST(moves.size() == 11);
    moves = bishop2->getValidMoves(&board);
    TEST(moves.size() == 5);
    moves = bishop3->getValidMoves(&board);
    TEST(moves.size() == 6);

    delete bishop1;
    delete bishop2;
    delete bishop3;
	return success;
}

bool queenMove(ostream& os){
	bool success = true;

    chessBoard board;
    Position pos1(3,3);
    Piece* queen1 =  new Queen(0,5,pos1);
    Position pos2(2,2);
    Piece* queen2 = new Queen(1,5,pos2);
    Position pos3(1,3);
    Piece* queen3 = new Queen(1,5,pos3);
 
    board[pos1] = queen1;
    list<Position> moves = queen1->getValidMoves(&board);
    TEST(moves.size() == 27);
    board[pos2] = queen2;
    moves = queen1->getValidMoves(&board);
    TEST(moves.size() == 25);
    moves = queen2->getValidMoves(&board);
    TEST(moves.size() == 21);
    board[pos3] = queen3;
    moves = queen1->getValidMoves(&board);
    TEST(moves.size() == 24);
    moves = queen2->getValidMoves(&board);
    TEST(moves.size() == 19);
    moves = queen3->getValidMoves(&board);
    TEST(moves.size() == 16);

    delete queen1;
    delete queen2;
    delete queen3;
	return success;
}

bool kingMove(ostream& os){
	bool success = true;

    chessBoard board;
    Position pos1(3,3);
    Piece* king1 =  new King(0,4,pos1);
    Position pos2(3,2);
    Piece* pawn2 = new Pawn(0,0,pos2);
    Position pos3(2,2);
    Piece* pawn3 = new Pawn(1,0,pos3);
 
    board[pos1] = king1;
    list<Position> moves = king1->getValidMoves(&board);
    TEST(moves.size() == 8);
    board[pos2] = pawn2;
    moves = king1->getValidMoves(&board);
    TEST(moves.size() == 7);
    moves = pawn2->getValidMoves(&board);
    TEST(moves.size() == 1);
    board[pos3] = pawn3;
    moves = king1->getValidMoves(&board);
    TEST(moves.size() == 7);
    moves = pawn2->getValidMoves(&board);
    TEST(moves.size() == 0);
    moves = pawn3->getValidMoves(&board);
    TEST(moves.size() == 1);

    delete king1;
    delete pawn2;
    delete pawn3;
    return success;
}

