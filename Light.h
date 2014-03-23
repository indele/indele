#pragma once

#include <iostream>
#include <fstream>
#include <cstring>

class Light
{
private:
	Light* m_pRight;
	Light* m_pLeft;
	Light* m_pAbove;
	Light* m_pBottom;
	int m_state;

public:
	Light(void);
	~Light(void);
	void SetState(int state);
	void SetRight(Light* pRight);
	void SetLeft(Light* pLeft);
	void SetAbove(Light* pAbove);
	void SetBottom(Light* pBottom);
	int GetState();
	Light* GetRight();
	Light* GetLeft();
	Light* GetAbove();
	Light* GetBottom();
};
