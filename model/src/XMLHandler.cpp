#include "XMLHandler.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "Pawn.h"
#include "CS240Exception.h"
#include <iostream>
using namespace std;

XMLHandler::XMLHandler(){
}

XMLHandler::~XMLHandler(){
}

void XMLHandler::save(string fileName, list<Move>& history, chessBoard& board){
	ofstream outFile(fileName.c_str());
	if(!outFile.is_open()){
		cout << fileName << " failed to open." << endl;
		return;
	}

	outFile << "<chessgame>" << endl;

	//Generates the board section of the XML
	printBoard(outFile, board);

	//Generates the history section of the XML
	printHistory(outFile, history);    

	outFile << "</chessgame>" << endl;

	outFile.close();
}

void XMLHandler::load(string fileName, list<Move>& history, chessBoard& board, 
		list<Piece*>& white, list<Piece*>& black){
	URLInputStream* stream = NULL;
	try{
		stream = new URLInputStream(fileName);
		HTMLTokenizer tokenizer(stream);
		cout << "Tokenizer Created" << endl;
		HTMLToken current = tokenizer.GetNextToken();
		string value = current.GetValue();
		StringUtil::ToLower(value);
		while(value.compare("board") != 0){
			current = tokenizer.GetNextToken();
			value = current.GetValue();
			StringUtil::ToLower(value);
		}
		loadBoard(tokenizer, board, white, black);

		current = tokenizer.GetNextToken();
		value = current.GetValue();
		StringUtil::ToLower(value);
		loadHistory(tokenizer, history);
	}
	catch(exception &e){
		cout << "Exception Occured: " << e.what() << endl;
		delete stream;
	}
	catch(CS240Exception &e){
		cout << "Exception Occured: " << e.GetMessage() << endl;
		delete stream;
	}
	catch(...){
		cout << "Unknown Exception Occured"  << endl;
		delete stream;
	}
	delete stream;
}

void XMLHandler::printBoard(ofstream& outFile, chessBoard& board){
	outFile << "<board>" << endl;
	string temp;
	for(int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			temp = printPiece(board(i,j));
			outFile << temp;
		}
	}
	outFile << "</board>" << endl;
}

void XMLHandler::printHistory(ofstream& outFile, list<Move>& history){

	outFile << "<History>" << endl;
	string temp;
	list<Move>::reverse_iterator it = history.rbegin();
	for(;it != history.rend(); it++){
		outFile << "<Move>" << endl;
		temp = printMove(*it);
		outFile << temp;
		outFile << "</Move>" << endl;
	}
	outFile << "</history>" << endl;    
}

string XMLHandler::printPiece(Piece* piece){
	if(piece != NULL){
		stringstream out;
		string str = "<piece type=\"";
		string temp = convertType(piece->getType());
		str += temp;
		str += "\" color=\"";
		temp = convertColor(piece->getColor());
		str += temp;
		str += "\" row=\"";
		out << piece->getPosition().getRow();
		str += out.str();
		str += "\" column=\"";
		out.str("");
		out << piece->getPosition().getCol();
		str += out.str();
		str += "\"/>\n";
		return str;
	}
	return "";
}

string XMLHandler::printMove(Move move){
	Position posi = move.getInit();
	Position posf = move.getFinal();
	stringstream out;
	string start = "<piece type=\"";
	string final;
	string temp = convertType(move.getType());
	start += temp;
	start += "\" color=\"";
	temp = convertColor(move.getColor());
	start += temp;
	start += "\" row=\"";
	final = start;
	out << posi.getRow();
	start += out.str();
	start += "\" column=\"";
	out.str("");
	out << posi.getCol();
	start += out.str();
	start += "\"/>\n";
	out.str("");
	out << posf.getRow();
	final += out.str();
	final += "\" column=\"";
	out.str("");
	out << posf.getCol();
	final += out.str();
	final += "\"/>\n";
	start += final;
	if(move.getCaptured()){
		string cap = "<piece type=\"";
		temp = convertType(move.getPieceCap());
		cap += temp;
		cap += "\" color=\"";
		temp = convertColor(!move.getColor());
		cap += temp;
		cap += "\" row=\"";
		out.str("");
		out << posf.getRow();
		cap += out.str();
		cap += "\" column=\"";
		out.str("");
		out << posf.getCol();
		cap += out.str();
		cap += "\"/>\n";
		start += cap;
	}
	return start;
}

string XMLHandler::convertType(int type){
	string str = "";
	switch (type){
	case 0:
		str = "pawn";
		break;
	case 1:
		str = "rook";
		break;
	case 2:
		str = "knight";
		break;
	case 3:
		str = "bishop";
		break;
	case 4:
		str = "king";
		break;
	case 5:
		str = "queen";
		break;
	}
	return str;
}

string XMLHandler::convertColor(int color){
	if(color == 0){
		return "white";
	} else{
		return "black";
	}
}

void XMLHandler::loadBoard(HTMLTokenizer& tokenizer, chessBoard& board,
		list<Piece*>& white, list<Piece*>& black){
	HTMLToken current = tokenizer.GetNextToken();
	string value = current.GetValue();
	StringUtil::ToLower(value);

	while(value.compare("board") != 0){
		if(value.compare("piece") == 0){
			loadPiece(current, board, white, black);
		}
		current = tokenizer.GetNextToken();
		value = current.GetValue();
		StringUtil::ToLower(value);
	}
	current = tokenizer.GetNextToken();
}

void XMLHandler::loadHistory(HTMLTokenizer& tokenizer, list<Move>& history){
	HTMLToken current = tokenizer.GetNextToken();
	string value = current.GetValue();
	StringUtil::ToLower(value);
	while(value.compare("history") != 0){
		if(value.compare("move") == 0){
			loadMove(tokenizer, history);
		}
		current = tokenizer.GetNextToken();
		value = current.GetValue();
		StringUtil::ToLower(value);
	}

}

void XMLHandler::loadPiece(HTMLToken current, chessBoard& board,
		list<Piece*>& white, list<Piece*>& black){
	int type = convertType(current.GetAttribute("TYPE"));
	int color = convertColor(current.GetAttribute("COLOR"));
	int row = atoi(current.GetAttribute("ROW").c_str());
	int col = atoi(current.GetAttribute("COLUMN").c_str());
	Position pos(row, col);
	Piece* piece;
	switch(type){
	case 0:
		piece = new Pawn(color,0,pos);
		break;
	case 1:
		piece = new Rook(color,1,pos);
		break;
	case 2:
		piece = new Knight(color,2,pos);
		break;
	case 3:
		piece = new Bishop(color,3,pos);
		break;
	case 4:
		piece = new King(color,4,pos);
		break;
	case 5:
		piece = new Queen(color,5,pos);
		break;
	}
	if(color == 0){
		if(type == 4){
			white.push_back(piece);
		} else {
			white.push_front(piece);
		}
	} else {
		if(type == 4){
			black.push_back(piece);
		} else {
			black.push_front(piece);
		}
	}
	board[pos] = piece;
}

void XMLHandler::loadPiece(HTMLToken current, int& row, int& col, int& color, int& type){
	type = convertType(current.GetAttribute("TYPE"));
	color = convertColor(current.GetAttribute("COLOR"));
	row = atoi(current.GetAttribute("ROW").c_str());
	col = atoi(current.GetAttribute("COLUMN").c_str());
}

void XMLHandler::loadMove(HTMLTokenizer& tokenizer, list<Move>& history){
	HTMLToken current = tokenizer.GetNextToken();
	string value = current.GetValue();
	StringUtil::ToLower(value);
	int count = 0;
	int row, col, rowi, coli, color, type, typeOther;
	bool cap = false;
	while(value.compare("move") != 0){
		if(value.compare("piece") == 0){
			if(count < 2){
				loadPiece(current, row, col, color, type);
				if(count == 0){
					rowi = row;
					coli = col;
				}
				count++;
			} else {
				cap = true;
				loadPiece(current, row, col, color, typeOther);
			}
		}
		current = tokenizer.GetNextToken();
		value = current.GetValue();
		StringUtil::ToLower(value);
	}
	Position orig(rowi, coli);
	Position final(row, col);
	if(cap){
		Move move(orig, final, !color, type, typeOther);
		history.push_front(move);
	} else {
		Move move(orig, final, color, type);
		history.push_front(move);
	}
}

int XMLHandler::convertType(string type){
	StringUtil::ToLower(type);
	if(type.compare("pawn") == 0){
		return 0;
	} else if(type.compare("rook") == 0){
		return 1;
	} else if(type.compare("knight") == 0){
		return 2;
	} else if(type.compare("bishop") == 0){
		return 3;
	} else if(type.compare("king") == 0){
		return 4;
	} else if(type.compare("queen") == 0){
		return 5;
	}
	return 6;
}

int XMLHandler::convertColor(string color){
	StringUtil::ToLower(color);
	if(color.compare("white") == 0){
		return 0;
	}
	return 1;
}

