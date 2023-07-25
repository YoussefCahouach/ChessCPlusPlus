#include "Piece.hpp"
#include "Chessboard.hpp"
#include <string>
#include <iostream>
using namespace std;

Piece::Piece()
{
	m_color = CPC_NONE;
	m_type = CPT_EMPTY;
}

//IN CASE OF ERROR RE-WRITE DEFAULT OPTION FOR SWITCH-CASE's
string Piece::pieceTypeToString(const ChessPieceType& m_type)
{
	string tipus;
	switch (m_type)
	{
	case CPT_King: tipus = "R";
		break;
	case CPT_Queen: tipus = "D";
		break;
	case CPT_Rook: tipus = "T";
		break;
	case CPT_Bishop: tipus = "A";
		break;
	case CPT_Knight: tipus = "C";
		break;
	case CPT_Pawn: tipus = "P";
		break;
	case CPT_EMPTY: tipus = "_";
		break;
	}
	return tipus;
}

string Piece::pieceColorToString(const ChessPieceColor& m_color)
{
	string tipus;
	switch (m_color)
	{
	case CPC_White: tipus = "0";
		break;
	case CPC_Black: tipus = "1";
		break;
	case CPC_NONE: tipus = "_";
		break;
	}
	return tipus;
}

ChessPieceType Piece::stringToPieceType(const string& type)
{
	ChessPieceType tipus = CPT_EMPTY;
	switch (type[0])
	{
	case 'R': tipus = CPT_King;
		break;
	case 'D': tipus = CPT_Queen;
		break;
	case 'T': tipus = CPT_Rook;
		break;
	case 'A': tipus = CPT_Bishop;
		break;
	case 'C': tipus = CPT_Knight;
		break;
	case 'P': tipus = CPT_Pawn;
		break;
	case '_': tipus = CPT_EMPTY;
		break;
	}
	return tipus;
}

ChessPieceColor Piece::stringToPieceColor(const string& color)
{
	ChessPieceColor tipus = CPC_NONE;
	switch (color[0])
	{
	case '0': tipus = CPC_White;
		break;
	case '1': tipus = CPC_Black;
		break;
	case '_': tipus = CPC_NONE;
		break;
	case 'w': tipus = CPC_White;
		break;
	case 'b': tipus = CPC_Black;
		break;
	}
	return tipus;
}

void Piece::RenderPiece(int x, int y)
{
	//DESCRIPTION:
	//S'encarrega de mostrar les peces en pantalla. 
	//PARAMETERS:
	//x/y: Les posicions x i y que ocupen a l'array.
	//RETURN: -

	//Fem la conversió per adaptar els pixels amb les posicions que hem obtés. 
	int cell_posX = CELL_INIT_X + (x * CELL_W);		
	int cell_posY = CELL_INIT_Y + (y * CELL_H);
	
	switch (m_type)
	{
	case CPT_King:
		if(CPC_White ==m_color)
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_KING_WHITE, cell_posX, cell_posY);
		else
			if(CPC_Black ==m_color)
				GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_KING_BLACK, cell_posX, cell_posY);
		break;
	case CPT_Queen:
		if (CPC_White == m_color)
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_QUEEN_WHITE, cell_posX, cell_posY);
		else
			if (CPC_Black == m_color)
				GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_QUEEN_BLACK, cell_posX, cell_posY);
		break;
	case CPT_Rook:
		if (CPC_White == m_color)
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_ROOK_WHITE, cell_posX, cell_posY);
		else
			if (CPC_Black == m_color)
				GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_ROOK_BLACK, cell_posX, cell_posY);
		break;
	case CPT_Bishop:
		if (CPC_White == m_color)
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_BISHOP_WHITE, cell_posX, cell_posY);
		else
			if (CPC_Black == m_color)
				GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_BISHOP_BLACK, cell_posX, cell_posY);
		break;
	case CPT_Knight:
		if (CPC_White == m_color)
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_KNIGHT_WHITE, cell_posX, cell_posY);
		else
			if (CPC_Black == m_color)
				GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_KNIGHT_BLACK, cell_posX, cell_posY);
		break;
	case CPT_Pawn: 
		if (CPC_White ==m_color)
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_PAWN_WHITE, cell_posX, cell_posY);
		else
			if (CPC_Black ==m_color)
				GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_PAWN_BLACK, cell_posX, cell_posY);
		break;
	case CPT_EMPTY:
		break;
	}
}