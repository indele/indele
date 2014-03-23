#pragma once

#include "Node.h"

class QueueStack
{
private:
	Node* m_pHead;
	
public:
	QueueStack(void);
	~QueueStack(void);
	void Insert(Node* pNew);
	Node* PopFront();
	Node* PopBack();
};
