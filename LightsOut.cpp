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
	char buffer[128] = {0, };	// 파일에서 한 줄을 읽어올 버퍼
	char* temp;					// String Token시 임시로 단어를 저장할 버퍼
	Light* pNew = NULL;			
	Light* pNode = NULL;
	Light* pRowWalker = NULL;	// 행 단위를 이동하는 변수
	Light* pRowPrev = NULL;		// 이전 행을 가리키는 변수
	Light* pColWalker = NULL;	// 열 단위를 이동하는 변수
	Light* pAboveNode = NULL;	// 새로운 노드의 윗 노드를 가리키는 변수
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

///// 사용자가 입력한 x, y 좌표를 QueueStack에 저장 /////
bool LightsOut::Push(int x, int y)
{
	Node* pNew = NULL;

	pNew = new Node;
	
	///// 메모리할당에 실패할 경우 /////
	if(!pNew)
	{
		cout<<"Failed to memory allocate..."<<endl;
		return false;
	}
	
	///// 성공적으로 메모리 할당에 성공할 경우 /////
	pNew->SetPos(x, y);
	m_qsPosLog.Insert(pNew);
	m_useCnt++;
	
	return true;
}

///// 사용자가 입력한 x, y 좌표에 대해 on/off를 수행 /////
bool LightsOut::LightOnOff(int x, int y)
{
	Light* pWalker = m_pHead;	// 사용자가 입력한 좌표를 가리킬 변수

	///// 0 ~ 4사이의 숫자가 아닌 경우 예외 처리 /////
	if((x < 0 || x > 4) || (y < 0 || y > 4))
		return false;

	///// 입력받은 좌표로 pWalker 변수를 이동 /////
	for(int i=0; i<x; i++)
		pWalker = pWalker->GetRight();

	for(int i=0; i<y; i++)
		pWalker = pWalker->GetBottom();

	///// 입력 받은 좌표의 상태값을 XOR 연산을 이용하여 On/Off /////
	pWalker->SetState((pWalker->GetState()) ^ 1);

	///// 입력받은 좌표의 상, 하, 좌, 우에 노드가 존재 할 경우 XOR 연산을 이용하여 On/Off /////
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

///// 맵을 처음상태로 초기화 /////
void LightsOut::Reset()
{
	Node* pTemp = m_qsPosLog.PopFront();
	Light* pWalker = m_pHead;

	///// 리스트가 비어있는 경우 이미 초기화가 이루어 졌다고 판단하고 예외처리 /////
	if(!pTemp)
	{
		cout<<endl<<"The map is already initialized..."<<endl<<endl;
	}

	else
	{
		///// QueueStack 리스트가 비어있을 때 까지 이전노드로 이동하면서 Light on/off 를 수행 /////
		while(pTemp)
		{
			LightOnOff(pTemp->GetPosX(), pTemp->GetPosY());
			pTemp = pTemp->GetNext();
		}
		
		///// 리셋 후 게임을 포기하고 새로운 게임을 시작 할 경우를 생각하여 QueueStack의 소멸자 호출 /////
		m_qsPosLog.~QueueStack();
		
		///// UserCount와 UndoCount도 초기화 /////
		m_useCnt = 0;
		m_undoCnt = 0;
		
		cout<<"Reset!!!"<<endl;

		cout<<endl<<"States of Lights : "<<endl;
		PrintLights();
	}
}

///// 사용자의 입력을 한단계 취소 /////
void LightsOut::Undo()
{
	Node* pTemp = m_qsPosLog.PopFront();
	Light* pWalker = m_pHead;

	///// QueueStack 리스트가 비어있는 경우 이미 맵이 초기상태이므로 예외 처리 /////
	if(!pTemp)
	{
		cout<<endl;
		cout<<"You can't undoing..."<<endl;
		cout<<"The map is initialized state..."<<endl<<endl;
		cout<<"Undo count : "<<m_undoCnt<<endl;
	}

	else
	{
		m_undoCnt++;	//Undo 횟수를 Count
		
		///// UndoCount가 3을 넘어갈 경우 Undo를 수행하지 못한다 /////
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

		m_useCnt--;		// UserCount는 UndoCount가 하나씩 증가함에 따라 하나씩 감소한다.

		cout<<endl<<"States of Lights : "<<endl;
		PrintLights();
	}
}

///// 문제가 해결되었는지 확인 /////
bool LightsOut::IsSolved()
{
	Light* pRowWalker = m_pHead;
	Light* pColWalker = NULL;

	while(pRowWalker)
	{
		pColWalker = pRowWalker;

		while(pColWalker)
		{
			///// 어느 한 노드라도 'On' 상태를 가지는 노드가 있는경우 문제가 해결되지 않았다고 판단 /////
			if(pColWalker->GetState() == 1)
				return false;

			pColWalker = pColWalker->GetRight();
		}

		pRowWalker = pRowWalker->GetBottom();
	}

	return true;
}

///// 현제 맵의 상태를 보여주는 함수 /////
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

///// 사용자의 좌표, 횟수, 점수를 파일에 저장하는 함수 /////
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
