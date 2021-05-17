#include "stdafx.h"
#include "cQuickSlot.h"


cQuickSlot::cQuickSlot()
{
}


cQuickSlot::~cQuickSlot()
{
}

void cQuickSlot::Setup()
{
	m_pTexQuickSlot = g_pTextureManager->GetTexture("./3dObject/UI/quickslot.png", &m_stII);

	m_vPos.x = 0;
	m_vPos.y = -8.0;

	m_vScale.x = 0.9f;
	m_vScale.y = 0.9f;

	D3DXMatrixTranslation(&m_matT, m_vPos.x, m_vPos.y, m_vPos.z);
	D3DXMatrixScaling(&m_matS, m_vScale.x, m_vScale.y, m_vScale.z);
}

void cQuickSlot::Update()
{
}

void cQuickSlot::Render(int xLeft, int yTop)
{
	RECT rcSlot;

	SetRect(&rcSlot,
		xLeft, yTop,
		m_stII.Width,
		m_stII.Height);

	m_pD3DSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	m_matWorld = m_matS * m_matT;

	m_pD3DSprite->SetTransform(&m_matWorld);

	m_pD3DSprite->Draw(m_pTexQuickSlot,
		&rcSlot,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_XRGB(255, 255, 255));

	m_pD3DSprite->End();
}
