#include "stdafx.h"
#include "cEnemy.h"


cCreature*	cEnemy::s_pTarget = NULL;

cEnemy::cEnemy()
	: m_eActState(ACTION_COMMAND)
	, m_isActiveTurn(false)
	, m_fTurnSpeed(90)
	, ID(MONSTER_NULL)
{
}


cEnemy::~cEnemy()
{
}

void cEnemy::SetupCreature()
{
	if (!m_pMesh)
	{
		m_pMesh = new cSkinnedMesh;

		switch (ID)
		{
		case MONSTER_BOSS:
			break;
		case MONSTER_SKELARCHER:
			m_pMesh->Load("./DarkPawnArcher/", "Dark_Pawn_Archer.X", m_stBoundingSphere);
			
			break;
		}
	}

	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, 0.2f, 0.2f, 0.2f);
	SetOriginMatrix(matS);

	UpdateTransform();
}

void cEnemy::UpdateCreature()
{

	UpdateTransform();
	UpdateDirection();

	m_pMesh->Update(m_matWorld);

	temp_KeyStateControl();


}
void cEnemy::RenderCreature()
{
	m_pMesh->Render();
}
void cEnemy::ReleaseCreature()
{

}
void cEnemy::temp_KeyStateControl()
{
	if (g_pKeyManager->IsOnceKeyDown(VK_F1))
	{
		m_pState = STATE_NORMAL;
	}
	if (g_pKeyManager->IsOnceKeyDown(VK_F2))
	{
		m_pState = STATE_MOVE;
	}
	if (g_pKeyManager->IsOnceKeyDown(VK_F3))
	{
		m_pState = STATE_RUN;
	}
	if (g_pKeyManager->IsOnceKeyDown(VK_F4))
	{
		m_pState = STATE_ATTACK;
	}
	if (g_pKeyManager->IsOnceKeyDown(VK_F5))
	{
		m_pState = STATE_KNOCKBACK;
	}
	if (g_pKeyManager->IsOnceKeyDown(VK_F6))
	{
		m_pState = STATE_TIRED;
	}
	if (g_pKeyManager->IsOnceKeyDown(VK_F7))
	{
		m_pState = STATE_ROLLRUN;
	}
	if (g_pKeyManager->IsOnceKeyDown(VK_F8))
	{
		m_pState = STATE_KNOCKDOWN;
	}
	if (g_pKeyManager->IsOnceKeyDown(VK_F9))
	{
		m_pState = STATE_DOWNUP;
	}
	if (g_pKeyManager->IsOnceKeyDown(VK_F10))
	{
		m_pState = STATE_DEATH;
	}

}

bool cEnemy::IsFindTarget(OUT D3DXVECTOR3& vToTargetDir, OUT float& fDistance)
{
	vToTargetDir = s_pTarget->GetPosition() - m_vPos;
	fDistance = D3DXVec3Length(&vToTargetDir);

	vToTargetDir /= fDistance;

	if (fDistance > m_fDetectionRange)
		return false;

	return true;
}

float cEnemy::BetweenCosAngleFromTarget(const D3DXVECTOR3 & vToTargetDir, OUT bool& isClock)
{
	float result = D3DXVec3Dot(&vToTargetDir, &m_vDir);
	isClock = true;
	
	D3DXVECTOR3 vCross;
	D3DXVec3Cross(&vCross, &m_vDir, &vToTargetDir);

	if (vCross.y > 0)
		isClock = false;

	return result;
}

