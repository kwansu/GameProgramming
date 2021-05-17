#pragma once

#define g_pUIManager	cUIManager::GetInstance()

class cUIManager
{
	SINGLETON(cUIManager);

private:
	LPD3DXSPRITE	m_pSprite;
	LPD3DXFONT		m_pFont;

public:
	void Setup();
	void Update();
	void Render();
};

