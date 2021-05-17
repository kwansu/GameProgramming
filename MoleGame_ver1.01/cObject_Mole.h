#pragma once
#include "cObject_Cube.h"

#define MOLE_MOVE_SPEED		0.2
#define MOLE_IDLE_TIME		800
#define MOLE_ACTIVE_TIME	1500
#define MOLE_HEIGHT			3

class cObject_Mole :
	public cObject_Cube
{
private:
	bool		m_bActice;
	bool		m_bUp;
	int			m_nLive;
	DWORD		m_tEventTime;

public:
	static int*	s_pActiveCount;
	static int*	s_pDeathCount;

	cObject_Mole();
	~cObject_Mole();
	void Setup();
	void Update();
	void Render();
	bool IsActicve()	{ return m_bActice; }
	void Collision();
	bool IsLive();
};

