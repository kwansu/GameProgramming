#pragma once
#include "cGameNode.h"
#include "stdObjects.h"

class cBattleRoomScene :
	public cGameNode
{
private:
	vector<ST_PT_VERTEX>	m_vecWorldGrid;
	LPDIRECT3DTEXTURE9		m_pTexture;

public:
	cBattleRoomScene();
	~cBattleRoomScene();

	// cGameNode override
	void Setup()	override;
	void Release()	override;
	void Update()	override;
	void Render()	override;
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

