#ifndef I_CHESS_PLAYER_H
#define I_CHESS_PLAYER_H

/**
 * The IChessPlayer class provides an interface for a ChessController implementation to interact
 * with the player through, regardless of whether the player is a human or a computer.
 */

#include "IChessView.h"
#include "chessFacade.h"
#include <list>
#include "Position.h"

class IChessPlayer
{
protected:
	chessFacade* facade;
	IChessView* view;
	bool gameover;
public: //methods
	/**
	 * Indicate to the player that the user clicked on the given
	 * row and column with the mouse.
	 */
	IChessPlayer(chessFacade* facade):facade(facade),view(NULL),gameover(false){
	}

	virtual void on_CellSelected(int row, int col, bool& selected) = 0;

	/**
	 * Handle when the timeout duration has passed.
	 */
	virtual void on_TimerEvent() = 0; 

	void setView(IChessView* view){
		this->view = view;
	}

	void setFacade(chessFacade* facade){
		this->facade = facade;
	}

	void endTurn(){
		if(facade->checkmate()){
			view->SetStatusBar("Checkmate:  Game over");
			gameover = true;
		} else if(facade->check()){
			view->SetStatusBar("Check");
			if(facade->getTurn() == 1){
				view->SetTopLabel("Black's turn");
				view->SetBottomLabel("");
			} else {
				view->SetTopLabel("");
				view->SetBottomLabel("White's turn");
			}
		} else if(facade->stalemate()){
			view->SetStatusBar("Stalemat:  Game over");
			gameover = true;
		} else {
			view->SetStatusBar("");
			if(facade->getTurn() == 1){
				view->SetTopLabel("Black's turn");
				view->SetBottomLabel("");
			} else {
				view->SetTopLabel("");
				view->SetBottomLabel("White's turn");
			}
		}
	}

	bool getGameover(){
		return gameover;
	}

	void setGameover(){
		gameover = false;
	}
};

#endif
