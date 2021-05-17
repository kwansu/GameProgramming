#include "stdafx.h"
#include "cProgressBar.h"


cProgressBar::cProgressBar()
	//: m_pUIText(NULL)
{
}


cProgressBar::~cProgressBar()
{
}

void cProgressBar::Setup()
{
	//m_pUIText = new cUIText;
	//m_pUIText->Setup(25, 12, "돋움체");


	m_pTexHp = g_pTextureManager->GetTexture("./3dObject/UI/bar_hp_front.tga", &m_stII);
	m_pTexHpBack = g_pTextureManager->GetTexture("./3dObject/UI/bar_hp_back.tga", &m_stII);

	m_pTexStm = g_pTextureManager->GetTexture("./3dObject/UI/bar_stm_front.tga", &m_stII);
	m_pTexStmBack = g_pTextureManager->GetTexture("./3dObject/UI/bar_stm_back.tga", &m_stII);


	m_vPos.x =	540;
	m_vPos.y =	6;

	m_vScale.x = 1.1f;
	m_vScale.y = 1.4f;

	m_vecScale.x = 1.1f;
	m_vecScale.y = 1.1f;

	D3DXMatrixTranslation(&m_matT, m_vPos.x, m_vPos.y, m_vPos.z);
	D3DXMatrixScaling(&m_matS, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixScaling(&m_mScale, m_vecScale.x, m_vecScale.y, m_vecScale.z);
}

void cProgressBar::Update()
{
}

void cProgressBar::Render(int xLeft, int yTop/*, D3DXMATRIXA16 * matW*/)
{
	RECT rcHpFront, rcHpBack, rcStmFront, rcStmBack;

	SetRect(&rcHpBack,
		xLeft, yTop,
		m_stII.Width,
		m_stII.Height);

	m_pD3DSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	m_matWorld = m_matS * m_matT;

	m_pD3DSprite->SetTransform(&m_matWorld);

	m_pD3DSprite->Draw(m_pTexHpBack,
		&rcHpBack,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(100, 255, 255, 255));
	
	
	SetRect(&rcHpFront,
		xLeft, yTop,
		m_stII.Width * (float(*m_pHp) / MAX_HP),
		m_stII.Height);

	m_pD3DSprite->Draw(m_pTexHp,
		&rcHpFront,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(255, 255, 255, 255));

	///////////////////스태미나

	m_matWorld = m_mScale * m_matT;
	
	m_pD3DSprite->SetTransform(&m_matWorld);

	SetRect(&rcStmBack,
		xLeft, yTop,
		m_stII.Width,
		m_stII.Height);

	m_pD3DSprite->Draw(m_pTexStmBack,
		&rcStmBack,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 10.5, 0),
		D3DCOLOR_ARGB(100, 255, 255, 255));

	SetRect(&rcStmFront,
		xLeft, yTop,
		m_stII.Width * (float(*m_pStamina) / MAX_STAMINA),
		m_stII.Height);

	m_pD3DSprite->Draw(m_pTexStm,
		&rcStmFront,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 10.5, 0),
		D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pD3DSprite->End();

	//m_pUIText->Render(m_vPos.x, m_vPos.y, "1000", 0, 0, 0);
}