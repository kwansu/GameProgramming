#pragma once

#define g_pInput cInput::GetInstance()


class cInput
{
	SINGLETONE(cInput);

private:
	bool	m_aInputKey[256];
	POINT	m_ptMouse;
	POINT	m_ptMouseBefore;
	POINT	m_ptMouseInterval;
	int		m_nMouseWheel;

public:
	void Update();
	void KeyDown(char VK)		{ m_aInputKey[VK] = true; }
	void KeyUp(char VK)			{ m_aInputKey[VK] = false; }
	bool IsKeyPress(char VK)	{ return m_aInputKey[VK]; }
	void SetMouse(int x, int y)	{ m_ptMouse = { x, y }; }
	POINT GetMousePos()			{ return m_ptMouse; }
	POINT GetMouseInterval()	{ return m_ptMouseInterval; }
	void AddWheel(short val)	{ m_nMouseWheel += val; }
	int GetMouseWheel()			{ return m_nMouseWheel; }
};