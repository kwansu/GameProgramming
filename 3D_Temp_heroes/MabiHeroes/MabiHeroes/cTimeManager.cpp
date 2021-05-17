#include "StdAfx.h"
#include "cTimeManager.h"


cTimeManager* g_pTimeManager = cTimeManager::GetInstance();

float	g_fDeltaTime = 0;

cTimeManager::cTimeManager(void)
	: m_dwDeltaTime(0)
	, m_Second(0.f)
	, m_secondFrame(0)
{
	m_dwLastUpdateTime = GetTickCount();
}


cTimeManager::~cTimeManager(void)
{
}

float cTimeManager::GetDeltaTime()
{
	return (float) m_dwDeltaTime * 0.001f;
}

void cTimeManager::Update()
{
	DWORD dwCurrTime = GetTickCount();
	m_dwDeltaTime = dwCurrTime - m_dwLastUpdateTime;
	g_fDeltaTime = m_dwDeltaTime * 0.001f;
	m_dwLastUpdateTime = dwCurrTime;

	//m_Second += m_dwDeltaTime;
	//++m_secondFrame;
	//if (m_Second > 1000)
	//{
	//	cout << m_secondFrame * 1000 / (float)m_Second << endl;
	//	m_Second = 0;
	//	m_secondFrame = 0;
	//}
}
