#include "stdafx.h"
#include "cNoll.h"
#include "cSkinnedMesh.h"

cNoll::cNoll()
	: m_currentState(NOLL_STATE_NOMAL)
	, m_oldState(NOLL_STATE_NOMAL)
	, m_Hp(100.f)
	, m_isFight(false)
	, m_playAniNum(NOLL_ANI_NOMAL)
	, m_attackDilay(0.f)
{
	m_pTarget = NULL;
	m_statePriority[(int)NOLL_STATE_NOMAL] = 6;			// 비교 숫자가 낮으면 변경 불가.
	m_statePriority[(int)NOLL_STATE_DIE] = 0;
	m_statePriority[(int)NOLL_STATE_WALK] = 4;
	m_statePriority[(int)NOLL_STATE_HIT] = 2;
	m_statePriority[(int)NOLL_STATE_HITFLYING] = 1;
	m_statePriority[(int)NOLL_STATE_ATTACK] = 3;
	m_statePriority[(int)NOLL_STATE_TURN] = 5;

	m_saveTime = 0.f;
	//m_vPos.x = -100;
	//m_vPos.z = 5;

}


cNoll::~cNoll()
{
}



void cNoll::SetupCreature()
{
	m_pMesh = new cSkinnedMesh;
	m_pMesh->Load("./3dObject/Monster/", "gnoll.X", m_stBoundingSphere);

	m_pmatClub = m_pMesh->SearchMat("ValveBiped_Anim_Attachment_RH");
	m_hammer = new cWearItem;
	m_hammer->Setup("hammer.x", m_pmatClub);

	this->AnimationToState();

	D3DXMATRIXA16 matOrigin;
	D3DXMatrixScaling(&matOrigin, 0.2f, 0.2f, 0.2f);
	SetOriginMatrix(matOrigin);

	m_fMoveRadius = 3.7f;

	cCreature::LoadHitBox("./GameData/gnoll.txt", matOrigin);

	g_pSoundManager->addSound("기본소리", "./3dObject/Sound/monster/noll_breath1.wav", false, false);
	g_pSoundManager->addSound("기본히트", "./3dObject/Sound/monster/Hit_Flesh_Slash_adult.wav", false, false);


}

void cNoll::ReleaseCreature()
{

}

void cNoll::UpdateCreature()
{
	if (m_playAniNum == NOLL_ANI_SMASH_ATTACK)
	{
		m_saveTime += g_fDeltaTime;
		if (m_saveTime >= 0.1f)
		{
			g_pEffectManager->AddSwingEffect("NOLL", m_hammer->GetSwingEffectVec().m_vecEffect_Swing_Up, m_hammer->GetSwingEffectVec().m_vecEffect_Swing_Down);
			m_saveTime -= 0.02f;
		}
	}
	else if (m_playAniNum == NOLL_ANI_DOUBLE_ATTACK)
	{
		m_saveTime += g_fDeltaTime;
		if (m_saveTime >= 0.02f)
		{
			g_pEffectManager->AddSwingEffect("NOLL", m_hammer->GetSwingEffectVec().m_vecEffect_Swing_Up, m_hammer->GetSwingEffectVec().m_vecEffect_Swing_Down);
			m_saveTime -= 0.02f;
		}
	}
	UpdateDirection();
	if (m_pTarget)
	{
		this->NollShiftMoveUpdate();
		this->CircleAttackDilay();

		D3DXVECTOR3 vLook;
		vLook = *m_pTarget - m_vPos;
		if (D3DXVec3LengthSq(&vLook) <= 100 && D3DXVec3LengthSq(&vLook) >= 0)
		{
			if (m_currentState == NOLL_STATE_NOMAL || m_currentState == NOLL_STATE_WALK)
			{
				D3DXVec3Normalize(&vLook, &vLook);
				float fDot = D3DXVec3Dot(&vLook, &m_vDir);
				if (fDot > -0.95f)
				{
					D3DXVECTOR3 vCross;
					D3DXVec3Cross(&vCross, &vLook, &m_vDir);
					if (vCross.y > 0)
					{
						m_vRot.y += 2.f;
						m_playAniNum = NOLL_ANI_TURN_LEFT;
					}
					else
					{
						m_vRot.y -= 2.f;
						m_playAniNum = NOLL_ANI_TURN_RIGHT;
					}
					m_currentState = NOLL_STATE_WALK;
				}
				else if (m_currentState == NOLL_STATE_NOMAL)
				{
					if (!m_isFight)
					{
						m_isFight = true;
						int rnd = rand() % 100;
						if(rnd > 30)
							m_playAniNum = NOLL_ANI_SMASH_ATTACK;
						else
							m_playAniNum = NOLL_ANI_DOUBLE_ATTACK;
						m_currentState = NOLL_STATE_ATTACK;
					}
				}
				else if(m_currentState == NOLL_STATE_WALK)
				{
					this->CompulsionAnimation();
				}
			}
		}
		else if (D3DXVec3LengthSq(&vLook) <= 5000 && D3DXVec3LengthSq(&vLook) > 100)
		{
			if (m_currentState == NOLL_STATE_NOMAL || m_currentState == NOLL_STATE_WALK || m_currentState == NOLL_STATE_TURN)
			{
				D3DXVec3Normalize(&vLook, &vLook);
				float fDot = D3DXVec3Dot(&vLook, &m_vDir);
				if (fDot > -0.97f)
				{
					D3DXVECTOR3 vCross;
					D3DXVec3Cross(&vCross, &vLook, &m_vDir);
					if (vCross.y > 0)
					{
						m_vRot.y += 1.f;
						if (fDot > -0.5f)
						{
							if (m_currentState == NOLL_STATE_WALK && m_oldState == NOLL_STATE_WALK)
							{
								this->CompulsionAnimation();
							}
							m_currentState = NOLL_STATE_TURN;
							m_playAniNum = NOLL_ANI_TURN_RIGHT;
						}
						else
						{
							m_currentState = NOLL_STATE_WALK;
							m_playAniNum = NOLL_ANI_WALK_FRONT;
						}
					}
					else
					{
						m_vRot.y -= 1.f;
						if (fDot > -0.5f)
						{
							if (m_currentState == NOLL_STATE_WALK && m_oldState == NOLL_STATE_WALK)
							{
								this->CompulsionAnimation();
							}
							m_currentState = NOLL_STATE_TURN;
							m_playAniNum = NOLL_ANI_TURN_LEFT;
						}
						else
						{
							m_currentState = NOLL_STATE_WALK;
							m_playAniNum = NOLL_ANI_WALK_FRONT;
						}
					}
				}
				else
				{
					m_playAniNum = NOLL_ANI_WALK_FRONT;
					m_currentState = NOLL_STATE_WALK;
				}
			}
		}
		else
		{

		}

		if (g_pKeyManager->IsOnceKeyDown('2'))
		{
			m_currentState = NOLL_STATE_HITFLYING;
			m_playAniNum = NOLL_ANI_KNOCK_BACK_START;
		}

		this->ManagedState();
	}

	if (g_pKeyManager->IsOnceKeyDown('P'))
	{
		this->Damaged(1.f, m_pTargetObj, true);
	}
}

void cNoll::RenderCreature()
{
	m_hammer->Render();
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

}


void cNoll::ManagedState()
{
	UpdateTransform();
	if (m_currentState == m_oldState)
	{
		float Rate = m_pMesh->GetTrackRate();
		int nRate = Rate / 1;

		if (fabs(Rate - (0.8f + nRate)) < EPSILON + 0.01f)		// 애니메이션이 끝났다면.
		{
			// 날라가는 모션 2으로 바꿔줌
			if (m_oldState == NOLL_STATE_HITFLYING && m_playAniNum == NOLL_ANI_KNOCK_BACK_START)
			{
				m_playAniNum = NOLL_ANI_KNOCK_BACK_ING;
				this->AnimationToState();
			}
			else if (m_oldState == NOLL_STATE_HITFLYING && m_playAniNum == NOLL_ANI_KNOCK_BACK_ING)		// 날라가는 모션 3으로 바꿔줌
			{
				m_playAniNum = NOLL_ANI_KNOCK_BACK_STAND_UP;
				this->AnimationToState();
			}
			else
			{
				if (m_currentState != NOLL_STATE_WALK)
				{
					m_currentState = m_oldState = NOLL_STATE_NOMAL;
					m_playAniNum = NOLL_ANI_NOMAL;
					this->AnimationToState();
				}
				else
				{
					m_currentState = m_oldState = NOLL_STATE_NOMAL;
					m_playAniNum = NOLL_ANI_NOMAL;
				}
			}
		}
		// workState 면 움직이게.
		if (m_oldState == NOLL_STATE_WALK && m_currentState == NOLL_STATE_WALK)
		{
			if (m_playAniNum == NOLL_ANI_WALK_FRONT)
			{
				m_vPos -= m_vDir * 0.3f;
			}

		}
	}
	else
	{
		if (m_currentState == NOLL_STATE_HIT && m_oldState == NOLL_STATE_HIT)
		{
			this->AnimationToState();
		}
		else if (m_statePriority[(int)m_currentState] < m_statePriority[(int)m_oldState])
		{
			m_oldState = m_currentState;
			this->AnimationToState();
		}
		else
		{
			m_currentState = m_oldState;
		}
	}
	
}

void cNoll::AnimationToState()
{
	m_vecHitAttack.clear();
	switch (m_oldState)
	{
	case NOLL_STATE_NOMAL:
		//g_pSoundManager->play("기본소리", 0.3f);
		m_pMesh->SwitchAnimationBlend(m_playAniNum);
		break;
	case NOLL_STATE_TURN:
		m_pMesh->SwitchAnimationBlend(m_playAniNum);
		break;
	case NOLL_STATE_DIE:
		break;
	case NOLL_STATE_WALK:
		g_pSoundManager->play("기본소리", 0.4f);
		m_pMesh->SwitchAnimationBlend(m_playAniNum);
		break;
	case NOLL_STATE_HIT:
		m_pMesh->SwitchAnimationBlend(m_playAniNum,1.5f, 0.05f);
		break;
	case NOLL_STATE_HITFLYING:
		m_pMesh->SwitchAnimationBlend(m_playAniNum);
		break;
	case NOLL_STATE_ATTACK:
		m_pMesh->SwitchAnimationBlend(m_playAniNum);
		break;
	default:
		break;
	}
}

void cNoll::Damaged(float fDamege, cGameObject * pAttacker, bool isSmash)
{
	g_pSoundManager->play("기본히트", 0.4f);

	if (isSmash)
	{
		m_currentState = NOLL_STATE_HITFLYING;
		m_playAniNum = NOLL_ANI_KNOCK_BACK_START;

		if (m_playAniNum == NOLL_ANI_KNOCK_BACK_START)
		{
			if (m_pTarget->y > EPSILON || m_vPos.y > EPSILON ||
				m_pTarget->y < EPSILON || m_vPos.y < EPSILON)
			{
				int a = 0;	// 여기에 걸리면 뭔가 이상이 있는거임
				DebugBreak;
			}
			D3DXVECTOR3 vTarget = *m_pTarget;
			D3DXVECTOR3 vpos = m_vPos;
			vTarget.y = 0;
			vpos.y = 0;

			SetShiftMove(pAttacker->GetDirection(), fDamege * 0.3f, 0, 0.6f);
		}
	}
	else
	{
		int rnd = rand() % 2;
		m_currentState = NOLL_STATE_HIT;
		if (rnd)
			m_playAniNum = NOLL_ANI_HIT2 + 1;
		else
			m_playAniNum = NOLL_ANI_HIT2;
	}

	this->AnimationToState();


}

D3DXVECTOR3 cNoll::GetDirection()
{
	return -m_vDir;
}

void cNoll::AnimationRateProcessLocal(float fAniRate)
{
	m_hammer->Update();
}


void cNoll::CircleAttackDilay()
{
	if (m_isFight)
	{
		m_attackDilay += g_pTimeManager->GetDeltaTime();
		if (m_attackDilay >= 5.f)
		{
			m_attackDilay = 0.f;
			m_isFight = false;
		}
	}
	else
	{
		m_attackDilay = 0.f;
	}
}

void cNoll::CompulsionAnimation()
{
	m_currentState = m_oldState = NOLL_STATE_NOMAL;
	m_playAniNum = NOLL_ANI_NOMAL;
	//this->AnimationToState();
}

void cNoll::NollShiftMoveUpdate()
{
	if (m_playAniNum == NOLL_ANI_SMASH_ATTACK)
	{
		if (fabs(m_pMesh->GetTrackRate() - 0.f) < EPSILON + 0.02f)
		{
			m_vecHitList.clear();
			//ShiftMove(m_vDir, 0.2f, 0.5f);
			SetShiftMove(-m_vDir, 30.f, 1.2f, 1.8f);
			SetEnableHitAttack(0, 10.f, false, 0.3f, 0.5f);
		}
	}
	else if (m_playAniNum == NOLL_ANI_DOUBLE_ATTACK)
	{
		if (fabs(m_pMesh->GetTrackRate() - 0.0f) < EPSILON + 0.02f)
		{
			m_vecHitList.clear();
			//ShiftMove(m_vDir, 0.2f, 0.5f);
			SetShiftMove(-m_vDir, 30.f, 0.7f, 1.2f);
			SetEnableHitAttack(0, 10.f, true, 0.3f, 0.9f);
		}
	}

}

void cNoll::Slicing()
{
}
