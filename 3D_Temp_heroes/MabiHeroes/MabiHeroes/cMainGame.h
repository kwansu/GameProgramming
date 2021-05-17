#pragma once
#include "cGameNode.h"
#include "cMonsterTestScene.h"
#include "cCollisionTestScene.h"
#include "cEditScene.h"
#include "cMainScene.h"
#include "cBattleRoomScene.h"

class cMainGame : public cGameNode
{
private:
	cGameNode*	m_pSceneMonsterTest;
	cGameNode*	m_pSceneMain;

	D3DLIGHT9	m_lightDirection;

public:
	cMainGame(void);
	~cMainGame(void);

	void Setup();
	void Release();
	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

