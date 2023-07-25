#ifndef ChessPosition_hpp
#define ChessPosition_hpp

#include <stdio.h>
#include <string>
#include <vector>
using namespace std;


class ChessPosition {
public:
    //Constructors i destructors.
    ChessPosition() : m_posX(0), m_posY(0) { }
    ChessPosition(const string& pos);
    ~ChessPosition() { }

    //Getters i setters.
    int getPosX() const { return m_posX; }
    int getPosY() const { return m_posY; }
    void setPosX(int posX) { m_posX = posX; }
    void setPosY(int posY) { m_posY = posY; }

    //Funció per convertir una posició en un string.
    string posToString(int pos);

    //Un operador operator== per comprovar que dues posicions son iguals.
    bool operator==(const ChessPosition& pos) const;
private:
    int m_posX; //Column
    int m_posY; //Row


};

ostream& operator<<(ostream& output, const ChessPosition& pos);
typedef vector<ChessPosition> VecOfPositions;


#endif /* ChessPosition_hpp */
