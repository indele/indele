////////////////////////////////////////////////////////////////////////////////////
///// 사용자가 입력한 좌표를 저장할 QueueStack에 사용되는 노드				   /////
///// Node는 x, y좌표와 다음 Node와 이전 Node를 가리키는 포인터를 가지고 있다. /////
////////////////////////////////////////////////////////////////////////////////////

#include "Node.h"

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