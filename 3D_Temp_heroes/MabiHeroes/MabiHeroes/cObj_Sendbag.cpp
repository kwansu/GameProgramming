#include "stdafx.h"
#include "cObj_Sendbag.h"


cObj_Sendbag::cObj_Sendbag()
{
}


cObj_Sendbag::~cObj_Sendbag()
{
}

void cObj_Sendbag::Setup()
{
	ST_COLLISION_BOX_STICK coll;

	coll.pmatSticking = &m_matWorld;
	coll.vHalfSize = D3DXVECTOR3(5, 10, 5);
	m_vecCollisionBox.push_back(coll);

	m_vPos.z = -20;

	m_vPos.y = 10;
	UpdateTransform();
}

void cObj_Sendbag::Update()
{
}

void cObj_Sendbag::Render()
{
	g_pCollisionRender->RenderBox(m_vecCollisionBox[0], &m_color);
	m_color = D3DXCOLOR(1, 0, 0, 1);
}

void cObj_Sendbag::Damaged(float fDamege, cGameObject * pAttacker, bool isSmash)
{
	m_color = D3DXCOLOR(0, 1, 0, 1);
}

