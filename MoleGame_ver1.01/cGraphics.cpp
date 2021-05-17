#include "stdafx.h"
#include "cGraphics.h"


cGraphics::cGraphics()
{
	D3DXCreateTextureFromFile(g_pDDevice, TEXT("pumpkin.jpg")
		, &m_pTexturePumpkin);
}


cGraphics::~cGraphics()
{
	SAFE_RELEASE(m_pTexturePumpkin);
}


void cGraphics::Release()
{
	SAFE_RELEASE(m_pTexturePumpkin);
}


void cGraphics::GetPumpkin(pTexture* pOut)
{
	*pOut = m_pTexturePumpkin;
}
