#pragma once

#define g_pTime cTime::GetInstance()

class cTime
{
	SINGLETONE(cTime);

private:
	float	m_fAverageFPS;		//10�������� ��� FPS
	float	m_fFPS;				//�������ִ� FPS
	DWORD	m_tFrameTime;		//�� ������ ����

	DWORD	m_tCurrentTime;		//���� ��ǻ�� ƽī����
	DWORD	m_tExitTime;		//������ �������� �ð�
	DWORD	m_tElapseTime;		//������ ������ ����ð�
	DWORD	m_tGameTime;		//������ ����ð�
	
public:
	void AdjustTime();
	void SetFPS(float fFPS)		{ m_fFPS = fFPS; }
	float GetFPS()	const		{ return m_fFPS; }
};

