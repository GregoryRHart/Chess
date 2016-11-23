#include "chessController.h"
#include <iostream>
using namespace std;

chessController::chessController(int mode):view(NULL),fileName(""),selected(false){
	facade = new chessFacade;
	switch(mode){
	case 1:
		player1 = new chessPlayerh(facade);
		player2 = new chessPlayerh(facade);
		break;
	case 2:
		player1 = new chessPlayerh(facade);
		player2 = new chessPlayerc(facade);
		break;
	case 3:
		player1 = new chessPlayerc(facade);
		player2 = new chessPlayerh(facade);
		break;
	case 4:
		player1 = new chessPlayerc(facade);
		player2 = new chessPlayerc(facade);
		break;
	default:
		cout << "Bad input" << endl;
	}
}

/**
 * Destructor
 */
chessController::~chessController(){
	delete player1;
	delete player2;
	delete facade;
}

/**
 * Indicate to the player that the user clicked on the given
 * row and column with the mouse.
 */
void chessController::on_CellSelected(int row, int col, int button){
	if(facade->getTurn() == 0){
		player1->on_CellSelected(row,col,selected);
	} else {
		player2->on_CellSelected(row,col,selected);
	}
}

///@param row where drag began
///@param col where drag began
void chessController::on_DragStart(int row,int col){}

///@param row where drag ended
///@param col where drag ended
///@return true if the drag resulted in a successful drop
bool chessController::on_DragEnd(int row,int col){}

/**
 * Handle when the user selected the new game button.
 */
void chessController::on_NewGame(){
	unHighlight();
	delete facade;
	facade = new chessFacade;
	player1->setFacade(facade);
	player2->setFacade(facade);
	clearBoard();
	setUpBoard();
	player1->setGameover();
}

/**
 * Handle when the user selected the save game button.
 */
void chessController::on_SaveGame(){
	unHighlight();
	if(fileName.compare("") == 0){
		string file = view->SelectSaveFile();
		if(file.compare("") != 0){
			facade->save(file);
			fileName = file;
		}
	} else {
		facade->save(fileName);
	}
}

/**
 * Handle when the user selected the save game as button.
 */
void chessController::on_SaveGameAs(){
	unHighlight();
	string file = view->SelectSaveFile();
	if(file.compare("") != 0){
		facade->save(file);
		fileName = file;
	}
}

/**
 * Handle when the user selected the load game button.
 */
void chessController::on_LoadGame(){
	unHighlight();
	string file = view->SelectLoadFile();
	if(file.compare("") != 0){
		facade->load(file);
		fileName = file;
		clearBoard();
		placePieces();
		player1->setGameover();
		player1->endTurn();
	}
}

/**
 * Handle when the user selected the undo move button.
 */
void chessController::on_UndoMove(){
	unHighlight();
	list<Position> move = facade->undo();
	if(!move.empty()){
		Position orig = move.back();
		Position final = move.front();
		view->ClearPiece(orig.getRow(),orig.getCol());
		view->ClearPiece(final.getRow(),final.getCol());
		int color = facade->getColor(orig);
		int piece = facade->getPiece(orig);
		ImageName image = (ImageName)(2*piece+4+color);
		view->PlacePiece(orig.getRow(), orig.getCol(), image);
		color = facade->getColor(final);
		piece = facade->getPiece(final);
		image = (ImageName)(2*piece+4+color);
		view->PlacePiece(final.getRow(), final.getCol(), image);
		player1->endTurn();
	}
}

/**
 * Handle when the user selects to quit the game, either through the
 * quit button, the close X button, or the file menu.
 */
void chessController::on_QuitGame(){
}

/**
 * Handle when a timer event has been signaled.
 */
void chessController::on_TimerEvent(){
	if(!player1->getGameover()){
		if(facade->getTurn() == 0){
			player1->on_TimerEvent();
		} else {
			player2->on_TimerEvent();
		}
	}
}

/**
 * Set the IChessView that this IChessController will handle inputs for.
 */
void chessController::SetView(IChessView* view){
	this->view = view;
	player1->setView(view);
	player2->setView(view);
	setUpBoard();
}

void chessController::setUpBoard(){
	for(int i = 0; i<8; i++){
		view->PlacePiece(1,i,B_PAWN);
	}
	for(int i = 0; i<8; i++){
		view->PlacePiece(6,i,W_PAWN);
	}
	view->PlacePiece(0,0,B_ROOK);
	view->PlacePiece(0,7,B_ROOK);
	view->PlacePiece(0,1,B_KNIGHT);
	view->PlacePiece(0,6,B_KNIGHT);
	view->PlacePiece(0,2,B_BISHOP);
	view->PlacePiece(0,5,B_BISHOP);
	view->PlacePiece(0,3,B_QUEEN);
	view->PlacePiece(0,4,B_KING);
	view->PlacePiece(7,0,W_ROOK);
	view->PlacePiece(7,7,W_ROOK);
	view->PlacePiece(7,1,W_KNIGHT);
	view->PlacePiece(7,6,W_KNIGHT);
	view->PlacePiece(7,2,W_BISHOP);
	view->PlacePiece(7,5,W_BISHOP);
	view->PlacePiece(7,3,W_QUEEN);
	view->PlacePiece(7,4,W_KING);
	view->SetBottomLabel("White's Turn");
}

void chessController::clearBoard(){
	for(int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			view->ClearPiece(i,j);
		}
	}
}

void chessController::unHighlight(){
	for(int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			view->UnHighlightSquare(i,j);
		}
	}
}

void chessController::placePieces(){
	Position pos;
	int color;
	int piece;
	ImageName image;
	for(int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			pos.setRow(i);
			pos.setCol(j);
			color = facade->getColor(pos);
			if(color != 10){
				piece = facade->getPiece(pos);
				image = (ImageName)(2*piece+4+color);
				view->PlacePiece(pos.getRow(), pos.getCol(), image);
			}
		}
	}
}

