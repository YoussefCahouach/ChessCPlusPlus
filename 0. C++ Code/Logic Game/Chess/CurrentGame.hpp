#ifndef CurrentGame_hpp
#define CurrentGame_hpp

#include <stdio.h>
#include <string>
#include <queue>
#include "GameInfo.h" 
#include "Chessboard.hpp"
#include "QueueMovements.h"

using namespace std;

class CurrentGame { 
public:
    CurrentGame();
    ~CurrentGame() {}

    void init(GameMode mode, const string& intitialBoardFile, const string& movementsFile);     //Inicialització de la partida.
	bool updateAndRender(int mousePosX, int mousePosY, bool mouseStatus);                       //Gestiona el joc de forma general.
    int changePlayer(int lastMove);                                                             //Canvia el jugador.
    void end();                                                                                 //Guarda els moviments realitzats en un fitxer.
    
private:
    Chessboard m_board;
    QueueMovements m_movements;
    GameMode m_mode;
    string m_fitxerMovements;
    int m_winner;
    bool m_clicked;
    bool m_gameOver;
};

#endif /* CurrentGame_hpp */
