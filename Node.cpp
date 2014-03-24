#include "Node.h"

//test comment

Node::Node(void)
{
	m_posX = -1;
	m_posY = -1;
	m_pNext = NULL;
	m_pPrev = NULL;
}

Node::~Node(void) {}

void Node::SetPos(int x, int y)
{
	m_posX = x;
	m_posY = y;
}

int Node::GetPosX()
{
	return m_posX;
}

int Node::GetPosY()
{
	return m_posY;
}

void Node::SetNext(Node* pNext)
{
	m_pNext = pNext;
}

void Node::SetPrev(Node* pPrev)
{
	m_pPrev = pPrev;
}

Node* Node::GetNext()
{
	return m_pNext;
}

Node* Node::GetPrev()
{
	return m_pPrev;
}
