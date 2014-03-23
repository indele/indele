#pragma once

#include "Light.h"
#include "QueueStack.h"
#include "Functions.h"

class LightsOut
{
private:
	Light* m_pHead;
	QueueStack m_qsPosLog;
	int m_undoCnt;
	int m_mapID;
	int m_minCnt;
	int m_useCnt;

public:
	LightsOut(void);
	~LightsOut(void);
	bool LoadMap(char* fname);
	bool LightOnOff(int x, int y);
	bool Push(int x, int y);
	void Undo();
	void Reset();
	bool IsSolved();
	void PrintLights();
	void RecordSolution(char* fname);
};
