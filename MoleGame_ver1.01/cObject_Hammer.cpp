#include "stdafx.h"
#include "cObject_Hammer.h"
#include "stdObjects.h"


cObject_Hammer::cObject_Hammer()
	: m_childGrip(&m_matWorld), m_childHead(&m_matWorld)
	, m_paMoles(NULL), m_nIndex(0), m_nScore(0), m_bCollision(false)
	, m_bAttack(true), m_bReturn(false), m_fRot(HAMMER_SWING_ANGLE)
{
	m_childGrip.m_pChildObject = new cObject_Cube;
	m_childHead.m_pChildObject = new cObject_Cube;
	D3DXMatrixScaling(&m_childGrip.m_matPos, 1, 1, 5);
	D3DXMatrixScaling(&m_childHead.m_matPos, 2.5f, HAMMER_REACH, 2.5f);
	cMatrixA matPos;
	D3DXMatrixTranslation(&matPos, 0, 0, -7);
	m_childGrip.m_matPos *= matPos;
	m_str = m_strScore;
}


cObject_Hammer::~cObject_Hammer()
{
}


void cObject_Hammer::Setup()
{
	for (int x = -10; x <= 10; x += 10)
		for (int z = 10; z >= -10; z -= 10)
			m_aHolePos.push_back(cVec3(x, 0, z));

	m_vecCenter = cVec3(0, HAMMER_REACH+1, -HAMMER_HEIGHT);
	m_fAngleX = -90;
}


void cObject_Hammer::Update()
{
	if (m_bAttack)
	{
		for (int i = 0; i < 9; ++i)
			if (g_pInput->IsKeyPress('1' + i))
				SetSwing(i);

		for (int i = 0; i < 9; ++i)
			if (g_pInput->IsKeyPress(VK_NUMPAD1 + i))
				SetSwing(i);
	}
	else
	{
		m_vecInter += m_vecMove * (m_bReturn ? -1 : 1);
		m_fAngleX += m_fRot * (m_bReturn ? -1 : 1);

		if (m_fAngleX >= 0)
			m_bReturn = true;
		
		if (m_fAngleX <= -90)
			m_bAttack = true;

		if (!m_bCollision)
		{
			if ((*m_paMoles)[m_nIndex].IsCollision((cObject_Cube*)m_childHead.m_pChildObject))
			{
				(*m_paMoles)[m_nIndex].Collision();
				m_bReturn = true;
				m_bCollision = true;
				if (!(*m_paMoles)[m_nIndex].IsLive())
					++m_nScore;
			}
		}
	}

	wsprintf(m_str, TEXT("SCORE : %d , LEVEL : %d"), m_nScore, g_nStage);
	SetWindowText(g_hWnd, m_str);

	UpdateRotateMatrix();
	D3DXVec3TransformCoord(&m_vecPos, &cVec3(0, 0, HAMMER_HEIGHT), &m_matRot);
	m_vecPos += m_vecCenter + m_vecInter;
}


void cObject_Hammer::Render()
{
	UpdateWorldMatrix();
	m_childHead.Render();
	m_childGrip.Render();
}


void cObject_Hammer::SetSwing(int nIndex)
{
	m_vecMove = m_aHolePos[nIndex];
	m_vecMove.y = 0;
	m_vecMove /= HAMMER_SWING_FRAME;
	m_fRot = HAMMER_SWING_ANGLE;
	m_nIndex = nIndex;

	m_bCollision = false;
	m_bAttack = false;
	m_bReturn = false;
}


void cObject_Hammer::SetArrayCube(vector<cObject_Mole>* paMoles)
{
	m_paMoles = paMoles;
}
