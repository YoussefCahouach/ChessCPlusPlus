#ifndef Chessboard_hpp
#define Chessboard_hpp

#include <stdio.h>
#include "Piece.hpp"
#include "GameInfo.h"
#include "../GraphicManager.h"


class Chessboard {

public:
    //Constructors i destructors.
    Chessboard();
    ~Chessboard();

    //Funcions esencials pel funcionament del Caronte.
    ChessPieceColor GetPieceColorAtPos(const ChessPosition& pos) const;
    ChessPieceType GetPieceTypeAtPos(const ChessPosition& pos) const;

    //Funcions extra.
    string fromIntToLetter(int posX) const;
    int fromLetterToInt(const string& lletra) const;
    int fromStringToInt(const string& posicioXString) const;
    int checkPosition(const ChessPosition& pos, int i, int j) const;


    void LoadBoardFromFile(const string& path);

    //Functions Related to valid moves.
    VecOfPositions getValidMovesKing(const ChessPosition& pos, VecOfPositions& vecMoviments) const;
    VecOfPositions getValidMovesQueen(const ChessPosition& pos, VecOfPositions& vecMoviments) const;
    VecOfPositions getValidMovesBishop(const ChessPosition& pos, VecOfPositions& vecMoviments) const;
    VecOfPositions getValidMovesKnight(const ChessPosition& pos, VecOfPositions& vecMoviments) const;
    VecOfPositions getValidMovesRook(const ChessPosition& pos, VecOfPositions& vecMoviments) const;
    VecOfPositions getValidMovesPawn(const ChessPosition& pos, VecOfPositions& vecMoviments) const;
    VecOfPositions GetValidMoves(const ChessPosition& pos) const;

    bool MovePiece(const ChessPosition& posFrom, const ChessPosition& posTo);
    string ToString() const;


    //Noves funcions (Segona Part)
    void Render();
    bool gameState(int m_turn);
    ChessPosition conversorPosition(int posX, int posY);
    void displayValidMoves(int posX, int posY);

    ChessPosition getPosInicial() const { return m_posInicial; }
    void setPosInicial(const ChessPosition& posInicial) { m_posInicial = posInicial; }
    
    int getTorn() const { return m_turn; }
    void setTorn(const int torn) { m_turn = torn; }
    
private:
    Piece m_board[NUM_COLS][NUM_ROWS];
    vector<ChessPosition> m_moves;
    int static const LIM_MIN = 0;
    int static const LIM_MAX = 7;
    int static const PIECE_MAX = 32;
    ChessPosition m_posInicial;
    int m_turn;


};

ifstream& operator>>(ifstream& input, Piece& p);

#endif /* Chessboard_hpp */