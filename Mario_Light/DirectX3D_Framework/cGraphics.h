#pragma once

#define g_pGraphics cGraphics::GetInstance()

class cGraphics
{
	SINGLETONE(cGraphics);

private:

public:
	pTexture	m_ptexMario;
	pTexture	m_ptexGround;
	void LoadTextrueFile();
	void Release();
};

