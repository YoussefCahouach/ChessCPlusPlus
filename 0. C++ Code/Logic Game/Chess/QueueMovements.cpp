#include <iostream>
#include "QueueMovements.h"

using namespace std;

//DESCRIPTION:
// Es tracta d'una cua dinàmica que s'encarrega de guardar tots els moviments que es fa a la partida. Aquests moviments son reproduits quan executem
// el mode REPLAY.
//FUNCTIONS:
//afegeix: S'encarrega d'afegir al final de la cua, la posició que li passem per parametre. Aquesta posició ha de ser de tipus ChessPosition.
//treu: S'encarrega d'eliminar la posició que hi ha al principi de tot de la cua. 

QueueMovements::QueueMovements()
{
	m_primer = nullptr;
	m_ultim = nullptr;

}
QueueMovements::~QueueMovements()
{
	Node* auxP = m_primer;
	Node* auxF;
	while (auxP != NULL)
	{
		auxF = auxP;
		auxP = auxP->getNext();
		delete auxF;
	}
}
void QueueMovements::afegeix(ChessPosition& valor)
{
	Node* aux = new Node;
	aux->setValor(valor);
	aux->setNext(nullptr);
	if (esBuida())
	{
		m_primer = aux;
		m_ultim = aux;
	}
	else
	{
		m_ultim->setNext(aux);
		m_ultim = aux;
	}
}
void QueueMovements::treu()
{
	if (!esBuida())
	{
		Node* aux = m_primer;
		if (m_primer == m_ultim)
		{
			m_primer = nullptr;
			m_ultim = nullptr;
		}
		else
		{
			m_primer = m_primer->getNext();
		}
		delete aux;
	}

}
bool QueueMovements::esBuida() const
{
	bool buit = false;
	if (m_primer == NULL)
		buit = true;
	
	return buit;
}