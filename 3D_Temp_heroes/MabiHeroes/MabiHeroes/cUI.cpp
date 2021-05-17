#include "stdafx.h"
#include "cUI.h"


cUI::cUI()
	//: m_pTexture(NULL)
{
	ZeroMemory(&m_stII, sizeof(D3DXIMAGE_INFO));
	D3DXMatrixIdentity(&m_matT);
	D3DXMatrixIdentity(&m_matR);
	D3DXMatrixIdentity(&m_matWorld);

	D3DXCreateSprite(g_pD3DDevice, &m_pD3DSprite);
}

cUI::~cUI()
{
}
