#pragma once
#include "stdObjects.h"

class cMainGame
{
private:
	DWORD	m_tNextTime;
	DWORD	m_tFrameTime;
	float	m_fFPS;

	int		m_nFrame;

	// 오브젝트 :
	cObject_Camera*			m_pCamera;
	cObject_Grid*			m_pGrid;
	cObject_MoleMachine*	m_pMachine;
	cObject_Hammer*			m_pHammer;

public:
	cMainGame();
	~cMainGame();

	void Initialize();
	void Release();
	void Run();
	void Update();
	void Render();
	void MessageHandler(UINT iMsg, WPARAM wp, LPARAM lp);
};

