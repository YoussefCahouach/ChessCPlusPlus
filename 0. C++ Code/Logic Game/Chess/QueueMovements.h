#ifndef QueueMovements_hpp
#define QueueMovements_hpp

#include <iostream>
#include <stdio.h>
#include <string>
#include "ChessPosition.hpp"


class Node 
{
public:
	ChessPosition& getValor() { return m_valor; }
	Node* getNext() { return m_next; }
	void setValor(const ChessPosition& valor) { m_valor = valor; }
	void setNext(Node* next) { m_next = next; }
private:
	ChessPosition m_valor;
	Node* m_next;
};

class QueueMovements
{
public:
	QueueMovements();
	~QueueMovements();
	void afegeix(ChessPosition& valor);
	void treu();
	ChessPosition& getPrimer() const { return m_primer->getValor(); } //Obtenim el contingut del principi de la cua.
	ChessPosition& getUltim() const { return m_ultim->getValor(); }   //Obtenim el contingut del final de la cua.
	bool esBuida() const;
private:
	Node* m_primer;
	Node* m_ultim;
};

#endif /* QueueMovements_h */