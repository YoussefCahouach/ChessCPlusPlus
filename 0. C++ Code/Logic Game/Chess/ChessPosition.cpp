#include "ChessPosition.hpp"
#include "GameInfo.h"
#include <iostream>
#include <fstream>
#include <sstream>
/* Coordinate system:
    Y (rows)
  . ^
  . |  ***Black***
  4 |
  3 |
  2 |
  1 |  ***White***
 (0,0)----------> X (cols)
      a b c ...
*/

ChessPosition::ChessPosition(const string& pos) //Completat.
{
	m_posX = -1;
	switch (pos[0])
	{
	case 'a': m_posX = 0;
		break;
	case 'b': m_posX = 1;
		break;
	case 'c': m_posX = 2;
		break;
	case 'd': m_posX = 3;
		break;
	case 'e': m_posX = 4;
		break;
	case 'f': m_posX = 5;
		break;
	case 'g': m_posX = 6;
		break;
	case 'h': m_posX = 7;
		break;
	}
	m_posY = -1;
	switch (pos[1])
	{
	case '8': m_posY = 7;
		break;
	case '7': m_posY = 6;
		break;
	case '6': m_posY = 5;
		break;
	case '5': m_posY = 4;
		break;
	case '4': m_posY = 3;
		break;
	case '3': m_posY = 2;
		break;
	case '2': m_posY = 1;
		break;
	case '1': m_posY = 0;
		break;
	}
}

string ChessPosition::posToString(int pos) //Completat.
{
	string str = to_string(pos);
	return str;
	
}

bool ChessPosition::operator==(const ChessPosition& pos) const //Completat.
{
	return ((m_posX == pos.m_posX) && (m_posY == pos.m_posY));
}

ostream& operator<<(ostream& output, const ChessPosition& pos) //Completat.
{
	string posXString;
	switch (pos.getPosX())
	{
	case 0: posXString = "a";
		break;
	case 1: posXString = "b";
		break;
	case 2: posXString = "c";
		break;
	case 3: posXString = "d";
		break;
	case 4: posXString = "e";
		break;
	case 5: posXString = "f";
		break;
	case 6: posXString = "g";
		break;
	case 7: posXString = "h";
		break;
	}
	string posYString;
	posYString = to_string(pos.getPosY());

	string posString;
	posString = posXString + posYString;
	output << posString;
	return output;
}