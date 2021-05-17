#include "stdafx.h"
#include "cEquipment.h"


cEquipment::cEquipment()
	: m_isSwitch(false)
	, m_pFiona(NULL)
{
}


cEquipment::~cEquipment()
{
}

void cEquipment::Setup()
{
	m_pTexEquip = g_pTextureManager->GetTexture("./3dObject/UI/equipment.png", &m_stII);
	//m_pTexEquipCheck = g_pTextureManager->GetTexture("./3dObject/UI/equipCheck.png", &m_stII);


	m_vPos.x = 870;
	m_vPos.y = 30;

	D3DXMatrixTranslation(&m_matT, m_vPos.x, m_vPos.y, m_vPos.z);


	for (int i = 0; i < 2; ++i)
	{
		SetRect(&m_stRc[i].rc, 1131 + i * 43, 121, 1174 + i * 43, 164);
		m_stRc[i].isClick = false;
	}




	g_pSoundManager->addSound("장비창", "./3dObject/Sound/ui_equip_item.wav", false, false);
}

void cEquipment::Update()
{
	if (g_pKeyManager->IsOnceKeyDown('B') || g_pKeyManager->IsOnceKeyDown('I'))
	{
		g_pSoundManager->play("장비창", 0.3f);
		g_pCamera->SetIsUiLock(true);
		//m_isOpen = true;

		if (!m_isSwitch)
			m_isSwitch = true;
		else
			m_isSwitch = false;
	}
	
	if (g_pCamera->GetIsUiLock())
	{
		if (g_pKeyManager->IsOnceKeyDown(VK_LBUTTON))
		{
			m_isOpen = false;
			g_pCamera->SetIsUiLock(false);
		}
	}

	POINT ptMouse;

	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);


	if (g_pCamera->GetIsUiLock())
	{
		if (g_pKeyManager->IsOnceKeyDown(VK_RBUTTON))
		{
			int a = 0;

			for (int i = 0; i < 2; ++i)
			{
				if (PtInRect(&m_stRc[i].rc, ptMouse))
				{
					m_pFiona->ChangeEquip(i);
					if(!m_stRc[i].isClick)
						m_stRc[i].isClick = true;	
					else
						m_stRc[i].isClick = false;
				}
			}
		}
	}

}

void cEquipment::Render(int xLeft, int yTop)
{
	RECT rcEquip;

	SetRect(&rcEquip,
		xLeft, yTop,
		m_stII.Width,
		m_stII.Height);


	if (m_isSwitch)
	{
		m_pD3DSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

		m_matWorld = m_matT;

		m_pD3DSprite->SetTransform(&m_matWorld);

		m_pD3DSprite->Draw(m_pTexEquip,
			&rcEquip,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			D3DCOLOR_XRGB(255, 255, 255));

		//for (int i = 0; i < 2; ++i)
		//{
		//	m_matWorld = m_matT;
		//
		//	m_pD3DSprite->SetTransform(&m_matWorld);
		//
		//	m_pD3DSprite->Draw(m_pTexEquip,
		//		&m_stRc[i].rc,
		//		&D3DXVECTOR3(0, 0, 0),
		//		&D3DXVECTOR3(0, 0, 0),
		//		D3DCOLOR_XRGB(255, 255, 255));
		//}
		m_pD3DSprite->End();

	}
}

void cEquipment::SetFiona(cObj_Fiona* fiona)
{
	m_pFiona = fiona;
}
