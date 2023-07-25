#include "CurrentGame.hpp"
#include "GameInfo.h"
#include "../GraphicManager.h"
#include "QueueMovements.h"
#include <iostream>
#include <fstream>

CurrentGame::CurrentGame()    //Inicialitza els atributs de la classe CurrentGame.
{
    //DESCRIPTION:
    //Inicialitza les variables de la classe CurrentGame.
    //PARAMETERS:
    //m_mode: Indica el mode que estem jugant.
    //m_fitxerMovements: Guarda el nom del document que voldrem editar quan acabem una partida en mode GM_NORMAL.
    //m_winner: Indica qui és el guanyador.
    //m_clicked: Indica si ha clicat.
    //m_gameOver: Indica si la partida ha acabat.
    //RETURN: -

    m_mode = GM_NONE;
    m_fitxerMovements = "";
    m_winner = -1;
    m_board.setTorn(CPC_White);   
    m_clicked = false;
    m_gameOver = false;
}

int CurrentGame::changePlayer(int lastMove)
{
    //DESCRIPTION:
    //Canvia el torn del jugador, entre blanques i negres. Depenent del parametre, retornem un torn o un altre, es a dir, retornem el color el qual ha
    //de jugar.
    //PARAMETERS:
    //lastMove: Indica el color de l'ultim jugador que ha mogut una peça.
    //RETURN:
    //changeColor: Retorna el torn del jugador (color) que jugarà en el següent torn.

    int changeColor;
    if (lastMove == CPC_Black)
        changeColor = CPC_White;
    else
        changeColor = CPC_Black;
    return changeColor;
}

void CurrentGame::init(GameMode mode, const string& intitialBoardFile, const string& movementsFile)
{
    //DESCRIPTION:
    //Inicialitzem el parametre m_board amb el tauler inicial. Si el mode és GM_NORMAL haurem de eliminar les dades del fitxer movementsFile
    //per omplir-lo de nou amb els nous moviments. En cas que sigui GM_REPLAY, agafem el contingut del fitxer i ho guardem en la nostra cua dinamica.
    //PARAMETERS:
    //mode: Indica mode de joc que s'està jugant. 
    //initialBoardFile: Fitxer el qual conté el tauler inicial del joc.
    //movementsFile: Fitxer que conté la llista de moviments de la partida anterior (en cas que mode == GM_NORMAL).
    //RETURN: (RES)

    m_mode = mode;                                  //Guardem el mode de joc.
    m_fitxerMovements = movementsFile;              //Guardem el fitxer, per la funció end().

    m_board.LoadBoardFromFile(intitialBoardFile);   //Inicialitzem m_board.

    if (mode == GM_NORMAL)
    {
        ofstream fitxer;
        fitxer.open(movementsFile);
        if (fitxer.is_open())                       //In case of error.
        {   
            fitxer.clear();                         //Clear the file
        }
        fitxer.close();
    }
    else
        if (mode == GM_REPLAY)
        {
            ifstream fitxer;
            fitxer.open(movementsFile);
            if (fitxer.is_open())                   //In case of error
            {
                string posInicial, posFinal;
                fitxer >> posInicial >> posFinal;
                while (fitxer)
                {
                    ChessPosition posI(posInicial), posF(posFinal); 

                    //Fixem les posicions.
                    posI.setPosX(posI.getPosX() + 1);
                    posI.setPosY(posI.getPosY() + 1);
                    posF.setPosX(posF.getPosX() + 1);
                    posF.setPosY(posF.getPosY() + 1);

                    m_movements.afegeix(posI);                      //Afegim la posició inicial.
                    m_movements.afegeix(posF);                      //I la posició final.
                    fitxer >> posInicial >> posFinal;
                }
            }
            fitxer.close();
        }
}

bool CurrentGame::updateAndRender(int mousePosX, int mousePosY, bool mouseStatus) 
{
    //DESCRIPTION:
    //Aquesta funció s'encarrega de gestionar la major part gràfica del joc. Si el mode es GM_NORMAL tendrem la possibilitat de jugar una partida
    //als escacs. El joc va per torns. La partida no finalitza fins que un dels dos reis hagi mort. Guardem tots els moviments realitzats de forma
    //satisfactoria a la cua m_movements 
    //PARAMETERS:
    //mousePosX/mousePosY: Indica la posició en pantalla del ratolí.
    //mouseStatus: Indica l'estat del clic del ratolí.
    //RETURN: gameOver, si ha acabat la partida retorna TRUE, en cas contrari retornarà FALSE.
    
    m_board.Render(); //Mostrem el tauler i les peces.

    if (m_mode == GM_NORMAL && !m_board.gameState(m_board.getTorn()))
    {
        int posX, posY;
        ChessPosition posFrom, posTo;                                   //Creem dos objectes de tipus ChessPosition, posició inicial i final.

        posFrom = m_board.getPosInicial();                              //Obtenim la posició inicial.
        posTo = m_board.conversorPosition(mousePosX, mousePosY);        //Obtenim la posició a la qual volem anar.

        if ((mouseStatus) && (mousePosX >= CELL_INIT_X) && (mousePosY >= CELL_INIT_Y) && (mousePosX <= (CELL_INIT_X + CELL_W * NUM_COLS)) && (mousePosY <= (CELL_INIT_Y + CELL_H * NUM_ROWS)))
        {
            if (m_board.MovePiece(posFrom, posTo))                      //Realitzem el moviment desitjat, si es compleix la condició ->
            {
                m_movements.afegeix(posFrom);                           //Guardem la posició inicial a la cua.
                m_movements.afegeix(posTo);                             //I guardem la posició final.

                if (!m_board.gameState(m_board.getTorn()));             //Si no s'ha acabat la partida, canviem el torn de la partida.
                    m_board.setTorn(changePlayer(m_board.getTorn()));   //Canvi de jugador.
            }
            else
                m_board.setPosInicial(posTo);                           //Guardem la posició   
        }
        else  //Cas en que no cliquem a cap peça, mantenim les posicions valides en pantalla.
        {
            posX = CELL_INIT_X + (posFrom.getPosX() * CELL_W);
            posY = CELL_INIT_Y + (posFrom.getPosY() * CELL_H);
            m_board.displayValidMoves(posX, posY);
        }
    }
    else
        if (m_mode == GM_REPLAY)
        {
            bool acabat = false;
            ChessPosition posFrom, posTo;                                 

            if ((mousePosX >= CELL_INIT_X) && (mousePosY >= CELL_INIT_Y) && (mousePosX <= (CELL_INIT_X + CELL_W * NUM_COLS)) && (mousePosY <= (CELL_INIT_Y + CELL_H * NUM_ROWS)))
            {
                if (mouseStatus)
                    m_clicked = true;                                                   //Indiquem el click 
                else
                {
                    if (m_clicked)
                    {
                        m_clicked = false;
                        if (!m_movements.esBuida() && !acabat)
                        {
                            posFrom = m_movements.getPrimer();                          //Guardem la posició inicial guardada al principi de la cua.
                            m_movements.treu();                                         //Eliminem la posició.
                            posTo = m_movements.getPrimer();                            //Guardem la posició final guardada al principi de la cua.
                            m_movements.treu();                                         //Eliminem la posició.
                            m_board.MovePiece(posFrom, posTo);                          //Movem peça
                            acabat = m_board.gameState(m_board.getTorn());              //Comprobem estat del joc

                            if (!acabat)
                                m_board.setTorn(changePlayer(m_board.getTorn()));       //Canviem de torn 
                        }
                    }
                }
            }
            else
                m_clicked = false;                                                      //Desfem el click
        }

    m_gameOver = m_board.gameState(m_board.getTorn());                                  //Indica si la partida ha acabat.                         
     
    cout << m_board.ToString();                                                         //Suport per comprovar el funcionament correcte del joc. (Consola)

    //---------------------------------------------------TEXTOS-------------------------------------------------------------
    int posTextX = CELL_INIT_X;
    int posTextY = CELL_INIT_Y + (CELL_H * NUM_ROWS) + 60;

    std::string msg = "PosX: " + to_string(mousePosX) + ", PosY: " + to_string(mousePosY);
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY, 0.8, msg);
    
    std::string mode = "GAME MODE: ";
    if (m_mode == GM_NORMAL)
        mode += "Normal Play";
    else
        mode += "RePlay";
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY+50, 0.8, mode);

    std::string color = "Turn: ";
    if (m_board.getTorn() == CPC_White)
        color += "White";
    else
        color += "Black";
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY + 100, 0.8, color);

    std::string winner;
    if (m_mode == GM_REPLAY && m_movements.esBuida())
        winner = "No more moves to replay. ";

    if (m_gameOver) //Si la partida ha acabat, mostrem qui és el guanyador de la partida.
    {
        m_winner = changePlayer(m_board.getTorn());
        winner += "Guanyador: ";
        if (m_winner == CPC_Black)
            winner += "Negres";
        else
            if (m_winner == CPC_White)
                winner += "Blanques";
    }
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY + 150, 0.8, winner);
    return m_gameOver;
}

void CurrentGame::end()
{
    //DESCRIPTION:
    //Una vegada finalitzada la partida, ja sigui matant el rei o sense matar, si polsem "ESC" ens guardarà tots el moviments que hagim fet en el
    //document que vam guardar al metode init. 
    //PARAMETERS: -
    //RETURN: -

    if (m_mode==GM_NORMAL)
    {
        string posXString, posYString, posString;
      	ofstream fitxer;
	    fitxer.open(m_fitxerMovements);                                                             //Obrim fitxer amb parametre
        if (fitxer.is_open())                                                                       //Condicio fitxer obert
        {
            while (!m_movements.esBuida())                                                          //Mentre la cua no estigui buida.
            {
                posXString = m_board.fromIntToLetter(m_movements.getPrimer().getPosX());            //Agafem la posició X i ho transformem a string
                posYString = to_string(m_movements.getPrimer().getPosY());                          //Agafem la posició Y i ho transformem a string
                posString = posXString + posYString;                                                //Unim els dos strings.
                
                fitxer << posString << " ";                                                         //Guardem la posició inicial al fitxer.
                m_movements.treu();                                                                 //Eliminem la posició utilitzada de la cua.

                posXString = m_board.fromIntToLetter(m_movements.getPrimer().getPosX());            //Agafem la posició X i ho transformem a string
                posYString = to_string(m_movements.getPrimer().getPosY());                          //Agafem la posició Y i ho transformem a string
                posString = posXString + posYString;                                                //Unim els dos strings.

                fitxer << posString << endl;                                                        //Guardem posició al fitxer
                m_movements.treu();                                                                 //Eliminem la posició utilitzada de la cua.
            }
            fitxer.close();                                                                         //Tanquem el fitxer
        } 
    }
}