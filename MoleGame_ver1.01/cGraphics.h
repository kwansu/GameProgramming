#pragma once

#define g_pGraphics cGraphics::GetInstance()

class cGraphics
{
	SINGLETONE(cGraphics);

private:
	pTexture m_pTexturePumpkin;

public:
	void GetPumpkin(pTexture* pOut);
	void Release();
};

