#include "stdafx.h"
#include "cWearItem.h"


cWearItem::cWearItem()
	: m_pMesh(NULL)
	, m_pmatParent(NULL)
{
	D3DXMatrixIdentity(&m_matR);
	D3DXMatrixIdentity(&m_matS);
	D3DXMatrixIdentity(&m_matT);
}


cWearItem::~cWearItem()
{
}

void cWearItem::Setup(string filePath, D3DXMATRIXA16* matParent)
{
	m_pmatParent = matParent;

	D3DXMATRIXA16 idintity;
	D3DXMatrixIdentity(&idintity);
	if (m_pmatParent)
	{
		ST_SPHERE coll;
		m_pMesh = new cSkinnedMesh;
		m_FileName = filePath;
		if (filePath == "sword2.x")
		{
			m_pMesh->Load("./3dObject/Sword/", (char*)filePath.c_str(), coll);
			D3DXMatrixRotationZ(&m_matR, D3DXToRadian(285));
			D3DXMatrixScaling(&m_matS, 2, 2, 2);
			D3DXMatrixTranslation(&m_matT, 5, 1, 0);
		}
		else if (filePath == "sword.x")
		{
			m_pMesh->Load("./3dObject/Sword/", (char*)filePath.c_str(), coll);
			D3DXMatrixRotationY(&m_matR, D3DXToRadian(-90));
		}
		else if (filePath == "hammer.x")
		{
			m_pMesh->Load("./3dObject/Monster/weapon/", (char*)filePath.c_str(), coll);
			D3DXMatrixRotationY(&m_matR, D3DXToRadian(-90));

		}
		else if (filePath == "shield.x")
		{
			m_pMesh->Load("./3dObject/Shield/", (char*)filePath.c_str(), coll);
			D3DXMatrixRotationX(&m_matR, D3DXToRadian(80));

			D3DXMATRIXA16 matZ;
			D3DXMatrixRotationY(&matZ, D3DXToRadian(180));
			m_matR *= matZ;
			D3DXMatrixTranslation(&m_matT, 8, 3, 0);
		}
		else if (filePath == "paladin_sword.x")
		{
			m_pMesh->Load("./3dObject/Sword/paladin/", (char*)filePath.c_str(), coll);
			D3DXMatrixRotationY(&m_matR, D3DXToRadian(-90));
			D3DXMatrixScaling(&m_matS, 1.4, 1.4, 1.4);
			D3DXMatrixTranslation(&m_matT, 5, 1, 0);
		}
		else if (filePath == "paladin_shield.x")
		{
			m_pMesh->Load("./3dObject/shield/paladin/", (char*)filePath.c_str(), coll);
			D3DXMatrixRotationX(&m_matR, D3DXToRadian(90));
			D3DXMatrixTranslation(&m_matT, 12, 3, 0);
		}
		else if (filePath == "bow.x")
		{
			m_pMesh->Load("./3dObject/woodenelf/", (char*)filePath.c_str(), coll);
			D3DXMatrixRotationY(&m_matR, D3DXToRadian(90));
			//D3DXMatrixTranslation(&m_matT, 12, 3, 0);
		}
	}
}

void cWearItem::Update()
{
	D3DXMATRIXA16 idintity;
	D3DXMatrixIdentity(&idintity);
	static float angle = 0.f;
	if (m_pMesh)
	{
		m_matWrodl = m_matS * m_matR * m_matT * *m_pmatParent ;
		m_pMesh->Update(m_matWrodl);

	}

	m_SwingEffect.m_vecEffect_Swing_Down.x = m_matWrodl._41;
	m_SwingEffect.m_vecEffect_Swing_Down.y = m_matWrodl._42;
	m_SwingEffect.m_vecEffect_Swing_Down.z = m_matWrodl._43;

	D3DXVECTOR3	vecUp;
	if (m_FileName == "sword.x" || m_FileName == "sword2.x")
	{
		vecUp = { 0, 0, -65 };
	}
	else
	{
		vecUp = { 0, 0, -50 };
	}
	D3DXVec3TransformCoord(&vecUp, &vecUp, &m_matWrodl);
	m_SwingEffect.m_vecEffect_Swing_Up = vecUp;

}

void cWearItem::Render()
{
	if (m_pMesh)
		m_pMesh->Render();
}

void cWearItem::Release()
{
}

void cWearItem::SetParent(D3DXMATRIXA16 * matParent)
{
	m_pmatParent = matParent;
}

void cWearItem::SetPosition(int px, int py, int pz)
{
	D3DXMatrixTranslation(&m_matT, px, py, pz);
}
