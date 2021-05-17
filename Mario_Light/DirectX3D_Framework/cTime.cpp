#include "stdafx.h"
#include "cTime.h"


cTime::cTime()
	: m_fAverageFPS(0), m_fFPS(60), m_tFrameTime(1000/60.f)
	, m_tExitTime(0), m_tElapseTime(0)
{
	m_tCurrentTime = GetTickCount();
	m_tGameTime = m_tCurrentTime;
}


cTime::~cTime()
{
}


void cTime::AdjustTime()
{
	m_tCurrentTime = GetTickCount();
	m_tElapseTime = m_tCurrentTime - m_tExitTime;
	m_tGameTime += m_tElapseTime;

	if (m_tElapseTime < m_tFrameTime)
		Sleep(m_tFrameTime - m_tElapseTime);
}
