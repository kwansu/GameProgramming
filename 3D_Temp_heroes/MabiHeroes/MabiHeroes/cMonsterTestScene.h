#pragma once
#include "cGameNode.h"

class cGrid;
class cCamera;
class cSkelArcher;
class cObj_Fiona;

class cMonsterTestScene : public cGameNode
{
	cGrid*				m_pGrid;

	cSkelArcher*		m_pSkelArcher;
	cObj_Fiona*			m_pFiona;

	std::vector<ST_PN_VERTEX> m_vecVertex;
public:
	cMonsterTestScene();
	~cMonsterTestScene();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void SetLight();
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

