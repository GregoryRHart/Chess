#ifndef CHESS_CONTROLLER_H
#define CHESS_CONTROLLER_H

#include "chessFacade.h"
#include "ChessGuiDefines.h"
#include "IChessController.h"
#include "IChessPlayer.h"
#include "chessPlayerh.h"
#include "chessPlayerc.h"
#include <string>
using namespace std;

class chessController: public IChessController {
private:
	IChessView* view;
	IChessPlayer* player1;
	IChessPlayer* player2;
	chessFacade* facade;
	string fileName;
	bool selected;

public:

	chessController(int mode);

	/**
	 * Destructor
	 */
	~chessController();

	/**
	 * Indicate to the player that the user clicked on the given
	 * row and column with the mouse.
	 */
	void on_CellSelected(int row, int col, int button);

	///@param row where drag began
	///@param col where drag began
	void on_DragStart(int row,int col);

	///@param row where drag ended
	///@param col where drag ended
	///@return true if the drag resulted in a successful drop
	bool on_DragEnd(int row,int col);

	/**
	 * Handle when the user selected the new game button.
	 */
	void on_NewGame();

	/**
	 * Handle when the user selected the save game button.
	 */
	void on_SaveGame();

	/**
	 * Handle when the user selected the save game as button.
	 */
	void on_SaveGameAs();

	/**
	 * Handle when the user selected the load game button.
	 */
	void on_LoadGame();

	/**
	 * Handle when the user selected the undo move button.
	 */
	void on_UndoMove();

	/**
	 * Handle when the user selects to quit the game, either through the
	 * quit button, the close X button, or the file menu.
	 */
	void on_QuitGame();

	/**
	 * Handle when a timer event has been signaled.
	 */
	void on_TimerEvent();

	/**
	 * Set the IChessView that this IChessController will handle inputs for.
	 */
	void SetView(IChessView* view);

	void setUpBoard();

	void clearBoard();

	void unHighlight();

	void placePieces();
};

#endif

