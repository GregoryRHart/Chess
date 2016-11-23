model/obj/King.o: model/src/King.cpp model/inc/King.h model/inc/Piece.h \
 model/inc/Position.h model/inc/chessBoard.h
model/obj/Bishop.o: model/src/Bishop.cpp model/inc/Bishop.h \
 model/inc/Piece.h model/inc/Position.h model/inc/chessBoard.h
model/obj/Piece.o: model/src/Piece.cpp model/inc/Piece.h \
 model/inc/Position.h model/inc/chessBoard.h
model/obj/Pawn.o: model/src/Pawn.cpp model/inc/Pawn.h model/inc/Piece.h \
 model/inc/Position.h model/inc/chessBoard.h
model/obj/chessBoard.o: model/src/chessBoard.cpp model/inc/chessBoard.h \
 model/inc/Piece.h model/inc/Position.h
model/obj/Position.o: model/src/Position.cpp model/inc/Position.h
model/obj/XMLHandler.o: model/src/XMLHandler.cpp model/inc/XMLHandler.h \
 utils/inc/StringUtil.h utils/inc/URLInputStream.h \
 utils/inc/InputStream.h utils/inc/HTMLTokenizer.h \
 utils/inc/URLInputStream.h utils/inc/HTMLToken.h utils/inc/HTMLToken.h \
 model/inc/Move.h model/inc/Position.h model/inc/Piece.h \
 model/inc/chessBoard.h model/inc/King.h model/inc/Queen.h \
 model/inc/Bishop.h model/inc/Knight.h model/inc/Rook.h model/inc/Pawn.h \
 view/inc/CS240Exception.h
model/obj/Knight.o: model/src/Knight.cpp model/inc/Knight.h \
 model/inc/Piece.h model/inc/Position.h model/inc/chessBoard.h
model/obj/Move.o: model/src/Move.cpp model/inc/Move.h \
 model/inc/Position.h model/inc/Piece.h model/inc/chessBoard.h
model/obj/Rook.o: model/src/Rook.cpp model/inc/Rook.h model/inc/Piece.h \
 model/inc/Position.h model/inc/chessBoard.h
model/obj/chessFacade.o: model/src/chessFacade.cpp \
 model/inc/chessFacade.h model/inc/Position.h model/inc/chessBoard.h \
 model/inc/Piece.h model/inc/Move.h model/inc/King.h model/inc/Queen.h \
 model/inc/Bishop.h model/inc/Knight.h model/inc/Rook.h model/inc/Pawn.h \
 model/inc/XMLHandler.h utils/inc/StringUtil.h utils/inc/URLInputStream.h \
 utils/inc/InputStream.h utils/inc/HTMLTokenizer.h \
 utils/inc/URLInputStream.h utils/inc/HTMLToken.h utils/inc/HTMLToken.h
model/obj/Queen.o: model/src/Queen.cpp model/inc/Queen.h \
 model/inc/Piece.h model/inc/Position.h model/inc/chessBoard.h
controller/obj/chessController.o: controller/src/chessController.cpp \
 controller/inc/chessController.h model/inc/chessFacade.h \
 model/inc/Position.h model/inc/chessBoard.h model/inc/Piece.h \
 model/inc/Move.h model/inc/King.h model/inc/Queen.h model/inc/Bishop.h \
 model/inc/Knight.h model/inc/Rook.h model/inc/Pawn.h \
 view/inc/ChessGuiDefines.h controller/inc/IChessController.h \
 view/inc/IChessView.h view/inc/ChessGui.h view/inc/ChessGuiDefines.h \
 view/inc/ChessGuiBoard.h view/inc/ChessGuiBoardCell.h \
 controller/inc/IChessPlayer.h controller/inc/chessPlayerh.h \
 controller/inc/chessPlayerc.h
controller/obj/chessPlayerh.o: controller/src/chessPlayerh.cpp \
 controller/inc/chessPlayerh.h controller/inc/IChessPlayer.h \
 view/inc/IChessView.h view/inc/ChessGui.h view/inc/ChessGuiDefines.h \
 view/inc/ChessGuiBoard.h view/inc/ChessGuiBoardCell.h \
 model/inc/chessFacade.h model/inc/Position.h model/inc/chessBoard.h \
 model/inc/Piece.h model/inc/Move.h model/inc/King.h model/inc/Queen.h \
 model/inc/Bishop.h model/inc/Knight.h model/inc/Rook.h model/inc/Pawn.h
controller/obj/chessPlayerc.o: controller/src/chessPlayerc.cpp \
 controller/inc/chessPlayerc.h controller/inc/IChessPlayer.h \
 view/inc/IChessView.h view/inc/ChessGui.h view/inc/ChessGuiDefines.h \
 view/inc/ChessGuiBoard.h view/inc/ChessGuiBoardCell.h \
 model/inc/chessFacade.h model/inc/Position.h model/inc/chessBoard.h \
 model/inc/Piece.h model/inc/Move.h model/inc/King.h model/inc/Queen.h \
 model/inc/Bishop.h model/inc/Knight.h model/inc/Rook.h model/inc/Pawn.h
