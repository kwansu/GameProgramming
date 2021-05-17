#include "stdafx.h"
#include "cGraphics.h"


cGraphics::cGraphics()
:m_ptexGround(NULL), m_ptexMario(NULL)
{
}


cGraphics::~cGraphics()
{
	SAFE_RELEASE(m_ptexMario);
	SAFE_RELEASE(m_ptexGround);
}


void cGraphics::LoadTextrueFile()
{
	D3DXCreateTextureFromFile(g_pDevice,
		TEXT("image2.jpg"), &m_ptexMario);

	D3DXCreateTextureFromFile(g_pDevice,
		TEXT("111.jpg"), &m_ptexGround);
}


void cGraphics::Release()
{
	SAFE_RELEASE(m_ptexMario);
	SAFE_RELEASE(m_ptexGround);
}
