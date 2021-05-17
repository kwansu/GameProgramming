#include "stdafx.h"
#include "cObject_Mario.h"


cObject_Mario::cObject_Mario()
	: m_fLookSpeed(0), m_fUpSpeed(0)
	, m_bBottom(true), m_papPlane(NULL)
	, m_pChildHead(NULL), m_pChildLArm(NULL)
	, m_pChildRArm(NULL), m_pChildLLeg(NULL)
	, m_pChildRLeg(NULL)
{
}


cObject_Mario::~cObject_Mario()
{
	SAFE_DELETE(m_pChildHead);
	SAFE_DELETE(m_pChildLArm);
	SAFE_DELETE(m_pChildRArm);
	SAFE_DELETE(m_pChildLLeg);
	SAFE_DELETE(m_pChildRLeg);
}


void cObject_Mario::Setup(vector<cObject_Plane*>* papPlane)
{
	m_papPlane = papPlane;

	SetLocalSize(2.1f, 3.1f, 1);

	m_pCollider = new cCollider(&m_matWolrd);
	m_pCollider->Setup(&m_aLocalPos);

	m_pChildHead = new cObject_Mario_Head;
	m_pChildHead->SetLocalSize(2.1f, 2.f, 2.f);
	m_pChildHead->Setup(&m_matWolrd, 0, 7.1f, 0);

	m_pChildLArm = new cObject_Limbs(false);
	m_pChildLArm->SetLocalSize(1, 3.2f, 1);
	m_pChildLArm->Setup(&m_matWolrd, 3.2f, 3.1f, 0);

	m_pChildRArm = new cObject_Limbs(true);
	m_pChildRArm->SetLocalSize(1, 3.2f, 1);
	m_pChildRArm->Setup(&m_matWolrd,-3.2f, 3.1f, 0);

	m_pChildLLeg = new cObject_Limbs(false);
	m_pChildLLeg->SetLocalSize(1, 3.2f, 1);
	m_pChildLLeg->Setup(&m_matWolrd, 1.1f,-3.2f, 0);
			
	m_pChildRLeg = new cObject_Limbs(true);
	m_pChildRLeg->SetLocalSize(1, 3.2f, 1);
	m_pChildRLeg->Setup(&m_matWolrd,-1.1f,-3.2f, 0);

	m_vPos.y = 30;
	UpdateWorld();
}


void cObject_Mario::Update()
{
	if (g_pInput->IsKeyPress('D'))
	{
		m_fLookSpeed += MARIO_ACCELERATION;
		m_pChildLArm->Walking();
		m_pChildRArm->Walking();
		m_pChildLLeg->Walking();
		m_pChildRLeg->Walking();
		m_fAngleY = 180;
	}
	else if (g_pInput->IsKeyPress('A'))
	{
		m_fLookSpeed -= MARIO_ACCELERATION;
		m_pChildLArm->Walking();
		m_pChildRArm->Walking();
		m_pChildLLeg->Walking();
		m_pChildRLeg->Walking();
		m_fAngleY = 0;
	}
	else if (m_fLookSpeed)
		m_fLookSpeed += m_fLookSpeed > 0 ? -MARIO_ACCELERATION : MARIO_ACCELERATION;

	//if (g_pInput->IsKeyPress('A'))
	//	m_fAngleY -= MARIO_ROTATE_SPEED;

	//if (g_pInput->IsKeyPress('D'))
	//	m_fAngleY += MARIO_ROTATE_SPEED;

	if (m_fLookSpeed > 1.5f)	m_fLookSpeed = 1.5f;
	if (m_fLookSpeed < -1.5f)		m_fLookSpeed = -1.5f;
	if (fabs(m_fLookSpeed) < MARIO_ACCELERATION)
		m_fLookSpeed = 0;

	if (m_bBottom)
	{
		if (g_pInput->IsKeyPress(VK_SPACE))
		{
			m_fUpSpeed = MARIO_JUMP_POWER;
		}
	}
	else
	{
		m_fUpSpeed -= GRVITY_ACCELERATION;
	}
	m_vPos += m_vLook * m_fLookSpeed + cVec3(0, 1, 0) * m_fUpSpeed;

	if (m_vPos.y < -40)
		m_vPos = cVec3(0, 3, 0);

	UpdateWorld();

	m_pCollider->Update();
	m_pChildHead->Update();
	m_pChildLArm->Update();
	m_pChildLLeg->Update();
	m_pChildRArm->Update();
	m_pChildRLeg->Update();

	m_pCollider->SetMinMax(m_pChildHead->GetCollider());
	m_pCollider->SetMinMax(m_pChildLArm->GetCollider());
	m_pCollider->SetMinMax(m_pChildLLeg->GetCollider());
	m_pCollider->SetMinMax(m_pChildRArm->GetCollider());
	m_pCollider->SetMinMax(m_pChildRLeg->GetCollider());

	CollisionHandling();

	UpdateWorld();
}


void cObject_Mario::Render()
{
	m_pChildHead->Render();
	m_pChildLArm->Render();
	m_pChildLLeg->Render();
	m_pChildRArm->Render();
	m_pChildRLeg->Render();

	cObject_Cube::Render();
}


void cObject_Mario::CollisionHandling()
{
	if (!m_papPlane)
		return;

	m_bBottom = false;
	cVec3 vOverlap;

	int size = m_papPlane->size();
	for (int i = 0; i < size; ++i)
	{
		if (m_pCollider->InterceptCube(&vOverlap, (*m_papPlane)[i]->GetCollider()))
		{
			if (abs(vOverlap.y) <= MIN(abs(vOverlap.x), abs(vOverlap.z)))
			{
				if (vOverlap.y > 0) m_bBottom = true;
				m_vPos.y += vOverlap.y;
				m_fUpSpeed = 0;
			}
			else
			{
				if (abs(vOverlap.x) <= abs(vOverlap.z))
					m_vPos.x += vOverlap.x;
				else
					m_vPos.z += vOverlap.z;
			}
		}
	}
}
