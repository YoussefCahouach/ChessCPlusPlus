#ifndef Piece_hpp
#define Piece_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include "GameInfo.h"
#include "../GraphicManager.h"

using namespace std;

typedef enum {
    CPT_King,
    CPT_Queen,
    CPT_Rook,
    CPT_Bishop,
    CPT_Knight,
    CPT_Pawn,
    CPT_EMPTY
} ChessPieceType;

typedef enum {
    CPC_Black,
    CPC_White,
    CPC_NONE
} ChessPieceColor;

class Piece {
public:
    //Constructors and Destroyers
    Piece();
    ~Piece() {}

    //Getters i setters.
    void setTipus(ChessPieceType tipus) { m_type = tipus; };
    void setColor(ChessPieceColor color) { m_color = color; };
    ChessPieceColor getColor() const { return m_color; };
    ChessPieceType getTipus() const { return m_type; }

    //Convert from typedef enum to string.
    string pieceTypeToString(const ChessPieceType& m_type);
    string pieceColorToString(const ChessPieceColor& m_color);

    //Convert from string to typedef enum.
    ChessPieceType stringToPieceType(const string& type);
    ChessPieceColor stringToPieceColor(const string& color);
    
    void RenderPiece(int x, int y);

private:
    ChessPieceType  m_type;
    ChessPieceColor m_color;
};


#endif /* Piece_hpp */
