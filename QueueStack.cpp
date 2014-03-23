///////////////////////////////////////////////////////////////////
///// 사용자가 입력하는 좌표를 저장하고 있는 QueueStack Class /////
///////////////////////////////////////////////////////////////////

#include "QueueStack.h"

using namespace std;

///// QueueStack Class의 생성자 /////
QueueStack::QueueStack(void)
{
	m_pHead = NULL;
}

///// QueueStack class의 소멸자 /////
///// QueueStack에 있는 모든 노드를 메모리 해제 /////
QueueStack::~QueueStack(void)
{
	Node* pWalker = NULL;	// 해제될 메모리를 가리킬 변수

	///// Head에서부터 하나씩 메모리 해제 /////
	while(m_pHead)
	{
		pWalker = m_pHead;
		m_pHead = pWalker->GetNext();
		delete pWalker;
	}
	
	m_pHead = NULL;
}

///// 새로운 노드를 리스트의 Head에 추가하는 함수 /////
void QueueStack::Insert(Node* pNew)
{
	///// Head가 비어있을 시 새로운 노드를 Head가 가리킨다 /////
	if(m_pHead == NULL)
		m_pHead = pNew;

	///// Head가 비어있지 않을 때 Head의 Next는 새로운 노드가 되고 Head는 새로운 노드를 가리킨다 ///// 
	else
	{
		pNew->SetNext(m_pHead);
		m_pHead->SetPrev(pNew);
		m_pHead = pNew;
	}
}

///// 리스트에서 가장 나중에 추가된 노드를 꺼내는 함수 /////
Node* QueueStack::PopFront()
{
	Node* pWalker = m_pHead;	// 반환값을 저장할 변수

	///// 리스트가 비어있는 경우 /////
	if(!pWalker)
		return NULL;

	///// 리스트가 비어있지 않은 경우 /////
	else
	{
		m_pHead = pWalker->GetNext();
		return pWalker;
	}
}

///// 리스트에서 가장 먼저 추가된 노드를 꺼내는 함수 /////
Node* QueueStack::PopBack()
{
	Node* pWalker = m_pHead;	// 반환값을 저장할 변수

	///// 리스트가 비어있는 경우 /////
	if(!pWalker)
		return NULL;

	///// 리스트에 노드가 하나만 있는 경우 /////
	else if(!pWalker->GetNext())
	{
		m_pHead = NULL;
		return pWalker;
	}

	///// 위의 경우가 아닌 경우 /////
	else
	{
		while(pWalker->GetNext())
			pWalker = pWalker->GetNext();

		pWalker->GetPrev()->SetNext(NULL);

		return pWalker;
	}
}
