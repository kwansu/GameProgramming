#include "stdafx.h"
#include "cLavasat.h"
using namespace ns_Lavasat;

cLavasat::cLavasat()
	: m_isStomp(false)
{
	m_fMoveRadius = 47;
	m_fAttackRange = 50;
	m_fDetectionRange = 500;
}


cLavasat::~cLavasat()
{
}

void cLavasat::SetupCreature()
{
	m_pMesh = new cSkinnedMesh;

	m_pMesh->Load("./3dObject/Lavasat/", "lavasat_ani28.X", m_stBoundingSphere);
	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, 0.16f, 0.16f, 0.16f);

	D3DXMATRIXA16 matR;
	D3DXMatrixRotationY(&matR, D3DXToRadian(180));
	SetOriginMatrix(matS * matR);

	LoadHitBox("./GameData/lavasat.txt", matS);


	matCollision[0] = m_mapHitBox["ValveBiped_Bip01_L_Hand"];
	matCollision[1] = m_mapHitBox["ValveBiped_Bip01_R_Hand"];
	matCollision[2] = m_mapHitBox["ValveBiped_Bip01_L_Foot"];
	matCollision[3] = m_mapHitBox["ValveBiped_Bip01_R_Foot"];


	m_stFireBall.stAttackBox.vHalfSize = D3DXVECTOR3(3, 3, 3);

	m_nHp = 30000;
	m_nDamaged = 9;


	g_pSoundManager->addSound("기본소리", "./3dObject/Sound/lavast/lavasat_breath_01.wav", false, false);
	g_pSoundManager->addSound("죽음", "./3dObject/Sound/lavast/lavasat_dying_boss_01.wav", false, false);
	g_pSoundManager->addSound("데미지뒤", "./3dObject/Sound/lavast/lavasat_hurt_01.wav", false, false);
	g_pSoundManager->addSound("데미지바닥", "./3dObject/Sound/lavast/lavasat_hurt_02.wav", false, false);
	g_pSoundManager->addSound("데미지양쪽", "./3dObject/Sound/lavast/lavasat_hurt_03.wav", false, false);
	g_pSoundManager->addSound("헤롱헤롱", "./3dObject/Sound/lavast/lavasat_low_health_01.wav", false, false);
	g_pSoundManager->addSound("기절중", "./3dObject/Sound/lavast/lavasat_voice_04.wav", false, false);
	g_pSoundManager->addSound("점프", "./3dObject/Sound/lavast/lavasat_motion_04.wav", false, false);

}

void cLavasat::UpdateCreature()
{
	UpdateTransform();
	if (IsFindTarget(m_vToTargetDir, m_fDist))
	{
		m_fDistAngle = BetweenCosAngleFromTarget(m_vToTargetDir, m_isClock);
		m_fDistAngle = D3DXToDegree(acos(m_fDistAngle));
		//
		if (m_eActState == ACTION_COMMAND)
			AICommand();
	}

	float fAngle = m_fTurnSpeed * g_fDeltaTime;
	if (m_isActiveTurn && m_fDistAngle > fAngle)
	{
		fAngle = (m_isClock ? -fAngle : fAngle);
		m_vRot.y += fAngle;
		UpdateDirection();
	}


	if (m_stFireBall.isActive)
	{
		m_stFireBall.Update();
		g_pWorld->ProcessAttackCollision(m_stFireBall.stAttackBox, this, 400, true, m_vecHitList);
	}

	if (m_isRun)
		m_vPos += m_vDir * fRUN_SPEED * g_fDeltaTime;

	if (g_pKeyManager->IsOnceKeyDown('N'))
	{
		m_nAniCurrentState = 브레스;	}

	if (g_pKeyManager->IsOnceKeyDown('M'))
	{
	m_nAniCurrentState = 시네마틱1;	}
	if (g_pKeyManager->IsOnceKeyDown('K'))
	{
		g_pSoundManager->play("죽음", 0.4f);
		m_nAniCurrentState = 죽는동작;
	}
	this->Effect();
}

void cLavasat::RenderCreature()
{
	if (m_stFireBall.isActive)
	{
		g_pCollisionRender->RenderBox(m_stFireBall.stAttackBox);
	}
}

void cLavasat::AniSituation()
{
	SetReserveAnimation(대기);
	m_isActiveTurn = false;
	m_isRun = false;
	
	switch (m_nAniCurrentState)
	{
	case 대기:
		g_pSoundManager->play("기본소리", 0.4f);
		m_eActState = ACTION_COMMAND;
		m_isEnableReserve = false;
		break;
	case 왼쪽점프:
		g_pSoundManager->play("점프", 0.4f);
		SetShiftMove(-m_vRight, 250.f, 0.38f, 0.71f);
		break;
	case 오른쪽점프:
		g_pSoundManager->play("점프", 0.4f);
		SetShiftMove(m_vRight, 250.f, 0.38f, 0.71f);
		break;
	case 뒷점프:
		g_pSoundManager->play("점프", 0.4f);
		SetShiftMove(-m_vDir, 300.f, 0.44f, 0.71f);
		SetEnableHitAttack(3, 200, true, 0.64f, 0.7f);
		SetEnableHitAttack(8, 200, true, 0.64f, 0.7f);
		SetEnableHitAttack(5, 200, true, 0.64f, 0.7f);
		SetEnableHitAttack(10, 200, true, 0.64f, 0.7f);
		break;
	case 짧은돌진:
		SetShiftMove(m_vDir, 700.f, 0.48f, 0.77f);
		AllAttackBoxEnable(500, false, 0.55f, 0.73f);
		m_fTurnSpeed = TRACE_ANGLE_SPEED;
		m_isActiveTurn = true;
		break;
	case 오른손불꽃싸다구:
		SetShiftMove(m_vDir, 80.f, 0.22f, 0.38f);
		SetEnableHitAttack(10, 300, false, 0.26f, 0.37f);
		SetEnableHitAttack(9, 300, false, 0.30f, 0.37f);
		m_fTurnSpeed = TRACE_ANGLE_SPEED;
		m_isActiveTurn = true;
		break;
	case 왼손불꽃싸다구:
		SetShiftMove(m_vDir, 80.f, 0.22f, 0.38f);
		SetEnableHitAttack(5, 300, false, 0.26f, 0.37f);
		SetEnableHitAttack(4, 300, false, 0.30f, 0.37f);
		m_fTurnSpeed = TRACE_ANGLE_SPEED;
		m_isActiveTurn = true;
		break;
	case 스톰프:
		SetEnableHitAttack(0, 450, true, 0.45f, 0.48f, 3);
		break;
	case 왼쪽돌기 : case 오른쪽돌기:
		m_fTurnSpeed = fTURN_SPEED;
		m_isActiveTurn = true;

		break;
	case 올려치기:
		AllAttackBoxEnable(600, true, 0.42f, 0.6f);
		SetEnableHitAttack(1, 900, false, 0.61f, 0.635f);
		m_fTurnSpeed = TRACE_ANGLE_SPEED;
		m_isActiveTurn = true;
		break;
	case 로데오:
		AllAttackBoxEnable(600, true, 0.4f, 0.74f);
		m_fTurnSpeed = 20;
		m_isActiveTurn = true;
		m_nAttackCombo = 0;
		break;
	case 로데오회전:
		m_nAttackCombo = 0;
		AllAttackBoxEnable(600, true, 0.28f, 0.83f);
		break;
	case 브레스:
		m_nAttackCombo = 0;
		break;
	case 쓰러짐:
		g_pSoundManager->play("헤롱헤롱", 0.4f);
		SetReserveAnimation(쓰러진상태);
		m_nDownCount = 180;
		if (m_nAniPrevIndexState == 죽는동작)
		{
			m_nDownCount = 99999;
		}
		else
		{
			m_nDownCount = 120;
		}
		break;
	case 쓰러진상태:
		g_pSoundManager->play("기절중", 0.4f);
		m_isEnableReserve = false;
		break;
	case 죽는동작:
		g_pSoundManager->play("죽음", 0.4f);
		SetReserveAnimation(쓰러짐);
		break;
	}
}

void cLavasat::AnimationRateProcessLocal(float fAniRate)
{
	switch (m_nAniCurrentState)
	{
	case 올려치기:
		if (fAniRate > 0.625f)
		{
			m_isRun = false;
			m_isActiveTurn = false;
		}
		else if(fAniRate > 0.4f)
			m_isRun = true;
		break;

	case 짧은돌진:
		m_stShiftMove.vShiftDir = -m_vDir;
		if (fAniRate > 0.78f)
			m_isActiveTurn = false;
		break;
		
	case 로데오:
		ActionRodeo(fAniRate);
		break;

	case 로데오회전:
		ActionRodeoTurn(fAniRate);
		break;

	case 브레스:
		if (fAniRate > 0.65f && m_nAttackCombo == 0)
		{
			ActionFireBall();
			++m_nAttackCombo;
		}
		break;

	case 쓰러진상태:
		if (--m_nDownCount < 0)
		{
			m_nAniCurrentState = 일어섬;
		}
		break;
	}
}

void cLavasat::AICommand()
{
	m_eActState = ACTION_ATTACK;

	if (m_fDistAngle > fATTACK_MAX_ANGLE)
	{
		if (m_fDist < fAVOID_MAX_DISTANCE && s_pTarget->IsAttacking())
		{
			int r = rand() % 20;

			if (r > 16)
			{
				m_nAniCurrentState = 로데오회전;
				m_fAniSpeed = 1.2f;
			}
			else if (r > 13)
			{
				m_nAniCurrentState = 스톰프;
				return;
			}
			else if (r > 7)
			{
				ActionAvoid();
				return;
			}
		}

		if (m_fDistAngle > fTURN_MAX_ANGLE)
			m_nAniCurrentState = m_isClock ? 왼쪽돌기 : 오른쪽돌기;
		else
		{
			m_isActiveTurn = true;
			m_fTurnSpeed = fTURN_SPEED;
			m_eActState = ACTION_COMMAND;
		}
	}
	else if (m_fDist > fSWOOP_MAX_DISTANCE)
	{
		// 일반 공격 범위 밖, 로데오 가능
		m_nAniCurrentState = 로데오;
		m_fAniSpeed = 1.2f;
	}
	else if (m_fDist > fSHORT_RUSH_DISTANCE)
	{
		// 올려치기, 잛은 돌진 가능 거리
		int r = rand() % 10;

		if (r > 7)
		{
			m_nAniCurrentState = 로데오;
			m_fAniSpeed = 1.2f;
		}
		else
			m_nAniCurrentState = 올려치기;
	}
	else if (m_fDist > m_fAttackRange)
	{
		int r = rand() % 10;

		if (r > 7)
		{
			m_nAniCurrentState = 로데오;
			m_fAniSpeed = 1.2f;
		}
		else if (r > 5)
		{
			m_nAniCurrentState = 로데오회전;
			m_fAniSpeed = 1.2f;
		}
		else
			m_nAniCurrentState = 짧은돌진;
	}
	else
	{
		// 일반 공격 가능 범위
		int r = rand() % 20;

		if (r > 16)
		{
			m_nAniCurrentState = 로데오회전;
			m_fAniSpeed = 1.2f;
		}
		else if (r > 13)
			m_nAniCurrentState = 스톰프;
		else
			m_nAniCurrentState = m_isClock ? 왼손불꽃싸다구 : 오른손불꽃싸다구;
	}
}

void cLavasat::ActionAvoid()
{
	//float fAttackCos = D3DXVec3Dot(&m_vToTargetDir, &s_pTarget->GetDirection());

	//if (fAttackCos > 0)
	//	return false;
	m_fAniSpeed = 1.3f;

	if (m_fDistAngle > 120)
		m_nAniCurrentState = 뒷점프;
	else if (m_isClock)
		m_nAniCurrentState = 오른쪽점프;
	else
		m_nAniCurrentState = 왼쪽점프;

	return;
}

void cLavasat::ActionFireBall()
{
	m_stFireBall.isActive = true;
	m_stFireBall.fActiveTime = 3.f;
	
	// 위치 방향 설정.
	m_stFireBall.matWorld = *m_vecAttackBox[1].pmatSticking;
	m_stFireBall.matWorld._41 += m_vDir.x * 2;
	m_stFireBall.matWorld._42 -= 2;
	m_stFireBall.matWorld._43 += m_vDir.z * 2;

	D3DXVec3TransformNormal(&m_stFireBall.vDir, &D3DXVECTOR3(0, 0, 1), &m_stFireBall.matWorld);
	D3DXVec3Normalize(&m_stFireBall.vDir, &m_stFireBall.vDir);

	g_pEffectManager->CreateFireBallEgg(3, &m_stFireBall.vPos, 2.f);

}

void cLavasat::ActionRodeo(float fAniRate)
{
	if (m_nAttackCombo == 0)
	{
		D3DXVECTOR3 vDir = m_vDir - m_vRight * 0.4f;
		D3DXVec3Normalize(&vDir, &vDir);
		SetShiftMove(vDir, 2000, 0.41f, 0.48f);
		++m_nAttackCombo;
	}
	else if(m_nAttackCombo == 1 && fAniRate >= 0.48f)
	{
		D3DXVECTOR3 vDir = m_vDir + m_vRight;
		D3DXVec3Normalize(&vDir, &vDir);
		SetShiftMove(vDir, 2000, 0.53f, 0.6f);
		++m_nAttackCombo;
	}
	else if (m_nAttackCombo == 2 && fAniRate >= 0.6f)
	{
		D3DXVECTOR3 vDir = m_vDir - m_vRight;
		D3DXVec3Normalize(&vDir, &vDir);
		SetShiftMove(vDir, 2000, 0.63f, 0.72f);
		++m_nAttackCombo;
		m_isActiveTurn = false;
	}
}

void cLavasat::ActionRodeoTurn(float fAniRate)
{
	if (m_nAttackCombo == 0)
	{
		D3DXVECTOR3 vDir = m_vDir - m_vRight * 0.7f;
		D3DXVec3Normalize(&vDir, &vDir);
		SetShiftMove(vDir, 2000, 0.28f, 0.33f);
		++m_nAttackCombo;
	}
	else if (m_nAttackCombo == 1 && fAniRate > 0.33f)
	{
		SetShiftMove(m_vRight, 2000, 0.375, 0.45f);
		++m_nAttackCombo;
	}
	else if (m_nAttackCombo == 2 && fAniRate < 0.45f)
	{
		m_stShiftMove.vShiftDir += m_vDir * 0.008f;
		D3DXVec3Normalize(&m_stShiftMove.vShiftDir, &m_stShiftMove.vShiftDir);
	}
	else if (m_nAttackCombo == 2)
	{
		D3DXVECTOR3 vDir = m_vDir - m_vRight;
		D3DXVec3Normalize(&vDir, &vDir);
		SetShiftMove(vDir, 2000, 0.465f, 0.535f);
		++m_nAttackCombo;
	}
	else if (m_nAttackCombo == 3 && fAniRate < 0.533f)
	{
		m_stShiftMove.vShiftDir -= m_vDir * 0.004f;
		D3DXVec3Normalize(&m_stShiftMove.vShiftDir, &m_stShiftMove.vShiftDir);
	}
	else if (m_nAttackCombo == 3)
	{
		D3DXVECTOR3 vDir = m_vRight;
		D3DXVec3Normalize(&vDir, &vDir);
		SetShiftMove(vDir, 2000, 0.567f, 0.638f);
		++m_nAttackCombo;
	}
	else if (m_nAttackCombo == 4 && fAniRate < 0.64f)
	{
		m_stShiftMove.vShiftDir += m_vDir * 0.008f;
		D3DXVec3Normalize(&m_stShiftMove.vShiftDir, &m_stShiftMove.vShiftDir);
	}
	else if (m_nAttackCombo == 4)
	{
		D3DXVECTOR3 vDir = -m_vRight;
		D3DXVec3Normalize(&vDir, &vDir);
		SetShiftMove(vDir, 2000, 0.67f, 0.725f);
		++m_nAttackCombo;
	}
	else if (m_nAttackCombo == 5 && fAniRate < 0.73)
	{
		m_stShiftMove.vShiftDir -= m_vDir * 0.004f;
		D3DXVec3Normalize(&m_stShiftMove.vShiftDir, &m_stShiftMove.vShiftDir);
	}
	else if (m_nAttackCombo == 5)
	{
		D3DXVECTOR3 vDir = m_vRight;
		D3DXVec3Normalize(&vDir, &vDir);
		SetShiftMove(vDir, 2000, 0.766f, 0.85f);
		++m_nAttackCombo;
	}
	else if (m_nAttackCombo == 6 && fAniRate < 0.85f)
	{
		m_stShiftMove.vShiftDir += m_vDir * 0.008f;
		D3DXVec3Normalize(&m_stShiftMove.vShiftDir, &m_stShiftMove.vShiftDir);
	}
}

void cLavasat::Damaged(float fDamege, cGameObject * pAttacker, bool isSmash)
{
	m_nHp -= fDamege;

	if (isSmash)
	{
		if (m_nHp / 3000 <= m_nDamaged)
		{
			--m_nDamaged;
			if (m_nDamaged % 3 == 0)
			{
				m_nAniCurrentState = 쓰러짐;
				m_fAniSpeed = 0.9f;
			}
			else
			{
				if (m_fDistAngle < 45)
				{
					g_pSoundManager->play("데미지뒤", 0.4f);
					m_nAniCurrentState = 데미지_뒤;
				}
					
				else if (m_fDistAngle > 135)
				{
					g_pSoundManager->play("데미지바닥", 0.4f);
					m_nAniCurrentState = 데미지_바닥;
				}
					
				else if (m_isClock)
				{
					g_pSoundManager->play("데미지양쪽", 0.4f);
					m_nAniCurrentState = 데미지_오른쪽;
				}
					
				else
				{
					g_pSoundManager->play("데미지양쪽", 0.4f);
					m_nAniCurrentState = 데미지_왼쪽;
				}
			}
		}
	}
}

void cLavasat::AllAttackBoxEnable(float fDamage, bool isSmash, float fStartRate, float fEndRate)
{
	for (int i = 0; i < 11; ++i)
	{
		SetEnableHitAttack(i, fDamage, isSmash, fStartRate, fEndRate);
	}
}

void cLavasat::Effect()
{
	/*0	ValveBiped_Bip01				몸뒤
	1	ValveBiped_Bip01_Head1			머리
	2	ValveBiped_Bip01_L_Calf			뒷다리위
	3	ValveBiped_Bip01_L_Foot			뒷다리
	4	ValveBiped_Bip01_L_Forearm		앞다리위
	5	ValveBiped_Bip01_L_Hand			앞다리
	6	ValveBiped_Bip01_Neck			목(몸 앞쪽)
	7	ValveBiped_Bip01_R_Calf
	8	ValveBiped_Bip01_R_Foot
	9	ValveBiped_Bip01_R_Forearm
	10	ValveBiped_Bip01_R_Hand*/


	/*
		대기,							  뒷점프,
	왼쪽돌기,							죽는동작,
	오른쪽돌기,						   피없어아파하기,
	왼쪽점프,							쓰러짐,
	오른쪽점프,						   쓰러진상태,
	포효,								  일어섬,
	짧은돌진,							데미지_뒤,
	달리는중,							데미지_바닥,
	왼손불꽃싸다구,					 데미지_왼쪽,
	오른손불꽃싸다구,					데미지_오른쪽,
	올려치기,							돌진시작,
	내려치기,							돌진중,
	스톰프,							 브레스,
	로데오,							 뒷점프브레스,
	로데오회전,
	*/
	if ( m_nAniCurrentState != 대기 && m_nAniCurrentState != 죽는동작 &&
		m_nAniCurrentState != 쓰러진상태)
	{
		if (int(m_pMesh->GetTrackRate() * 100) % 5 == 0)
		{
			D3DXMATRIXA16 matPos = *matCollision[0].pmatSticking;
			D3DXVECTOR3 tempVec = { 0, -5, 10 };

			D3DXVec3TransformCoord(&tempVec, &tempVec, &matPos);
			g_pEffectManager->CreateDust(tempVec, 1, { 0.2f, 0.2f, 0.2f }, 5.f);

			matPos = *matCollision[1].pmatSticking;
			tempVec = { 0, -5, 10 };

			D3DXVec3TransformCoord(&tempVec, &tempVec, &matPos);
			g_pEffectManager->CreateDust(tempVec, 1, { 0.2f, 0.2f, 0.2f }, 5.f);

			matPos = *matCollision[2].pmatSticking;
			tempVec = { 0, -5, 10 };

			D3DXVec3TransformCoord(&tempVec, &tempVec, &matPos);
			g_pEffectManager->CreateDust(tempVec, 1, { 0.2f, 0.2f, 0.2f }, 5.f);

			matPos = *matCollision[3].pmatSticking;
			tempVec = { 0, -5, 10 };


			D3DXVec3TransformCoord(&tempVec, &tempVec, &matPos);
			g_pEffectManager->CreateDust(tempVec, 1, { 0.2f, 0.2f, 0.2f }, 5.f);
		}
	}

	if (m_nAniCurrentState == 스톰프)
	{
		if (!m_isStomp &&int( m_pMesh->GetTrackRate() * 100) >= 70)
		{
			D3DXVECTOR3 tempVec = { 0, 0, 10 };

			D3DXMATRIXA16 matR;
			cout << " 호출 " << endl;
			for (int i = 0; i < 36; ++i)
			{
				D3DXMatrixIdentity(&matR);
				D3DXMatrixRotationY(&matR, D3DXToRadian(i * 10));
				D3DXMATRIXA16 matPos = matR * m_matWorld;
				D3DXVec3TransformCoord(&tempVec, &tempVec, &matPos);


				g_pEffectManager->CreateDust(tempVec, 1, { 0.6f, 0.6f, 0.6f }, 5.f);
			}
			m_isStomp = true;
		}
	}
	else
		m_isStomp = false;
}
