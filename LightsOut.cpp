#include "LightsOut.h"

using namespace std;

LightsOut::LightsOut(void)
{
	m_pHead = NULL;
	m_undoCnt = 0;
	m_mapID = -1;
	m_minCnt = -1;
	m_useCnt = 0;
}

LightsOut::~LightsOut(void)
{
	Light* pRowDel = NULL;
	Light* pColDel = NULL;

	while(m_pHead)
	{
		pRowDel = m_pHead;
		while(pRowDel->GetRight())
		{
			pColDel = pRowDel->GetRight();
			pRowDel->SetRight(pColDel->GetRight());
			delete pColDel;
		}
		m_pHead = pRowDel->GetBottom();
		delete pRowDel;
	}
}

bool LightsOut::LoadMap(char* fname)
{
	ifstream fin;
	char buffer[128] = {0, };	// ���Ͽ��� �� ���� �о�� ����
	char* temp;					// String Token�� �ӽ÷� �ܾ ������ ����
	Light* pNew = NULL;			
	Light* pNode = NULL;
	Light* pRowWalker = NULL;	// �� ������ �̵��ϴ� ����
	Light* pRowPrev = NULL;		// ���� ���� ����Ű�� ����
	Light* pColWalker = NULL;	// �� ������ �̵��ϴ� ����
	Light* pAboveNode = NULL;	// ���ο� ����� �� ��带 ����Ű�� ����
/*	
	if(m_pHead)
	{
		LightsOut::~LightsOut();
		m_useCnt = 0;
		m_undoCnt = 0;
	}
*/
	fin.open(fname);

	if(fin.fail())
	{
		cout<<"Fail to open file..."<<endl;
		return false;
	}

	m_useCnt = 0;
	m_undoCnt = 0;

	fin.getline(buffer, 128);
	temp = strtok(buffer, ":");
	temp = strtok(NULL, "\n");
	temp++;
	m_mapID = atoi(temp);
	cout<<"MapID : "<<m_mapID<<endl;

	fin.getline(buffer, 128);
	temp = strtok(buffer, ":");
	temp = strtok(NULL, "\n");
	temp++;
	m_minCnt = atoi(temp);
	cout<<"MinimumCount : "<<m_minCnt<<endl<<endl;

	fin.getline(buffer, 128);

	while(!fin.eof())
	{
		fin.getline(buffer, 128);
		temp = strtok(buffer, "\t");
		pNew = new Light;
		if(!pNew)
		{
			cout<<"Failed to memory allocate..."<<endl;
			return false;
		}
		pNew->SetState(atoi(temp));

		if(!m_pHead)
		{
			m_pHead = pNew;

			while(1)
			{
				pColWalker = m_pHead;
				temp = strtok(NULL, "\t");
				
				if(temp == NULL)
					break;
				
				pNode = new Light;
				
				if(!pNode)
				{
					cout<<"Failed to memory allocate..."<<endl;
					return false;
				}
				pNode->SetState(atoi(temp));

				while(pColWalker->GetRight())
				{
					pColWalker = pColWalker->GetRight();
				}

				pColWalker->SetRight(pNode);
				pNode->SetLeft(pColWalker);
			}
		}

		else
		{
			pRowWalker = m_pHead;
			pRowPrev = pRowWalker;
			
			while(pRowWalker->GetBottom())
			{
				pRowPrev = pRowWalker;
				pRowWalker = pRowWalker->GetBottom();
			}
			
			pRowWalker->SetBottom(pNew);
			pNew->SetAbove(pRowWalker);

			pRowPrev = pRowWalker;
			pRowWalker = pRowWalker->GetBottom();
			
			while(1)
			{
				temp = strtok(NULL, "\t");
				
				if(temp == NULL)
					break;
				
				pNode = new Light;
				
				if(!pNode)
				{
					cout<<"Failed to memory allocate..."<<endl;
					return false;
				}
				pNode->SetState(atoi(temp));

				pColWalker = pRowWalker;
				pAboveNode = pRowPrev;
				
				while(pColWalker->GetRight())
				{
					pColWalker = pColWalker->GetRight();
					pAboveNode = pAboveNode->GetRight();
				}

				pAboveNode = pAboveNode->GetRight();	
				
				pAboveNode->SetBottom(pNode);
				pNode->SetAbove(pAboveNode);
				pNode->SetLeft(pColWalker);
				pColWalker->SetRight(pNode);
			}
		}
	}

	PrintLights();

	fin.close();

	return true;
}

///// ����ڰ� �Է��� x, y ��ǥ�� QueueStack�� ���� /////
bool LightsOut::Push(int x, int y)
{
	Node* pNew = NULL;

	pNew = new Node;
	
	///// �޸��Ҵ翡 ������ ��� /////
	if(!pNew)
	{
		cout<<"Failed to memory allocate..."<<endl;
		return false;
	}
	
	///// ���������� �޸� �Ҵ翡 ������ ��� /////
	pNew->SetPos(x, y);
	m_qsPosLog.Insert(pNew);
	m_useCnt++;
	
	return true;
}

///// ����ڰ� �Է��� x, y ��ǥ�� ���� on/off�� ���� /////
bool LightsOut::LightOnOff(int x, int y)
{
	Light* pWalker = m_pHead;	// ����ڰ� �Է��� ��ǥ�� ����ų ����

	///// 0 ~ 4������ ���ڰ� �ƴ� ��� ���� ó�� /////
	if((x < 0 || x > 4) || (y < 0 || y > 4))
		return false;

	///// �Է¹��� ��ǥ�� pWalker ������ �̵� /////
	for(int i=0; i<x; i++)
		pWalker = pWalker->GetRight();

	for(int i=0; i<y; i++)
		pWalker = pWalker->GetBottom();

	///// �Է� ���� ��ǥ�� ���°��� XOR ������ �̿��Ͽ� On/Off /////
	pWalker->SetState((pWalker->GetState()) ^ 1);

	///// �Է¹��� ��ǥ�� ��, ��, ��, �쿡 ��尡 ���� �� ��� XOR ������ �̿��Ͽ� On/Off /////
	if(pWalker->GetAbove())
		pWalker->GetAbove()->SetState((pWalker->GetAbove()->GetState()) ^ 1);

	if(pWalker->GetBottom())
		pWalker->GetBottom()->SetState((pWalker->GetBottom()->GetState()) ^ 1);

	if(pWalker->GetRight())
		pWalker->GetRight()->SetState((pWalker->GetRight()->GetState()) ^ 1);

	if(pWalker->GetLeft())
		pWalker->GetLeft()->SetState((pWalker->GetLeft()->GetState()) ^ 1);

	return true;
}

///// ���� ó�����·� �ʱ�ȭ /////
void LightsOut::Reset()
{
	Node* pTemp = m_qsPosLog.PopFront();
	Light* pWalker = m_pHead;

	///// ����Ʈ�� ����ִ� ��� �̹� �ʱ�ȭ�� �̷�� ���ٰ� �Ǵ��ϰ� ����ó�� /////
	if(!pTemp)
	{
		cout<<endl<<"The map is already initialized..."<<endl<<endl;
	}

	else
	{
		///// QueueStack ����Ʈ�� ������� �� ���� �������� �̵��ϸ鼭 Light on/off �� ���� /////
		while(pTemp)
		{
			LightOnOff(pTemp->GetPosX(), pTemp->GetPosY());
			pTemp = pTemp->GetNext();
		}
		
		///// ���� �� ������ �����ϰ� ���ο� ������ ���� �� ��츦 �����Ͽ� QueueStack�� �Ҹ��� ȣ�� /////
		m_qsPosLog.~QueueStack();
		
		///// UserCount�� UndoCount�� �ʱ�ȭ /////
		m_useCnt = 0;
		m_undoCnt = 0;
		
		cout<<"Reset!!!"<<endl;

		cout<<endl<<"States of Lights : "<<endl;
		PrintLights();
	}
}

///// ������� �Է��� �Ѵܰ� ��� /////
void LightsOut::Undo()
{
	Node* pTemp = m_qsPosLog.PopFront();
	Light* pWalker = m_pHead;

	///// QueueStack ����Ʈ�� ����ִ� ��� �̹� ���� �ʱ�����̹Ƿ� ���� ó�� /////
	if(!pTemp)
	{
		cout<<endl;
		cout<<"You can't undoing..."<<endl;
		cout<<"The map is initialized state..."<<endl<<endl;
		cout<<"Undo count : "<<m_undoCnt<<endl;
	}

	else
	{
		m_undoCnt++;	//Undo Ƚ���� Count
		
		///// UndoCount�� 3�� �Ѿ ��� Undo�� �������� ���Ѵ� /////
		if(m_undoCnt > 3)
		{
			cout<<endl<<"You can't undoing..."<<endl;
			cout<<"The Maximum number of perform undoing is 3"<<endl;
			cout<<"The current number of undo : "<<m_undoCnt-1<<endl<<endl;
			return;
		}

		cout<<"Undo : ("<<pTemp->GetPosX()<<", "<<pTemp->GetPosY()<<"), ";
		cout<<"Undo count : "<<m_undoCnt<<endl;	

		LightOnOff(pTemp->GetPosX(), pTemp->GetPosY());

		delete pTemp;

		m_useCnt--;		// UserCount�� UndoCount�� �ϳ��� �����Կ� ���� �ϳ��� �����Ѵ�.

		cout<<endl<<"States of Lights : "<<endl;
		PrintLights();
	}
}

///// ������ �ذ�Ǿ����� Ȯ�� /////
bool LightsOut::IsSolved()
{
	Light* pRowWalker = m_pHead;
	Light* pColWalker = NULL;

	while(pRowWalker)
	{
		pColWalker = pRowWalker;

		while(pColWalker)
		{
			///// ��� �� ���� 'On' ���¸� ������ ��尡 �ִ°�� ������ �ذ���� �ʾҴٰ� �Ǵ� /////
			if(pColWalker->GetState() == 1)
				return false;

			pColWalker = pColWalker->GetRight();
		}

		pRowWalker = pRowWalker->GetBottom();
	}

	return true;
}

///// ���� ���� ���¸� �����ִ� �Լ� /////
void LightsOut::PrintLights()
{
	Light* pRowWalker = NULL;
	Light* pColWalker = NULL;

	pRowWalker = m_pHead;

	while(pRowWalker)
	{
		pColWalker = pRowWalker;
		while(pColWalker)
		{
			cout<<pColWalker->GetState()<<"\t";
			pColWalker = pColWalker->GetRight();
		}
		cout<<endl;
		pRowWalker = pRowWalker->GetBottom();
	}
	cout<<endl;

}

///// ������� ��ǥ, Ƚ��, ������ ���Ͽ� �����ϴ� �Լ� /////
void LightsOut::RecordSolution(char* fname)
{
	ofstream fout;
	Node* pTemp = NULL;
	int score = 100 - ((10*(m_useCnt - m_minCnt)) + (5 * m_undoCnt));

	cout<<"Game Over!!!"<<endl;
	cout<<"Your Score is "<<score<<"!!"<<endl;
	cout<<"Record your solution and score on Results.txt!!"<<endl;
	cout<<"Go back to the main"<<endl;

	fout.open(fname, ios::app);

	fout<<"=========================================================================================="<<endl;
	fout<<"MapID : "<<m_mapID<<endl;
	fout<<"MinimumCount : "<<m_minCnt<<endl;
	fout<<"UserCount : "<<m_useCnt<<endl;
	fout<<"UndoCount : "<<m_undoCnt<<endl;
	fout<<"Score : "<<score<<endl;

	fout<<"Solution : ";
	pTemp = m_qsPosLog.PopBack();
	while(pTemp->GetPrev())
	{
		fout<<"("<<pTemp->GetPosX()<<", "<<pTemp->GetPosY()<<") -> ";
		delete pTemp;
		pTemp = m_qsPosLog.PopBack();
	}

	fout<<"("<<pTemp->GetPosX()<<", "<<pTemp->GetPosY()<<")";
	delete pTemp;

	fout<<endl;

	fout<<"=========================================================================================="<<endl<<endl;

	fout.close();
	m_qsPosLog.~QueueStack();
}
