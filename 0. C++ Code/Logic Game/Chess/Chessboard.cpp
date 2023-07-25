#include "Chessboard.hpp"
#include "ChessPosition.hpp"
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
using namespace std;


//Les funcions tenen el mateix ordre que l'arxiu "Chessboard.hpp".

Chessboard::Chessboard() //Constructor que s'encarrega de inicialitzar el tauler de joc.
{	
	for (int i = 0; i < NUM_COLS; i++)
		for (int j = 0; j < NUM_ROWS; j++)
		{
			m_board[i][j].setTipus(CPT_EMPTY);
			m_board[i][j].setColor(CPC_NONE);
		}
	m_moves.clear();
	m_turn = CPC_White;
	
}

Chessboard::~Chessboard() //Destructor
{
	m_moves.clear();
}

ChessPieceColor Chessboard::GetPieceColorAtPos(const ChessPosition& pos) const
{
	return m_board[pos.getPosX()][pos.getPosY()].getColor();
}

ChessPieceType Chessboard::GetPieceTypeAtPos(const ChessPosition& pos) const
{
	return m_board[pos.getPosX()][pos.getPosY()].getTipus();
}

string Chessboard::fromIntToLetter(int posX) const
{
	//DESCRIPTION:
	//Conversor que s'encarrega de traduir les posicions n�meriques en posicions alfabetiques.
	//PARAMETERS:
	//posX: Un nombre enter que pasem com a parametre, que despr�s el retornarem en forma de lletra.
	//letter: Un string que guardar� una lletra qualsevol del switch case.
	//RETURN:
	//Retorna l'string creat al principi de la funci�, retorna la posici� alfabetica.
	string letter = "_";
	switch (posX)
	{
	case 1: letter = "a";
		break;
	case 2: letter = "b";
		break;
	case 3: letter = "c";
		break;
	case 4: letter = "d";
		break;
	case 5: letter = "e";
		break;
	case 6: letter = "f";
		break;
	case 7: letter = "g";
		break;
	case 8: letter = "h";
		break;
	}
	return letter;
}

int Chessboard::fromStringToInt(const string& posicioXString) const
{
	//DESCRIPTION:
	//Conversor que s'encarrega de traduir les posicions n�meriques (en format string) en posicions numeriques (en format enter).
	//PARAMETERS:
	//lletra: Un string que pasem com a parametre, que despr�s el retornarem en forma d'enter.
	//posX: Un string que guardar� una posici� qualsevol del switch case.
	//RETURN:
	//Retorna l'enter creat al principi de la funci�, retorna la posici� alfabetica.
	int posX = -1;
	switch (posicioXString[0])
	{
	case '1': posX = 0;
		break;
	case '2': posX = 1;
		break;
	case '3': posX = 2;
		break;
	case '4': posX = 3;
		break;
	case '5': posX = 4;
		break;
	case '6': posX = 5;
		break;
	case '7': posX = 6;
		break;
	case '8': posX = 7;
		break;
	}
	return posX;
}

int Chessboard::fromLetterToInt(const string& lletra) const
{
	//DESCRIPTION:
	//Converteix una posici� alfabetica en una posici� numerica, per poder guardar la posici� en el vector m_board.
	//PARAMETERS:
	//lletra: un string que pasem com a parametre, que despr�s el retornarem en forma d'enter.
	//posX: un nombre enter que guardar� un numero qualsevol del switch case.
	//RETURN:
	//Retorna el enter creat al principi de la funci�, retorna la posici� numerica.
	int posX = -1;
	switch (lletra[0])
	{
	case 'a': posX = 0;
		break;
	case 'b': posX = 1;
		break;
	case 'c': posX = 2;
		break;
	case 'd': posX = 3;
		break;
	case 'e': posX = 4;
		break;
	case 'f': posX = 5;
		break;
	case 'g': posX = 6;
		break;
	case 'h': posX = 7;
		break;
	}
	return posX;
}

int Chessboard::checkPosition(const ChessPosition& pos, int i, int j) const
{
	//DESCRIPTION:
	//Comprova si la posici� a la qual volem anar est� buida o si hi ha una pe�a del color contrari al nostre que puguem eliminar, de manera que poguem ocupar
	//aquella posici�.
	//PARAMETERS:
	//pos: Objecte de tipus ChessPosition que indica la posici� en la qual estem, que ens servir� per comparar el color de les peces.
	//i/j: Dues variables les quals simulen una possible posici� que podem ocupar, ens ajudar� a comprovar el color de la pe�a i si est� ocupada o no.
	//RETURN:
	//Retorna 0 si la pe�a esta buida, retorna 1 si la pe�a es de color contrari al nostre i -1 quan la pe�a es del mateix color al nostre.

	if (m_board[i][j].getTipus() == CPT_EMPTY)
		return 0;
	else
		if (m_board[pos.getPosX()][pos.getPosY()].getColor() != m_board[i][j].getColor())
			return 1;
		else
			return -1;

}

void Chessboard::LoadBoardFromFile(const string& path) //C�rrega d'un fitxer guardat al tauler.
{
	string color, infoGeneral;
	string tipusPiece, posXString, posYString;
	int posX, posY;

	fstream fitxerChess;
	fitxerChess.open(path);	//Obrim el fitxer pasat com a parametre. 
	if (fitxerChess.is_open()) //Comprovem que el fitxer est� obert.
	{
		fitxerChess >> color >> infoGeneral;
		while (fitxerChess)								//Bucle fins que finalitzi tot el document.
		{	//Example -> 0. Ra4

			color = color[0];							//Seleccionem nom�s el n�mero.
			tipusPiece = infoGeneral[0];				//Seleccionem nom�s el tipus de pe�a.
			posXString = infoGeneral[1];				//Seleccionem nom�s la posici� X.
			posYString = infoGeneral[2];				//Seleccionem nom�s la posici� Y.
			//Conversi�ns
			posX = fromLetterToInt(posXString);			
			posY = fromStringToInt(posYString);

			m_board[posX][posY].setTipus(m_board[posX][posY].stringToPieceType(tipusPiece));
			m_board[posX][posY].setColor(m_board[posX][posY].stringToPieceColor(color));
			fitxerChess >> color >> infoGeneral;
		}
		fitxerChess.close();
	}
}

VecOfPositions Chessboard::getValidMovesKing(const ChessPosition& pos, VecOfPositions& vecMoviments) const
{
	//En aquest cas, el moviment del rey ha sigut desglosat en 8 condicions, analitzant cadascuna d'elles, de forma que en aquest cas no necessitem
	//de cap bucle.

	vecMoviments.clear();
	int i = 0, j = 0;

	//An�lisi del moviment nord.
	if (pos.getPosY() < LIM_MAX)			//Comprovem que la pe�a pot avan�ar almenys una posici� endevant. 
	{
		//Realitzem les operacions necessaries i les afegim al vector que hem passat com a parametre.
		i = pos.getPosX();
		j = pos.getPosY() + 1;
		if (checkPosition(pos, i, j) != -1)
		{
			string posX = fromIntToLetter(i + 1);
			string posY = to_string(j + 1);
			vecMoviments.push_back(posX += posY);
		}
	}

	//An�lisi del moviment sud.
	if (pos.getPosY() > LIM_MIN)			//Comprovem que la pe�a pot avan�ar almenys una posici� en darrere. 
	{
		i = pos.getPosX();
		j = pos.getPosY() - 1;
		if (checkPosition(pos, i, j) != -1)
		{
			string posX = fromIntToLetter(i + 1);
			string posY = to_string(j + 1);
			vecMoviments.push_back(posX += posY);
		}
	}

	//An�lisi del moviment oest.
	if (pos.getPosX() > LIM_MIN)			//Comprovem que la pe�a pot avan�ar almenys una posici� a l'esquerra. 
	{
		i = pos.getPosX() - 1;
		j = pos.getPosY();
		if (checkPosition(pos, i, j) != -1)
		{
			string posX = fromIntToLetter(i + 1);
			string posY = to_string(j + 1);
			vecMoviments.push_back(posX += posY);
		}
	}

	//An�lisi del moviment est.
	if (pos.getPosX() < LIM_MAX)			//Comprovem que la pe�a pot avan�ar almenys una posici� a la dreta. 
	{
		i = pos.getPosX() + 1;
		j = pos.getPosY();
		if (checkPosition(pos, i, j) != -1)
		{
			string posX = fromIntToLetter(i + 1);
			string posY = to_string(j + 1);
			vecMoviments.push_back(posX += posY);
		}
	}

	//An�lisi del moviment diagonal superior-dreta.
	if (pos.getPosX() < LIM_MAX && pos.getPosY() < LIM_MAX)		//Comprovem que la pe�a pot avan�ar almenys una posici� en diagonal.
	{
		i = pos.getPosX() + 1;
		j = pos.getPosY() + 1;
		if (checkPosition(pos, i, j) != -1)
		{
			string posX = fromIntToLetter(i + 1);
			string posY = to_string(j + 1);
			vecMoviments.push_back(posX += posY);
		}
	}

	//An�lisi del moviment diagonal inferior-dreta.
	if (pos.getPosX() < LIM_MAX && pos.getPosY() > LIM_MIN)		//Comprovem que la pe�a pot avan�ar almenys una posici� en diagonal.
	{
		i = pos.getPosX() + 1;
		j = pos.getPosY() - 1;
		if (checkPosition(pos, i, j) != -1)
		{
			string posX = fromIntToLetter(i + 1);
			string posY = to_string(j + 1);
			vecMoviments.push_back(posX += posY);
		}
	}

	//An�lisi del moviment diagonal superior-esquerra.
	if (pos.getPosX() > LIM_MIN && pos.getPosY() < LIM_MAX)		//Comprovem que la pe�a pot avan�ar almenys una posici� en diagonal.
	{
		i = pos.getPosX() - 1;
		j = pos.getPosY() + 1;
		if (checkPosition(pos, i, j) != -1)
		{
			string posX = fromIntToLetter(i + 1);
			string posY = to_string(j + 1);
			vecMoviments.push_back(posX += posY);
		}
	}

	//An�lisi del moviment diagonal inferior-esquerra.
	if (pos.getPosX() > LIM_MIN && pos.getPosY() > LIM_MIN)		//Comprovem que la pe�a pot avan�ar almenys una posici� en diagonal.
	{
		i = pos.getPosX() - 1;
		j = pos.getPosY() - 1;
		if (checkPosition(pos, i, j) != -1)
		{
			string posX = fromIntToLetter(i + 1);
			string posY = to_string(j + 1);
			vecMoviments.push_back(posX += posY);
		}
	}
	return vecMoviments;
}

VecOfPositions Chessboard::getValidMovesQueen(const ChessPosition& pos, VecOfPositions& vecMoviments) const
{
	vecMoviments.clear();
	vector<ChessPosition> aux;

	//Fem �s de les funcions de l'alfil i del cavall, de forma que obtinim dos vectos que els unim.
	vecMoviments = getValidMovesBishop(pos, vecMoviments);
	aux = getValidMovesRook(pos, aux);
	
	vecMoviments.reserve(vecMoviments.size() + aux.size());
	vecMoviments.insert(vecMoviments.end(), aux.begin(), aux.end());

	return vecMoviments;
}


VecOfPositions Chessboard::getValidMovesBishop(const ChessPosition& pos, VecOfPositions& vecMoviments) const
{
	vecMoviments.clear();
	bool obstacle = false;

	//An�lisi del moviment diagonal superior-dreta.
	if (pos.getPosX() < LIM_MAX && pos.getPosY() < LIM_MAX) 
	{
		for (int i = pos.getPosX() + 1, j = pos.getPosY() + 1; i < NUM_COLS && j < NUM_ROWS && !obstacle; i++, j++)
		{
			if (checkPosition(pos, i, j) != -1)
			{
				string posX = fromIntToLetter(i + 1); 
				string posY = to_string(j + 1);
				vecMoviments.push_back(posX += posY);

				if (checkPosition(pos, i, j) == 1)
					obstacle = true;
			}
			else
				obstacle = true;
		}
	}

	//An�lisi del moviment diagonal inferior-esquerra.
	obstacle = false;
	if (pos.getPosX() > LIM_MIN && pos.getPosY() > LIM_MIN)
	{
		for (int i = pos.getPosX() - 1, j = pos.getPosY() - 1; i >= 0 && j >= 0 && !obstacle; i--, j--)
		{
			if (checkPosition(pos, i, j) != -1)
			{
				string posX = fromIntToLetter(i + 1);
				string posY = to_string(j + 1);
				vecMoviments.push_back(posX += posY);

				if (checkPosition(pos, i, j) == 1)
					obstacle = true;
			}
			else
				obstacle = true;
		}
	}

	//An�lisi del moviment diagonal superior-esquerra.
	obstacle = false;
	if (pos.getPosX() > LIM_MIN && pos.getPosY() < LIM_MAX)
	{
		for (int i = pos.getPosX() - 1, j = pos.getPosY() + 1; i >= 0 && j < NUM_ROWS && !obstacle; i--, j++)
		{
			if (checkPosition(pos, i, j) != -1)
			{
				string posX = fromIntToLetter(i + 1);
				string posY = to_string(j + 1);
				vecMoviments.push_back(posX += posY);

				if (checkPosition(pos, i, j) == 1)
					obstacle = true;
			}
			else
				obstacle = true;
		}
	}

	//An�lisi del moviment diagonal inferior-dreta.
	obstacle = false;
	if (pos.getPosX() >= LIM_MIN && pos.getPosY() <= LIM_MAX)
	{
		for (int i = pos.getPosX() + 1, j = pos.getPosY() - 1; i < NUM_COLS && j >= 0 && !obstacle; i++, j--)
		{
			if (checkPosition(pos, i, j) != -1)
			{
				string posX = fromIntToLetter(i + 1);
				string posY = to_string(j + 1);
				vecMoviments.push_back(posX += posY);

				if (checkPosition(pos, i, j) == 1)
					obstacle = true;
			}
			else
				obstacle = true;
		}
	}
	return vecMoviments;
}
VecOfPositions Chessboard::getValidMovesKnight(const ChessPosition& pos, VecOfPositions& vecMoviments) const
{
	vecMoviments.clear();
	int i = 0;
	int j = 0;

	// +1 Despla�ament a la dreta.
	i = pos.getPosX() + 1;
	if (i < NUM_COLS)
	{
		// +2 Despla�aments amunt.
		j = pos.getPosY() + 2;
		if (j < NUM_ROWS)
		{
			if (checkPosition(pos, i, j) != -1)
			{
				string posX = fromIntToLetter(i + 1);
				string posY = to_string(j + 1);
				vecMoviments.push_back(posX += posY);
			}
		}
		// +2 Despla�aments avall.
		j = pos.getPosY() - 2;
		if (j >= 0)
		{
			if (checkPosition(pos, i, j) != -1)
			{
				string posX = fromIntToLetter(i + 1);
				string posY = to_string(j + 1);
				vecMoviments.push_back(posX += posY);
			}
		}
	}

	// +1 Despla�ament a l'esquerra.
	i = pos.getPosX() - 1;
	if (i >= LIM_MIN)
	{
		// +2 Despla�aments amunt.
		j = pos.getPosY() + 2;
		if (j < NUM_ROWS)
		{
			if (checkPosition(pos, i, j) != -1)
			{
				string posX = fromIntToLetter(i + 1);
				string posY = to_string(j + 1);
				vecMoviments.push_back(posX += posY);
			}
		}

		// +2 Despla�aments avall.
		j = pos.getPosY() - 2;
		if (j >= LIM_MIN)
		{
			if (checkPosition(pos, i, j) != -1)
			{
				string posX = fromIntToLetter(i + 1);
				string posY = to_string(j + 1);
				vecMoviments.push_back(posX += posY);
			}
		}
	}
	
	// +2 Despla�aments a la dreta.
	i = pos.getPosX() + 2;
	if (i < NUM_COLS)
	{
		// +1 Despla�ament amunt.
		j = pos.getPosY() + 1;
		if (j < NUM_ROWS)
		{
			if (checkPosition(pos, i, j) != -1)
			{
				string posX = fromIntToLetter(i + 1);
				string posY = to_string(j + 1);
				vecMoviments.push_back(posX += posY);
			}
		}

		// +1 Despla�ament avall.
		j = pos.getPosY() - 1;
		if (j >= LIM_MIN)
		{
			if (checkPosition(pos, i, j) != -1)
			{
				string posX = fromIntToLetter(i + 1);
				string posY = to_string(j + 1);
				vecMoviments.push_back(posX += posY);
			}
		}
	}

	// +2 Despla�aments a l'esquerra.
	i = pos.getPosX() - 2;
	if (i >= LIM_MIN)
	{
		// +1 Despla�ament amunt.
		j = pos.getPosY() + 1;
		if (j < NUM_ROWS)
		{
			if (checkPosition(pos, i, j) != -1)
			{
				string posX = fromIntToLetter(i + 1);
				string posY = to_string(j + 1);
				vecMoviments.push_back(posX += posY);
			}
		}

		// +1 Despla�ament avall.
		j = pos.getPosY() - 1;
		if (j >= LIM_MIN)
		{
			if (checkPosition(pos, i, j) != -1)
			{
				string posX = fromIntToLetter(i + 1);
				string posY = to_string(j + 1);
				vecMoviments.push_back(posX += posY);
			}
		}
	}
	return vecMoviments;
}
VecOfPositions Chessboard::getValidMovesRook(const ChessPosition& pos, VecOfPositions& vecMoviments) const
{
	vecMoviments.clear(); 
	bool obstacle = false;

	//An�lisi del moviment horitzontal dreta.
	if (pos.getPosX() < LIM_MAX)
	{
		for (int i = pos.getPosX()+1; i < NUM_COLS && !obstacle; i++)
		{
			if (checkPosition(pos, i, pos.getPosY()) != -1)
			{
				string posX = fromIntToLetter(i + 1);
				string posY = to_string(pos.getPosY() + 1);
				vecMoviments.push_back(posX += posY);

				if (checkPosition(pos, i, pos.getPosY()) == 1)
					obstacle = true;
			}
			else
				obstacle = true;
		}
	}

	//An�lisi del moviment horitzontal esquerra.
	obstacle = false;
	if (pos.getPosX() > LIM_MIN)
	{
		for (int i = pos.getPosX() -1 ; i >= 0 && !obstacle; i--)
		{
			if (checkPosition(pos, i, pos.getPosY()) != -1)
			{
				string posX = fromIntToLetter(i + 1);
				string posY = to_string(pos.getPosY() + 1);
				vecMoviments.push_back(posX += posY);

				if (checkPosition(pos, i, pos.getPosY()) == 1)
					obstacle = true;
			}
			else
				obstacle = true;
		}
	}

	//An�lisi del moviment vertical amunt.
	obstacle = false;
	if(pos.getPosY() < LIM_MAX)
	{
		for (int j = pos.getPosY() + 1; j < NUM_ROWS && !obstacle; j++)
		{
			if (checkPosition(pos, pos.getPosX(), j) != -1)
			{
				string posX = fromIntToLetter(pos.getPosX() + 1);
				string posY = to_string(j + 1);
				vecMoviments.push_back(posX += posY);

				if (checkPosition(pos, pos.getPosX(), j) == 1)
					obstacle = true;
			}
			else
				obstacle = true;
		}
	}

	//An�lisi del moviment vertical avall.
	obstacle = false;
	if(pos.getPosY() > LIM_MIN)
	{
		for(int j = pos.getPosY() - 1; j>=0 && !obstacle; j--)
		{
			if (checkPosition(pos, pos.getPosX(), j) != -1)
			{
				string posX = fromIntToLetter(pos.getPosX() + 1);
				string posY = to_string(j + 1);
				vecMoviments.push_back(posX += posY);

				if (checkPosition(pos, pos.getPosX(), j) == 1)
					obstacle = true;
			}
			else
				obstacle = true;
		}
	}
	return vecMoviments;
}

VecOfPositions Chessboard::getValidMovesPawn(const ChessPosition& pos, VecOfPositions& vecMoviments) const
{
 	vecMoviments.clear();
	int i = 0;
	int j = 0;
	if (m_board[pos.getPosX()][pos.getPosY()].getColor() == CPC_White) //Cas en que el pe� sigui blanc.
	{
		if (pos.getPosY() < LIM_MAX)
		{
			int i = pos.getPosX();
			int j = pos.getPosY() + 1;
			if (checkPosition(pos, i, j) == 0)
			{
				string posX = fromIntToLetter(i + 1);
				string posY = to_string(j + 1);
				vecMoviments.push_back(posX += posY);
			}
			if (pos.getPosY() == 1 && checkPosition(pos, i, j) == 0) //Si el pe� est� a la posici� inicial tenim la possibilitat de avan�ar 2 caselles.
			{
				j++;
				if (checkPosition(pos, i, j) == 0)
				{
					string posX = fromIntToLetter(i + 1);
					string posY = to_string(j + 1);
					vecMoviments.push_back(posX += posY);
				}
			}
		}

		//Moviment diagonal per eliminar la pe�a
		if (pos.getPosX() < LIM_MAX && pos.getPosY() < LIM_MAX) //Diagonal superior dreta
		{
			i = pos.getPosX() + 1;
			j = pos.getPosY() + 1;
			if (checkPosition(pos, i, j) == 1)
			{
				string posX = fromIntToLetter(i + 1);
				string posY = to_string(j + 1);
				vecMoviments.push_back(posX += posY);
			}
		}
		if (pos.getPosX() > LIM_MIN && pos.getPosY() < LIM_MAX) //Diagonal superior esquerra
		{
			i = pos.getPosX() - 1;
			j = pos.getPosY() + 1;
			if (checkPosition(pos, i, j) == 1)
			{
				string posX = fromIntToLetter(i + 1);
				string posY = to_string(j + 1);
				vecMoviments.push_back(posX += posY);
			}
		}
	}
	else //Color negre
	{
		if (pos.getPosY() > LIM_MIN)
		{
			int i = pos.getPosX();
			int j = pos.getPosY() - 1;
			if (checkPosition(pos, i, j) == 0)
			{
				string posX = fromIntToLetter(i + 1);
				string posY = to_string(j + 1);
				vecMoviments.push_back(posX += posY);
			}
			if (pos.getPosY() == 6 && checkPosition(pos, i, j) == 0) //Si el pe� est� a la posici� inicial tenim la possibilitat de avan�ar 2 caselles.
			{
				j--;
				if (checkPosition(pos, i, j) == 0)
				{
					string posX = fromIntToLetter(i + 1);
					string posY = to_string(j + 1);
					vecMoviments.push_back(posX += posY);
				}
			}
		}

		//Moviment diagonal per eliminar la pe�a
		if (pos.getPosX() < LIM_MAX && pos.getPosY() > LIM_MIN) //Diagonal inferior dreta
		{
			i = pos.getPosX() + 1;
			j = pos.getPosY() - 1;
			if (checkPosition(pos, i, j) == 1)
			{
				string posX = fromIntToLetter(i + 1);
				string posY = to_string(j + 1);
				vecMoviments.push_back(posX += posY);
			}
			
		}
		if (pos.getPosX() > LIM_MIN && pos.getPosY() > LIM_MIN) //Diagonal inferior esquerra
		{
			i = pos.getPosX() - 1;
			j = pos.getPosY() - 1;

			if (checkPosition(pos, i, j) == 1)
			{
				string posX = fromIntToLetter(i + 1);
				string posY = to_string(j + 1);
				vecMoviments.push_back(posX += posY);
			}
		}

	}
	return vecMoviments;
}

VecOfPositions Chessboard::GetValidMoves(const ChessPosition& pos) const
{
	vector<ChessPosition> vecMoviments;

	switch (m_board[pos.getPosX()][pos.getPosY()].getTipus())
	{
	case CPT_King: vecMoviments = getValidMovesKing(pos, vecMoviments);
		break;
	case CPT_Queen: vecMoviments = getValidMovesQueen(pos, vecMoviments);
		break;
	case CPT_Rook: vecMoviments = getValidMovesRook(pos, vecMoviments);
		break;
	case CPT_Bishop: vecMoviments = getValidMovesBishop(pos, vecMoviments);
		break;
	case CPT_Knight: vecMoviments = getValidMovesKnight(pos, vecMoviments);
		break;
	case CPT_Pawn: vecMoviments = getValidMovesPawn(pos, vecMoviments);
		break;
	case CPT_EMPTY: vecMoviments.clear();
		break;
	default: vecMoviments.clear(); //Cas en que sorgeixi un error, enviem un vector buit.
		break;
	}
	
	return vecMoviments;
}

bool Chessboard::MovePiece(const ChessPosition& posFrom, const ChessPosition& posTo) //FET
{
	int i = 0;
	bool esPot = false;
	m_moves = GetValidMoves(posFrom); //Omplim el vector amb les posicions valides de la pe�a.
	
	while (i < m_moves.size() && !esPot)
	{
		if (m_moves[i] == posTo && m_board[posFrom.getPosX()][posFrom.getPosY()].getColor()== m_turn)
		{
			esPot = true;
			m_board[posTo.getPosX()][posTo.getPosY()].setTipus(m_board[posFrom.getPosX()][posFrom.getPosY()].getTipus());
			m_board[posTo.getPosX()][posTo.getPosY()].setColor(m_board[posFrom.getPosX()][posFrom.getPosY()].getColor());
			m_board[posFrom.getPosX()][posFrom.getPosY()].setColor(CPC_NONE);												//Buidem la posici�.
			m_board[posFrom.getPosX()][posFrom.getPosY()].setTipus(CPT_EMPTY);												//Buidem la posici�.
		}
		else
			i++;
	}
	return esPot;
}

void Chessboard::Render() 
{
	//DESCRIPTION:
	//Renderitza el tauler amb totes les peces.
	//PARAMETERS: -
	//RETURN: -
	GraphicManager::getInstance()->drawSprite(IMAGE_BOARD, 0, 0);

	for (int i = 0; i < NUM_ROWS; i++)
		for (int j = 0; j < NUM_COLS; j++)
			m_board[j][i].RenderPiece(j, i);

}

bool Chessboard::gameState(int m_turn)
{
	//DESCRIPTION:
	//Aquesta funci� ens indica l'estat de la partida. Ens indica si segeuix viu el rei del jugador que est� jugant. 
	//PARAMETERS:
	//m_turn: Indica el jugador que est� jugant, el color, blanc o negre.
	//RETURN: Ens retorna TRUE si el rei ja ha mort, �s a dir, no est� al tauler, en cas contrari ens retorna FALSE i es seguiex jugant la partida.

	int i = 0, j = 0;
	bool mort = true;

	while (i < NUM_COLS && mort == true)
	{
		j = 0;
		while (j < NUM_ROWS && mort == true)
		{
			if ((m_board[i][j].getTipus() == CPT_King) && (m_board[i][j].getColor() == m_turn)) //Segeuix viu?
				mort = false;
			else
				j++;
		}
		if (mort == true)
			i++;
	}
	return mort;
}

ChessPosition Chessboard::conversorPosition(int posX, int posY)
{
	//DESCRIPTION:
	//Aquesta funci� modifica la posici� perque sigui adient a la pantalla interactiva. Configura la posici� dels pixels, perque funcioni correctament.
	//PARAMETERS:
	//mousePosX/mousePosY: Indica la posici� en pantalla del ratol�.
	//RETURN: Retorna la posici� modificada, adient per la pantalla interactiva.

	ChessPosition position;
	position.setPosX((posX - CELL_INIT_X) / CELL_W);
	position.setPosY((posY - CELL_INIT_Y) / CELL_H);

	return position;
}

void Chessboard::displayValidMoves(int posX, int posY)
{
	//DESCRIPTION:
	//Mostra les posicions valides de les peces al tauler.
	//PARAMETERS:
	//mousePosX/mousePosY: Indica la posici� en pantalla del ratol�.
	//RETURN: -
	
	ChessPosition position;
	position = conversorPosition(posX, posY); //Modifiquem la posici� perque sigui adient als pixels de la pantalla.
	vector<ChessPosition> vecMoviments;
	vecMoviments = GetValidMoves(position);				//Obtenim la llista de moviments de la pe�a en la qual s'ha clicat.
	for (int i = 0; i < vecMoviments.size(); i++)
	{
		GraphicManager::getInstance()->drawSprite(IMAGE_VALID_POS, GREEN_INIT_X + (vecMoviments[i].getPosX() * CELL_W), GREEN_INIT_Y + (vecMoviments[i].getPosY() * CELL_H));
		m_posInicial = position;						//La posici� inicial passa a ser la posici� on vam clicar.
	}
}


string Chessboard::ToString() const
{
	string tauler;
	Piece typeP;
	tauler += "\n";
	tauler += "      PARTIDA EN CURS...\n";
	for (int i = NUM_ROWS; i > 0; i--)
	{	
		tauler += "|";
		tauler += to_string(i);
		for (int j = 0; j < NUM_COLS; j++)
		{
			tauler += " ";
			if (m_board[j][i - 1].getColor() != CPC_NONE && m_board[j][i - 1].getTipus() != CPT_EMPTY)
			{
				if (m_board[j][i - 1].getColor() == CPC_Black)	//Color negre.
					tauler += "b";
				else											//Color blanc.
					tauler += "w";

				tauler += typeP.pieceTypeToString(m_board[j][i - 1].getTipus());
			}
			else
				tauler += "__";

		}
		tauler += "|\n";
	}

	tauler += "   a  b  c  d  e  f  g  h \n";
	tauler += "\n";

	return tauler;
}

ifstream& operator>>(ifstream& input, Piece& p) //FINISHED
{
	string color;
	string tipus;

	input >> color >> tipus;
	color = color[0];				//Nom�s necessitem el n�mero, sense el punt.
	tipus = tipus[0];				//Nom�s necessitem la primera lletra per identificar el tipus de pe�a.

	p.setColor(p.stringToPieceColor(color));
	p.setTipus(p.stringToPieceType(tipus));
	return input;
}