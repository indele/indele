#include "Light.h"

Light::Light(void)
{
	m_pRight = NULL;
	m_pLeft = NULL;
	m_pAbove = NULL;
	m_pBottom = NULL;
	m_state = 0;
}

Light::~Light(void) {}

void Light::SetState(int state)
{
	m_state = state;
}

void Light::SetRight(Light* pRight)
{
	m_pRight = pRight;
}

void Light::SetLeft(Light* pLeft)
{
	m_pLeft = pLeft;
}

void Light::SetAbove(Light* pAbove)
{
	m_pAbove = pAbove;
}

void Light::SetBottom(Light* pBottom)
{
	m_pBottom = pBottom;
}

int Light::GetState()
{
	return m_state;
}

Light* Light::GetRight()
{
	return m_pRight;
}

Light* Light::GetLeft()
{
	return m_pLeft;
}

Light* Light::GetAbove()
{
	return m_pAbove;
}

Light* Light::GetBottom()
{
	return m_pBottom;
}
