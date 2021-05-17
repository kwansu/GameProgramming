#pragma once

class cTimeManager
{
	SINGLETON(cTimeManager);

private:
	DWORD m_dwLastUpdateTime;
	DWORD m_dwDeltaTime;
	float	m_Second;
	int		m_secondFrame;
public:
	void Update();
	float GetDeltaTime();
};

extern cTimeManager* g_pTimeManager;
