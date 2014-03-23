#pragma once

#include <iostream>

class Node
{
private:
	int m_posX;
	int m_posY;
	Node* m_pNext;
	Node* m_pPrev;

public:
	Node(void);
	~Node(void);
	void SetPos(int x, int y);
	int GetPosX();
	int GetPosY();
	void SetNext(Node* pNext);
	void SetPrev(Node* pPrev);
	Node* GetNext();
	Node* GetPrev();
};
