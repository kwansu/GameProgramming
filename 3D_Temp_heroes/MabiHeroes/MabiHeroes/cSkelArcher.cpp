#include "stdafx.h"
#include "cSkelArcher.h"
using namespace ns_SKEL_ARCHER;

cSkelArcher::cSkelArcher()
{
	ID = MONSTER_SKELARCHER;
	m_fDetectionRange = 120.f;
	m_fAttackRange = 80.f;
	m_fSpeed = 1.3f;
}


cSkelArcher::~cSkelArcher()
{
}

void cSkelArcher::SetupCreature()
{
	cEnemy::SetupCreature();

	m_nHp = fHP_MAX;
}

void cSkelArcher::UpdateCreature()
{
	UpdateTransform();

	if (g_pKeyManager->IsOnceKeyDown('J'))
	{
		m_nAniCurrentState = ++m_nAniCurrentState % 31;
	}
}

