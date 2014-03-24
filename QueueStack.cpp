///////////////////////////////////////////////////////////////////
///// �����ڰ� �Է��ϴ� ��ǥ�� �����ϰ� �ִ� QueueStack Class /////
///////////////////////////////////////////////////////////////////

#include "QueueStack.h"

using namespace std;

//Test Comment

///// QueueStack Class�� ������ /////
QueueStack::QueueStack(void)
{
	m_pHead = NULL;
}

///// QueueStack class�� �Ҹ��� /////
///// QueueStack�� �ִ� ���� ���带 �޸��� ���� /////
QueueStack::~QueueStack(void)
{
	Node* pWalker = NULL;	// ������ �޸𸮸� ����ų ����

	///// Head�������� �ϳ��� �޸��� ���� /////
	while(m_pHead)
	{
		pWalker = m_pHead;
		m_pHead = pWalker->GetNext();
		delete pWalker;
	}
	
	m_pHead = NULL;
}

///// ���ο� ���带 ����Ʈ�� Head�� �߰��ϴ� �Լ� /////
void QueueStack::Insert(Node* pNew)
{
	///// Head�� �������� �� ���ο� ���带 Head�� ����Ų�� /////
	if(m_pHead == NULL)
		m_pHead = pNew;

	///// Head�� �������� ���� �� Head�� Next�� ���ο� ���尡 �ǰ� Head�� ���ο� ���带 ����Ų�� ///// 
	else
	{
		pNew->SetNext(m_pHead);
		m_pHead->SetPrev(pNew);
		m_pHead = pNew;
	}
}

///// ����Ʈ���� ���� ���߿� �߰��� ���带 ������ �Լ� /////
Node* QueueStack::PopFront()
{
	Node* pWalker = m_pHead;	// ��ȯ���� ������ ����

	///// ����Ʈ�� �����ִ� ���� /////
	if(!pWalker)
		return NULL;

	///// ����Ʈ�� �������� ���� ���� /////
	else
	{
		m_pHead = pWalker->GetNext();
		return pWalker;
	}
}

///// ����Ʈ���� ���� ���� �߰��� ���带 ������ �Լ� /////
Node* QueueStack::PopBack()
{
	Node* pWalker = m_pHead;	// ��ȯ���� ������ ����

	///// ����Ʈ�� �����ִ� ���� /////
	if(!pWalker)
		return NULL;

	///// ����Ʈ�� ���尡 �ϳ��� �ִ� ���� /////
	else if(!pWalker->GetNext())
	{
		m_pHead = NULL;
		return pWalker;
	}

	///// ���� ���찡 �ƴ� ���� /////
	else
	{
		while(pWalker->GetNext())
			pWalker = pWalker->GetNext();

		pWalker->GetPrev()->SetNext(NULL);

		return pWalker;
	}
}
