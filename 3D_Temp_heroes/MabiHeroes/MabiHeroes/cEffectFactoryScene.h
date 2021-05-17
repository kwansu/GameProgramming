#pragma once
#include "cGameNode.h"
#include "stdObjects.h"

class cEffectManager;
class cEffectFactoryScene :
	public cGameNode
{
private:
	cGrid*			m_pGrid;


	vector<ST_PT_VERTEX>	m_vecWorldGrid;
	LPDIRECT3DTEXTURE9		m_pTexture;
	D3DLIGHT9				m_lightDirection;

	cEffectManager*			m_pEffectManager;


public:
	cEffectFactoryScene();
	~cEffectFactoryScene();
	// cGameNode override
	void Setup()	override;
	void Release()	override;
	void Update()	override;
	void Render()	override;
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

