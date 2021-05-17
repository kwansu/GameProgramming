#pragma once
#include "stdObjects.h"

class cMainGame
{
private:
	// ������Ʈ ������ �ʱ�ȭ
	cObject_Camera*			m_pCamera;
	cGrid*					m_pGrid;
	cObject_Mario*			m_pMario;
	vector<cObject_Plane*>	m_apPlanes;

public:
	cMainGame();
	~cMainGame();

	void Initialize();
	void Release();
	void Run();
	void Update();
	void Render();
	void MessageHandler(UINT iMsg, WPARAM wp, LPARAM lp);
	void DialogHandler(HWND hDlg, UINT iMsg, WPARAM wp, LPARAM lp);
};

