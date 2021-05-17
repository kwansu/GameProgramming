#include "stdafx.h"
#include "cObject_Limbs.h"


cObject_Limbs::cObject_Limbs(bool bRight)
	: m_bRight(true), m_pmatParent(NULL)
	, m_fSwingSpeed(3.f), m_bWalk(false)
{
	D3DXMatrixIdentity(&m_matLocal);

	int size = m_aVertexPN.size();
	for (int i = 0; i < size; ++i)
		m_aVertexPN[i].pos.y -= 1;

	size = m_aLocalPos.size();
	for (int i = 0; i < size; ++i)
		m_aLocalPos[i].y -= 1;

	if (bRight)
		m_fSwingSpeed *= -1;
}


cObject_Limbs::~cObject_Limbs()
{
}


void cObject_Limbs::Setup(cMatrixA* pmatParent, float px, float py, float pz)
{
	int size = m_aVertexPNT.size();
	for (int i = 0; i < size; ++i)
		m_aVertexPNT[i].pos.y -= 2;

	m_pmatParent = pmatParent;
	D3DXMatrixTranslation(&m_matLocal, px, py, pz);
	UpdateWorld();

	//if (!m_pCollider)
	//	m_pCollider = new cCollider(&m_matWolrd);
	//m_pCollider->Setup(&m_aLocalPos);
}


void cObject_Limbs::Update()
{
	if (m_fAngleX > -60)
	{
		if (m_fAngleX > 30)
		{
			m_fSwingSpeed *= -1;
			m_fAngleX = 30;
		}
		if (m_fAngleX < -30)
		{
			m_fSwingSpeed *= -1;
			m_fAngleX = -30;
		}

		if (m_bWalk)
		{
			m_fAngleX += m_fSwingSpeed;
		}
		else
		{
			if (fabs(m_fAngleX) > fabs(m_fSwingSpeed))
				m_fAngleX -= m_fSwingSpeed;
			else
				m_fAngleX = 0;
		}

		m_bWalk = false;
	}
	UpdateWorld();
	m_matWolrd *= m_matLocal;

	if (m_pmatParent)
		m_matWolrd *= *m_pmatParent;

	//m_pCollider->Update();
}


void cObject_Limbs::Render()
{
	cObject_Cube::Render();
}


void cObject_Limbs::Walking()
{
	m_bWalk = true;
}


