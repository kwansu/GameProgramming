#pragma once

#define g_pTime cTime::GetInstance()

class cTime
{
	SINGLETONE(cTime);

private:
	float	m_fAverageFPS;		//10프레임의 평균 FPS
	float	m_fFPS;				//설정해주는 FPS
	DWORD	m_tFrameTime;		//한 프레임 간격

	DWORD	m_tCurrentTime;		//현재 컴퓨터 틱카운터
	DWORD	m_tExitTime;		//프레임 끝날때의 시간
	DWORD	m_tElapseTime;		//프레임 시작후 경과시간
	DWORD	m_tGameTime;		//게임의 경과시간
	
public:
	void AdjustTime();
	void SetFPS(float fFPS)		{ m_fFPS = fFPS; }
	float GetFPS()	const		{ return m_fFPS; }
};

