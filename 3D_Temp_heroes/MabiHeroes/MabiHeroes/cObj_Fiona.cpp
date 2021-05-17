#include "stdafx.h"
#include "cObj_Fiona.h"
#include "cCreature.h"
#include "cWearItem.h"
#include "cProgressBar.h"
#include "cQuickSlot.h"
#include "cEquipment.h"

cObj_Fiona::cObj_Fiona()
	: m_nCurrentAnim(0)
	, m_pmatSword(NULL)
	, m_nAniCount(0)
	, m_nCounterCount(0)
	, m_isAttacking(false)
	, m_isRun(false)
	, m_isNextShiftMove(0)
	, m_NextShiftMoveTime(0.f)
	, m_isSprint(false)
	, m_pProgressBar(NULL)
	, m_isRightTurn(false)
	, m_fKeyAngle(0)
	, m_fSecTime(0)
	, m_pQuickSlot(NULL)
	, m_nSlicingCount(0)
	, m_fFallingTime(0)
	, m_pEquipment(NULL)
	, m_isSound(false)
{
	m_vDir = D3DXVECTOR3(-1, 0, 0);
	m_fMoveHeight = 15;
}


cObj_Fiona::~cObj_Fiona()
{
}

void cObj_Fiona::SetupCreature()
{
	m_pProgressBar = new cProgressBar;
	m_pProgressBar->Setup();

	m_nHp = MAX_HP;
	m_nStamina = MAX_STAMINA;

	m_pProgressBar->SetHp(&m_nHp);
	m_pProgressBar->SetStamina(&m_nStamina);

	m_pQuickSlot = new cQuickSlot;
	m_pQuickSlot->Setup();

	m_pEquipment = new cEquipment;
	m_pEquipment->Setup();
	m_pEquipment->SetFiona(this);

	if (!m_pMesh)
	{
		m_pMesh = new cSkinnedMesh;
		//m_pMesh->Load("./3dObject/Fiona/", "fiona.X", m_stBoundingSphere);
		//m_pMesh->Load("./3dObject/Fiona_new/", "fiona_new1.X", m_stBoundingSphere);
		m_pMesh->Load("./3dObject/Fiona_new/", "fiona_plate_all.X", m_stBoundingSphere);

		m_pMesh_paladin = new cSkinnedMesh;
		m_pMesh_paladin->Load("./3dObject/paladin/", "paladin.X", m_stBoundingSphere);

		m_pMesh_Shoe = new cSkinnedMesh;
		m_pMesh_Shoe->Load("./3dObject/Fiona_new/", "fiona_new1.X", m_stBoundingSphere);

		m_pMesh_Dress = new cSkinnedMesh;
		m_pMesh_Dress->Load("./3dObject/Fiona_new/", "fiona_dress.X", m_stBoundingSphere);
	}

	cWearItem* m_pSword = new cWearItem;
	m_pmatSword = m_pMesh->SearchMat("ValveBiped_Anim_Attachment_RH");
	m_pSword->Setup("sword.x", m_pmatSword);
	m_vecWearItem.push_back(m_pSword);

	cWearItem* m_pShield = new cWearItem;
	m_pmatSshield = m_pMesh->SearchMat("ValveBiped_Bip01_L_Forearm");
	m_pShield->Setup("shield.x", m_pmatSshield);
	m_vecWearItem.push_back(m_pShield);

	//팔라딘 무기, 방패
	cWearItem* m_pPaladinSword = new cWearItem;
	//m_pPaladinSword->SetPosition(100, 100, 100);
	m_pmatSword = m_pMesh_paladin->SearchMat("ValveBiped_Anim_Attachment_RH");
	m_pPaladinSword->Setup("paladin_sword.x", m_pmatSword);
	m_vecWearItem.push_back(m_pPaladinSword);

	cWearItem* m_pPaladinShield = new cWearItem;
	//m_pPaladinShield->SetPosition(100, 100, 100);
	m_pmatSword = m_pMesh_paladin->SearchMat("ValveBiped_Bip01_L_Forearm");
	m_pPaladinShield->Setup("paladin_shield.x", m_pmatSword);
	m_vecWearItem.push_back(m_pPaladinShield);

	D3DXMATRIXA16 mat1;
	D3DXMatrixTranslation(&mat1, 99999, 99999, 99999);
	m_pMesh_paladin->Update(mat1);

	//SetScale(0.2f, 0.2f, 0.2f);
	D3DXMATRIXA16 matOrigin;
	D3DXMatrixScaling(&matOrigin, 0.2f, 0.2f, 0.2f);
	D3DXMATRIXA16 matR;
	D3DXMatrixRotationY(&matR, D3DXToRadian(90));
	SetOriginMatrix(matOrigin * matR);

	m_nAniCurrentState = STANDING_IDLE;
	m_pMesh->SwitchAnimationBlend(STANDING_IDLE);

	LoadHitBox("./GameData/fiona.txt", matOrigin);

	g_pSoundManager->addSound("공1", "./3dObject/Sound/fiona_attack4.wav", false, false);
	g_pSoundManager->addSound("공2", "./3dObject/Sound/Swing_Metal.wav", false, false);
	g_pSoundManager->addSound("강공", "./3dObject/Sound/fiona_strongattack2.wav", false, false);
	g_pSoundManager->addSound("강공2", "./3dObject/Sound/Swing_MetalStrong.wav", false, false);
	g_pSoundManager->addSound("방공", "./3dObject/Sound/Swing_Shield.wav", false, false);
	g_pSoundManager->addSound("스태미너오링", "./3dObject/Sound/fiona_lack_stamina.wav", false, false);
	g_pSoundManager->addSound("발소리", "./3dObject/Sound/walk_01.wav", false, false);
	g_pSoundManager->addSound("피격", "./3dObject/Sound/hit_common_blunt_adult2.wav", false, false);
	g_pSoundManager->addSound("드링크포션", "./3dObject/Sound/action_drink_potion.wav", false, false);
	g_pSoundManager->addSound("가드", "./3dObject/Sound/action_guard_begin.wav", false, false);
	g_pSoundManager->addSound("가드방어", "./3dObject/Sound/Action_Guard_Success.wav", false, false);
	g_pSoundManager->addSound("높은착지", "./3dObject/Sound/action_landing_higher.wav", false, false);
	g_pSoundManager->addSound("낮은착지", "./3dObject/Sound/action_landing_lower.wav", false, false);
	g_pSoundManager->addSound("스프린트끝", "./3dObject/Sound/action_sprint_end.wav", false, false);
	g_pSoundManager->addSound("카운터어택", "./3dObject/Sound/Skill_CounterAttack.wav", false, false);
	g_pSoundManager->addSound("팔라딘변신", "./3dObject/Sound/paladin2_transform_holysound.wav", false, false);
	g_pSoundManager->addSound("가드슬립", "./3dObject/Sound/action_guard_slip.wav", false, false);
	g_pSoundManager->addSound("구르기", "./3dObject/Sound/action_motion_dwyn_03.wav", false, false);
	g_pSoundManager->addSound("4스매시발차기", "./3dObject/Sound/Swing_Kick.wav", false, false);
	g_pSoundManager->addSound("3스매시발차기", "./3dObject/Sound/swing_lv5.wav", false, false);

}

void cObj_Fiona::UpdateCreature()
{
	m_pEquipment->Update();

	if (m_vVelocity.y <= -2)
	{
		m_fFallingTime += g_fDeltaTime;
		m_nAniCurrentState = FALLING;
	}
	else if (m_nAniCurrentState == FALLING)
	{
		m_fFallingTime = 0;
		if(m_fFallingTime > 1.5f)
			m_nAniCurrentState = FALLING_DAMAGE;
		else
			m_nAniCurrentState = FALLING_SAFE;
	}
	else
		Controller();



	if (g_pInput->IsKeyDown('1'))
	{
		m_pMesh->SwitchAnimationBlend(22);
	}

	if (g_pInput->IsKeyDown('2'))
	{
		m_nAniCurrentState = FALLING;
	}
	if (g_pInput->IsKeyDown('3'))
	{
		m_nAniCurrentState = POTION_BEGIN;
		m_nHp += 50;
	}
	if (g_pInput->IsKeyDown('4'))
	{
		m_nAniCurrentState = FALLING_SAFE;
	}
	if (g_pInput->IsKeyDown('5'))
	{
		m_nAniCurrentState = FALLING_DAMAGE;
	}
	if (g_pInput->IsKeyDown('6'))
	{
		m_nAniCurrentState = COMBO4_SMASH;
	}

	m_fSecTime += g_fDeltaTime;

	if (m_nAniCurrentState == STANDING_IDLE || m_nAniCurrentState == RUNNING_LOWER || m_eCharState == TIRED)
	{
		if (m_nStamina < MAX_STAMINA)
		{
			if (m_fSecTime < 1.5f)
			{
				m_nStamina += g_fDeltaTime * 99;
			}
			else
			{
				m_nStamina += g_fDeltaTime * 280;
			}
		}
		else if (m_nStamina > MAX_STAMINA)
		{
			m_nStamina = MAX_STAMINA;
		}
	}
	if (m_nStamina <= 0)
	{
		SetReserveAnimation(TIRED_BEGIN);
		m_nStamina = 0;
	}
	else if (m_eCharState == TIRED)
	{
		if (m_nStamina > 100)
		{
			m_eCharState = IDLE;
		}
	}


	if (m_nHp <= 0)
	{
		m_nHp = 0;
	}
	
	m_pProgressBar->Update();

	if(m_vVelocity.y > -2)
		m_vVelocity.y -= 1.f;

	UpdateTransform();
	this->Effect();
}

void cObj_Fiona::AttackStart()
{
	m_nAniCount = 0;

	if (g_pKeyManager->IsOnceKeyDown(VK_LBUTTON))
	{
		m_nAniCurrentState = ATTACK_COMBO1;
		m_fAniSpeed = 1.55f;
	}
	if (m_eCharState != TIRED)
	{
		if (g_pKeyManager->IsOnceKeyDown(VK_RBUTTON))
		{
			m_nStamina -= STAMINA_CONSUME;
			m_nAniCurrentState = GUARD_ATTACK;

			if (m_eCharState == SPRINT)
			{
				m_nAniCurrentState = DASH_ATTACK;
			}
		}
	}


	////////////////////스킬
	if (g_pKeyManager->IsOnceKeyDown('F'))
	{
		m_nAniCurrentState = SP_SHIELD_ASSAULT;
		m_fAniSpeed = 1.3f;
	}
	if (g_pKeyManager->IsOnceKeyDown('Z'))
	{
		m_nAniCurrentState = PALADIN_TRANSFORM;
		PaladinTransform();
	}
}

void cObj_Fiona::KeyManager()
{
	m_isRun = false;
	//float fRightY = g_pCamera->GetRotYdir().y + 90;
	D3DXVECTOR3	vKeyDir(0, 0, 0);	//float fCosn = 0;

	D3DXVECTOR3 vCamDir;
	vCamDir = g_pCamera->GetDirection();
	vCamDir.y = 0;
	D3DXVec3Normalize(&vCamDir, &vCamDir);

	if (g_pKeyManager->IsStayKeyDown('W'))
	{
		vKeyDir += vCamDir;
		m_isRun = true;
		//m_nAniCurrentState = RUNNING_LOWER;
	}
	

	if (g_pKeyManager->IsStayKeyDown('S'))
	{
		vKeyDir += -vCamDir;
		m_isRun = true;
		//m_nAniCurrentState = RUNNING_LOWER;
	}

	if (g_pKeyManager->IsStayKeyDown('A'))
	{
		vKeyDir += -g_pCamera->GetRightDir();
		m_isRun = true;
		//m_nAniCurrentState = RUNNING_LOWER;
	}

	if (g_pKeyManager->IsStayKeyDown('D'))
	{
		vKeyDir += +g_pCamera->GetRightDir();
		m_isRun = true;
		//m_nAniCurrentState = RUNNING_LOWER;
	}

	D3DXVec3Normalize(&vKeyDir, &vKeyDir);

	//캐릭터 이동 각 구하기
	m_fKeyAngle = D3DXVec3Dot(&vKeyDir, &m_vDir);

	m_fKeyAngle = acos(m_fKeyAngle);
	m_fKeyAngle = D3DXToDegree(m_fKeyAngle);

	D3DXVec3Cross(&vKeyDir, &vKeyDir, &m_vDir);

	if (vKeyDir.y > 0)
	{
		m_isRightTurn = false;
	}
	else
	{
		m_isRightTurn = true;
	}
		
}

void cObj_Fiona::Controller()
{
	//m_fKeyAngle = 0;

	KeyManager();

	m_vVelocity.x = 0;
	m_vVelocity.z = 0;

	if (m_eCharState == HIT_DAMEGED)
	{
		return;
	}
	else if (m_eCharState == FALLDOWN)
	{
		return;
	}
	else if (m_eCharState == POTION_DRINK)
	{
		return;
	}
	else if (m_eCharState == DOWN)
	{
		if (m_isRun)
		{
			m_vRot.y += m_isRightTurn ? m_fKeyAngle : -m_fKeyAngle;
			UpdateRotation();
			UpdateDirection();

			m_nAniCurrentState = DOWN_BACK_ROLL;
		}
	}
	else if (m_eCharState == ROLL_DASH)
	{
		return;
	}
	else if (m_eCharState == ATTACK)
	{
		return;
	}
	else if (m_eCharState == GUARD)
	{
		//AttackStart();

		if (g_pInput->IsKeyUp(VK_SPACE))
		{
			if (m_nAniCurrentState == GUARD_HIT || m_nAniCurrentState == DOWN_BACKWARD)
			{
				g_pCamera->SetCamComeBack();
				SetReserveAnimation(STANDING_IDLE);
			}
			else
			{
				g_pCamera->SetCamComeBack();
				m_nAniCurrentState = STANDING_IDLE;
			}
			
		}
	}
	else	///////////////캐릭터 이동 전체 제어///////////////
	{
		if (m_isRun)
		{
			if (m_eCharState != TIRED)
			{
				m_nAniCurrentState = RUNNING_LOWER;
			}
			else
			{
				m_nAniCurrentState = TIRED_RUN;
			}
			
			if (m_fKeyAngle < ROTATE_SPEED * g_fDeltaTime)
			{
				m_vRot.y += m_isRightTurn ? m_fKeyAngle : -m_fKeyAngle;
				//m_vDir = m_vKeyDir;
			}
			else
			{
				m_vRot.y += (m_isRightTurn ? ROTATE_SPEED : -ROTATE_SPEED) * g_fDeltaTime;
			}

			UpdateRotation();
			UpdateDirection();

			//대쉬 달리기
			if (g_pKeyManager->IsStayKeyDown(VK_LSHIFT))
			{
				m_fSecTime = 0;

				if (m_eCharState != TIRED)
				{
					m_nAniCurrentState = RUNNING_SPRINT;
				}
				else
				{
					m_nAniCurrentState = TIRED_RUN;
				}

				if (m_fKeyAngle < 50)
				{
					if (m_nAniCurrentState == RUNNING_SPRINT)
					{
						m_vVelocity = m_vDir * SPRINT_SPEED * g_fDeltaTime;
					}
					if (m_nAniCurrentState == TIRED_RUN)
					{
						m_vVelocity = m_vDir * TIRED_RUN_SPEED * g_fDeltaTime;
					}
				}
			}
			else //일반달리기
			{
				if (m_fKeyAngle < 50)
				{
					if (m_nAniCurrentState == RUNNING_LOWER)
					{
						m_vVelocity = m_vDir * RUN_SPEED * g_fDeltaTime;
					}
					if (m_nAniCurrentState == TIRED_RUN)
					{
						m_vVelocity = m_vDir * TIRED_RUN_SPEED * g_fDeltaTime;
					}
				}
			}

			if (m_nStamina > STAMINA_CONSUME_DODGE)
			{
				if (g_pKeyManager->IsOnceKeyDown(VK_SPACE))
				{
					m_nStamina -= STAMINA_CONSUME_DODGE;
					m_nAniCurrentState = DASH_RUNNING;
					m_fAniSpeed = 1.75f;
				}
			}
		}

		else 
		{
			if (m_eCharState == SPRINT)
			{
				m_nAniCurrentState = RUNNING_STOP;
			}
			else
			{
				if (m_eCharState != TIRED)
				{
					m_nAniCurrentState = STANDING_IDLE;
				}
				else if(m_nAniCurrentState != TIRED_BEGIN)
				{
					m_nAniCurrentState = TIRED_DURING;
				}
			}
			if (g_pKeyManager->IsStayKeyDown(VK_SPACE) && m_nAniCurrentState == STANDING_IDLE)
			{
				g_pCamera->SetCamAction(40, 160);
				m_nAniCurrentState = GUARD_DURING;
			}
		}

		AttackStart();
	}
}

void cObj_Fiona::RenderCreature()
{
	for (int i = 0; i < m_vecWearItem.size(); ++i)
	{
		m_vecWearItem[i]->Render();
	}

	
	m_pProgressBar->Render(0, 0);
	m_pQuickSlot->Render(0, 0);
	m_pEquipment->Render(0, 0);
}

void cObj_Fiona::ReleaseCreature()
{
}

void cObj_Fiona::AniSituation()
{
	//m_fAniSpeed = 1;

	switch (m_nAniCurrentState)
	{
		case STANDING_IDLE:
			m_eCharState = IDLE;
			break;

		case DASH_RUNNING:
			g_pSoundManager->play("구르기", 0.4f);
			UpdateDirection();
			m_eCharState = ROLL_DASH;
			SetShiftMove(m_vDir, 70.f, 0.f, 1.f);
			SetReserveAnimation(STANDING_IDLE);
			break;

			////////////////////	달리기
		case RUNNING_LOWER:
			m_eCharState = RUNNING;
			m_isEnableReserve = false;
			break;

		case RUNNING_SPRINT:
			m_eCharState = SPRINT;
			m_isEnableReserve = false;
			break;

		case RUNNING_STOP:
			g_pSoundManager->play("스프린트끝", 0.4f);
			SetShiftMove(m_vDir, 60.f, 0, 0.25f);
			SetReserveAnimation(STANDING_IDLE);
			break;

			////////////////////	공격	
		case ATTACK_COMBO1:
			g_pSoundManager->play("공1", 0.3f);
			m_fAttackRate = 0.5f;
			AttackShiftMove();

			SetEnableHitAttack(1, 50, false, 0, 0.35f);
			SetShiftMove(m_vDir, 500.f, 0.12f, 0.16f);
			SetReserveAnimation(STANDING_IDLE);
			break;

		case ATTACK_COMBO2:
			g_pSoundManager->play("공2", 0.4f);
			g_pCamera->SetCamAction(4, 50);
			
			AttackShiftMove();

			SetEnableHitAttack(1, 60, false, 0, 0.4f);
			SetShiftMove(m_vDir, 480.f, 0.16f, 0.22f);

			SetReserveAnimation(STANDING_IDLE);
			break;

		case ATTACK_COMBO3:
			g_pSoundManager->play("공2", 0.4f);
			g_pCamera->SetCamAction(3, 50);

			AttackShiftMove();

			SetEnableHitAttack(1, 80, false, 0, 0.4f);
			SetShiftMove(m_vDir, 470.f, 0.16f, 0.2f);
			SetReserveAnimation(STANDING_IDLE);
			break;

		case ATTACK_COMBO4:
			g_pSoundManager->play("공2", 0.4f);
			g_pCamera->SetCamAction(3, 50);

			AttackShiftMove();

			SetEnableHitAttack(1, 100, false, 0, 0.4f);
			SetShiftMove(m_vDir, 470.f, 0.24f, 0.3f);
			SetReserveAnimation(STANDING_IDLE);
			break;

			////////////////////	스매쉬
		case COMBO1_SMASH:
			g_pSoundManager->play("강공", 0.4f);
			g_pCamera->SetCamAction(15, 160);

			AttackShiftMove();

			SetEnableHitAttack(1, 200, true, 0.1f, 0.17f, 2.0f);
			SetShiftMove(m_vDir, 1100.f, 0.13f, 0.15f);
			SetReserveAnimation(STANDING_IDLE);
			break;

		case COMBO2_SMASH:
			g_pSoundManager->play("강공", 0.4f);
			g_pCamera->SetCamAction(15, 160);

			AttackShiftMove();

			SetEnableHitAttack(0, 250, true, 0.3f, 0.4f, 2.5);
			SetShiftMove(m_vDir, 900.f, 0.3f, 0.32f);
			SetReserveAnimation(STANDING_IDLE);
			break;

		case COMBO3A_SMASH:
			g_pSoundManager->play("강공", 0.4f);
			g_pCamera->SetCamAction(23, 160);
			AttackShiftMove();

			SetEnableHitAttack(0, 150, false, 0.2f, 0.4f, 2.7);
			SetShiftMove(m_vDir, 400.f, 0.22f, 0.25f);
			SetReserveAnimation(STANDING_IDLE);
			break;

		case COMBO3B_SMASH:
			g_pSoundManager->play("3스매시발차기", 0.4f);
			g_pCamera->SetCamComeBack();
			g_pCamera->SetSmashCam();
			AttackShiftMove();

			SetEnableHitAttack(3, 300, true, 0.3f, 0.5f, 3.5);
			SetShiftMove(m_vDir, 50.f, 0.6f, 0.76f);
			SetReserveAnimation(STANDING_IDLE);
			break;

		case COMBO4_SMASH:
			g_pSoundManager->play("4스매시발차기", 0.4f);
			g_pCamera->SetCamAction(17, 160);
			AttackShiftMove();

			SetEnableHitAttack(2, 500, true, 0.33f, 0.5f, 4);
			SetShiftMove(m_vDir, 420.f, 0.28f, 0.32f);
	   		SetReserveAnimation(STANDING_IDLE);
			break;

			////////////////////	대쉬 어택
		case DASH_ATTACK:
			g_pSoundManager->play("방공", 0.4f);
			g_pCamera->SetCamAction(27, 160);

			m_eCharState = ATTACK;
			SetEnableHitAttack(0, 100, true, 0.1f, 0.4f, 2.5f);
			SetShiftMove(m_vDir, 110, 0, 0.18f);
			SetReserveAnimation(STANDING_IDLE);
			break;

			////////////////////	가드
		case GUARD_BEGIN:
			m_eCharState = GUARD;
			SetReserveAnimation(GUARD_DURING);
			break;

		case GUARD_DURING:
			g_pSoundManager->play("가드", 0.4f);
			m_eCharState = GUARD;
			break;

		case GUARD_ATTACK:
			g_pSoundManager->play("공1",0.4f);
			g_pCamera->SetCamAction(20, 160);
			AttackShiftMove();

			SetEnableHitAttack(1, 100, false, 0, 0.4f, 1.8f);

			m_eCharState = ATTACK;
			SetShiftMove(m_vDir, 150.f, 0.1f, 0.2f);
			SetReserveAnimation(STANDING_IDLE);
			break;

		case GUARD_HIT:
			g_pSoundManager->play("가드방어", 0.4f);
			m_eCharState = GUARD;
			SetReserveAnimation(m_nAniPrevIndexState);
			break;

			////////////////////	피격
		case DAMAGE_FRONT:
			g_pSoundManager->play("피격", 0.3f);

			SetShiftMove(m_vDir, -20.f, 0, 0.8f);
			SetReserveAnimation(STANDING_IDLE);
			break;

		case DAMAGE_BACK:
			g_pSoundManager->play("피격", 0.3f);

			SetShiftMove(m_vDir, 20.f, 0, 0.8f);
			SetReserveAnimation(STANDING_IDLE);
			break;

		case DOWN_BACKWARD:
			g_pSoundManager->play("가드슬립", 0.3f);
			m_eCharState = GUARD;
			SetShiftMove(m_vDir, -74.f, 0, 0.5f);
			SetReserveAnimation(STANDING_IDLE);
			break;

		case DOWN_FRONT_IDLE:
			m_eCharState = DOWN;
			break;

		case DOWN_FRONT_ROLL:
			m_eCharState = DOWN;
			SetShiftMove(m_vDir, 130.f, 0.3f, 0.9f);
			SetReserveAnimation(STANDING_IDLE);
			break;

		case DOWN_BACK_IDLE:
			m_eCharState = DOWN;
			break;

		case DOWN_BACK_ROLL:
			m_eCharState = DOWN;
			SetShiftMove(m_vDir, 130.f, 0.3f, 0.9f);
			SetReserveAnimation(STANDING_IDLE);
			break;

		case DAMAGE_STRONG_BACK:
			g_pSoundManager->play("피격", 0.3f);

			SetShiftMove(m_vDir, 100.f, 0, 0.6f);
			SetReserveAnimation(DOWN_FRONT_IDLE);
			break;

		case DAMAGE_STRONG_FRONT:
			g_pSoundManager->play("피격", 0.3f);

			SetShiftMove(m_vDir, -100.f, 0, 0.6f);
			SetReserveAnimation(DOWN_BACK_IDLE);
			break;

			////////////////////	스킬	
		case SP_SHIELD_ASSAULT:
			AttackShiftMove();

			SetEnableHitAttack(0, 100, true, 0.3f, 0.7f, 3.3f);
		   	SetShiftMove(m_vDir, 500.f, 0.34f, 0.8f);
			SetReserveAnimation(STANDING_IDLE);
			break;

		case COUNTER_ATTACK:
			g_pSoundManager->play("카운터어택", 0.3f);
			AttackShiftMove();

			m_eCharState = GUARD;
			SetEnableHitAttack(0, 100, true, 0.2f, 1.f, 3.f);
			SetShiftMove(m_vDir, 200.f, 0.11f, 0.19f);
			SetReserveAnimation(STANDING_IDLE);
			break;

			////////////////////	낙하
		case FALLING:
			m_eCharState = FALLDOWN;
			break;

		case FALLING_SAFE:
			g_pSoundManager->play("낮은착지", 0.4f);
			m_eCharState = FALLDOWN;
			SetReserveAnimation(STANDING_IDLE);
			break;

		case FALLING_DAMAGE:
			g_pSoundManager->play("높은착지", 0.4f);
			m_eCharState = FALLDOWN;
			SetReserveAnimation(STANDING_IDLE);
			break;

			////////////////////	피곤하네
		case TIRED_BEGIN:
			g_pSoundManager->play("스태미너오링", 0.4f);
			m_eCharState = TIRED;
			SetReserveAnimation(TIRED_DURING);
			break;
			
		case TIRED_DURING:
			m_eCharState = TIRED;
			break;

		case TIRED_END:
			m_eCharState = TIRED;
			SetReserveAnimation(STANDING_IDLE);
			break;

			////////////////////	포션
		case POTION_BEGIN:
			m_eCharState = POTION_DRINK;
			SetReserveAnimation(POTION_DURING);
			break;

		case POTION_DURING:
			g_pSoundManager->play("드링크포션", 0.5f);
			m_eCharState = POTION_DRINK;
			SetReserveAnimation(POTION_END);
			break;

		case POTION_END:
			m_eCharState = POTION_DRINK;
			SetReserveAnimation(STANDING_IDLE);
			break;

			////////////////////	팔라딘 변신
		case PALADIN_TRANSFORM:
			g_pSoundManager->play("팔라딘변신", 0.4f);
			m_eCharState = ROLL_DASH;
			SetReserveAnimation(STANDING_IDLE);
			break;

		default:
			break;
	}
}

void cObj_Fiona::Damaged(float fDamege, cGameObject* pAttacker, bool isSmash)
{
	if (m_eCharState == ROLL_DASH)
		return;

	D3DXVECTOR3 vDir = pAttacker->GetDirection();
	float fRange;

	fRange = D3DXVec3Dot(&vDir, &m_vDir);

	if (!isSmash)
	{
		if (m_eCharState == GUARD)
		{
			if (fRange < -cos(D3DXToRadian(60)))
			{
				//m_eCharState = HIT_DAMEGED;
				m_nAniCurrentState = GUARD_HIT;
			}
			else
			{
				m_nHp -= fDamege;
				m_eCharState = HIT_DAMEGED;
				m_nAniCurrentState = DAMAGE_BACK;
				//g_pSoundManager->play("피격3", 0.2f);
			}
		}
		else //가드 아닐 때
		{
			if (fRange < -cos(D3DXToRadian(60)))
			{
				m_nHp -= fDamege;
				m_eCharState = HIT_DAMEGED;
				m_nAniCurrentState = DAMAGE_FRONT;
				//g_pSoundManager->play("피격3", 0.2f);
			}
			else
			{
				m_nHp -= fDamege;
				m_eCharState = HIT_DAMEGED;
				m_nAniCurrentState = DAMAGE_BACK;
				//g_pSoundManager->play("피격3", 0.2f);
			}
		}
	}
	else // 스매쉬 공격
	{
		if (isSmash)
		{
			if (m_eCharState == GUARD)
			{
				if (fRange < -cos(D3DXToRadian(60)))
				{
					m_nAniCurrentState = DOWN_BACKWARD;
					m_eCharState = HIT_DAMEGED;
				}
				else
				{
					m_nHp -= 100;
					//m_nHp -= fDamege;
					m_nAniCurrentState = DAMAGE_STRONG_BACK;
					m_eCharState = HIT_DAMEGED;
					//g_pSoundManager->play("피격3", 0.2f);
				}
			}
			else
			{
				if (fRange < -cos(D3DXToRadian(60)))
				{
					m_nHp -= 100;
					//m_nHp -= fDamege;
					m_nAniCurrentState = DAMAGE_STRONG_FRONT;
					m_eCharState = HIT_DAMEGED;
					//g_pSoundManager->play("피격3", 0.2f);
				}
				else
				{
					m_nHp -= 100;
					//m_nHp -= fDamege;
					m_nAniCurrentState = DAMAGE_STRONG_BACK;
					m_eCharState = HIT_DAMEGED;
					//g_pSoundManager->play("피격3", 0.2f);
				}
			}
		}
	}
}

void cObj_Fiona::DiagonalDir()
{
	D3DXVec3Normalize(&m_vVelocity, &m_vVelocity);

	float  fDistAngle;
	int nPositive = 1;
	fDistAngle = D3DXVec3Dot(&m_vDir, &m_vVelocity);
	fDistAngle = acosf(fDistAngle);

	D3DXVECTOR3 vCross;
	D3DXVec3Cross(&vCross, &m_vVelocity, &m_vDir);
	m_vVelocity = D3DXVECTOR3(0, 0, 0);

	if (vCross.y > 0)
	{
		nPositive *= -1;
	}

	fDistAngle = D3DXToDegree(fDistAngle);

	if (fDistAngle < ROTATE_SPEED)
	{
		m_vRot.y += fDistAngle * nPositive;
	}
	else
	{
		m_vRot.y += ROTATE_SPEED * nPositive;
	}

	if (fDistAngle < 50)
	{
		UpdateDirection();
		if (m_nAniCurrentState == RUNNING_SPRINT)
			m_vVelocity = m_vDir * SPRINT_SPEED;
		else 
			m_vVelocity = m_vDir * RUN_SPEED;
	}
}

float cObj_Fiona::GetMoveSpeed()
{
	return (m_vVelocity.x * m_vVelocity.x + m_vVelocity.z * m_vVelocity.z);
}

bool cObj_Fiona::GetDistanceAngle(float camY, OUT float& fCos)
{
	UpdateDirection();

	D3DXMATRIXA16 mat1;
	D3DXMatrixRotationY(&mat1, D3DXToRadian(camY));
	D3DXVECTOR3 v1;
	D3DXVec3TransformNormal(&v1, &D3DXVECTOR3(0, 0, 1), &mat1);

	fCos = D3DXVec3Dot(&v1, &m_vDir);

	D3DXVec3Cross(&v1, &v1, &m_vDir);

	return v1.y > 0;
}

bool cObj_Fiona::IsAttacking()
{
	if (m_eCharState == ATTACK)
		return true;

	return false;
}

void cObj_Fiona::AnimationRateProcessLocal(float fAniRate)
{
	if (--m_nSlicingCount == 0)
	{
		m_pMesh->SetAnimaionSpeed(m_fAniSpeed);
	}

	for (int i = 0; i < m_vecWearItem.size(); ++i)
	{
		m_vecWearItem[i]->Update();
	}


	if (m_nAniCurrentState == COMBO4_SMASH && fAniRate > 0.1f)
	{
		g_pCamera->SetCamComeBack();
		g_pCamera->SetSmashCam();
	}

	if (m_nAniCurrentState == COUNTER_ATTACK && fAniRate > 0.25f && fAniRate < 0.6f && m_nCounterCount == 0)
	{
		if (g_pKeyManager->IsOnceKeyDown(VK_RBUTTON))
		{
			m_nCounterCount++;
			m_nAniPrevIndexState = 0;
			m_nAniCurrentState = COUNTER_ATTACK;
		}
	}

	if (m_nAniCurrentState == GUARD_HIT && fAniRate < 0.6f)
	{
		if (g_pKeyManager->IsOnceKeyDown(VK_RBUTTON))
		{
			m_nCounterCount = 0;
			m_nAniCurrentState = COUNTER_ATTACK;
		}
	}

	if (m_eCharState == ATTACK)
	{
		m_fSecTime = 0;

		if (fAniRate < 0.45f)
		{
			if (g_pKeyManager->IsOnceKeyDown(VK_LBUTTON))
			{
				if (m_nAniCurrentState == ATTACK_COMBO1 && m_nAniCount == 0)
				{
					m_nAniCount++;
					SetReserveAnimation(ATTACK_COMBO2, 0.3f, 1.43f);
				}
				else if (m_nAniCurrentState == ATTACK_COMBO2 && m_nAniCount == 1)
				{
					m_nAniCount++;
					SetReserveAnimation(ATTACK_COMBO3, 0.4f, 1.43f);
				}
				else if (m_nAniCurrentState == ATTACK_COMBO3 && m_nAniCount == 2)
				{
					m_nAniCount++;
					SetReserveAnimation(ATTACK_COMBO4, 0.3f, 1.8f);
				}
				else if (m_nAniCurrentState == ATTACK_COMBO4 && m_nAniCount == 3)
				{
					m_nAniCount++;
					SetReserveAnimation(STANDING_IDLE);
				}
			}

			/////////////////////////////스매쉬 공격//////////////////////////////
			if (m_eCharState != TIRED)
			{
				if (g_pKeyManager->IsOnceKeyDown(VK_RBUTTON))
				{
					if (m_nAniCurrentState == ATTACK_COMBO1)
					{
						m_nStamina -= STAMINA_CONSUME;
						SetReserveAnimation(COMBO1_SMASH, 0.28f, 1.5f);
					}
					else if (m_nAniCurrentState == ATTACK_COMBO2)
					{
						m_nStamina -= STAMINA_CONSUME;
						SetReserveAnimation(COMBO2_SMASH, 0.4f, 1.5f);
					}
					else if (m_nAniCurrentState == ATTACK_COMBO3)
					{
						m_nStamina -= STAMINA_CONSUME;
						SetReserveAnimation(COMBO3A_SMASH, 0.28f, 1.5f);
					}
					else if (m_nAniCurrentState == ATTACK_COMBO4)
					{
						m_nStamina -= STAMINA_CONSUME;
						g_pCamera->CamVibrate();
						SetReserveAnimation(COMBO4_SMASH, 0.3f, 1.7);
					}

					//3타 두번째 스매쉬
					if (m_nAniCurrentState == COMBO3A_SMASH)
					{
						m_nStamina -= STAMINA_CONSUME;
						SetReserveAnimation(COMBO3B_SMASH, 0.3f, 1.5f);
					}
				}
			}
		}

		if (m_fAttackRate < fAniRate)
		{
			if (g_pKeyManager->IsStayKeyDown(VK_SPACE))
			{
				if (!m_isRun)
				{
					m_nAniCurrentState = GUARD_DURING;
				}
				else
				{

 					m_vRot.y += m_isRightTurn ? m_fKeyAngle : -m_fKeyAngle;
					UpdateRotation();
					UpdateDirection();

					if (m_nStamina > STAMINA_CONSUME_DODGE)
					{
						m_nStamina -= STAMINA_CONSUME_DODGE + 7;
						m_nAniCurrentState = DASH_RUNNING;
						m_fAniSpeed = 1.65f;
					}
				}
				m_vVelocity = D3DXVECTOR3(0, 0, 0);
			}
		}
	}
	else
	{
		g_pCamera->SetCamComeBack();
		g_pCamera->SetSmashCam();
	}
}

void cObj_Fiona::Effect()
{
	//m_matShiledSkill

	m_matShiledSkill[0] = m_matR;
	D3DXMATRIXA16 matR;
	D3DXMatrixIdentity(&matR);
	D3DXMatrixRotationY(&matR, D3DXToRadian(90));
	m_matShiledSkill[0] *= matR;
	m_matShiledSkill[0]._41 = m_vPos.x;
	m_matShiledSkill[0]._42 = m_vPos.y + 10.f;
	m_matShiledSkill[0]._43 = m_vPos.z;


	D3DXMatrixIdentity(&matR);
	D3DXMatrixRotationY(&matR, D3DXToRadian(0));
	m_matShiledSkill[1] = m_matR;
	m_matShiledSkill[1] *= matR;
	m_matShiledSkill[1]._41 = m_vPos.x;
	m_matShiledSkill[1]._42 = m_vPos.y + 15.f;
	m_matShiledSkill[1]._43 = m_vPos.z;


	D3DXMatrixIdentity(&matR);
	D3DXMatrixRotationY(&matR, D3DXToRadian(270));
	m_matShiledSkill[2] = m_matR;
	m_matShiledSkill[2] *= matR;
	m_matShiledSkill[2]._41 = m_vPos.x;
	m_matShiledSkill[2]._42 = m_vPos.y + 8.f;
	m_matShiledSkill[2]._43 = m_vPos.z;

	if (m_nAniCurrentState == ATTACK_COMBO1)
	{
		if (m_pMesh->GetTrackRate() >= 0.15f && m_pMesh->GetTrackRate() <= 0.3f)
		{
			g_pEffectManager->AddSwingEffect("PIONA", m_vecWearItem[0]->GetSwingEffectVec().m_vecEffect_Swing_Up, m_vecWearItem[0]->GetSwingEffectVec().m_vecEffect_Swing_Down);
		}
	}
	else if (m_nAniCurrentState == ATTACK_COMBO2)
	{
		if (m_pMesh->GetTrackRate() >= 0.15f && m_pMesh->GetTrackRate() <= 0.3f)
		{
			g_pEffectManager->AddSwingEffect("PIONA", m_vecWearItem[0]->GetSwingEffectVec().m_vecEffect_Swing_Up, m_vecWearItem[0]->GetSwingEffectVec().m_vecEffect_Swing_Down);
		}
	}
	else if (m_nAniCurrentState == ATTACK_COMBO3)
	{
		if (m_pMesh->GetTrackRate() >= 0.05f && m_pMesh->GetTrackRate() <= 0.25f)
		{
			g_pEffectManager->AddSwingEffect("PIONA", m_vecWearItem[0]->GetSwingEffectVec().m_vecEffect_Swing_Up, m_vecWearItem[0]->GetSwingEffectVec().m_vecEffect_Swing_Down);
		}
	}
	else if (m_nAniCurrentState == ATTACK_COMBO4)
	{
		if (m_pMesh->GetTrackRate() >= 0.25f && m_pMesh->GetTrackRate() <= 0.4f)
		{
			g_pEffectManager->AddSwingEffect("PIONA", m_vecWearItem[0]->GetSwingEffectVec().m_vecEffect_Swing_Up, m_vecWearItem[0]->GetSwingEffectVec().m_vecEffect_Swing_Down);
		}
	}
	else if (m_nAniCurrentState == COMBO3B_SMASH)
	{
		if (m_pMesh->GetTrackRate() >= 0.25f && m_pMesh->GetTrackRate() <= 0.6f)
		{
			D3DXMATRIXA16* matAtkWorld = m_vecAttackBox[3].pmatSticking;
			D3DXVECTOR3	vecUp = { 0, 0, -80 };
			D3DXVECTOR3	vecDown = { 0, 0, -10 };

			D3DXVec3TransformCoord(&vecUp, &vecUp, matAtkWorld);
			D3DXVec3TransformCoord(&vecDown, &vecDown, matAtkWorld);

			g_pEffectManager->AddSwingEffect("PIONA", vecUp, vecDown, true);
			vecUp.y -= 7;
			g_pEffectManager->CreateDust(vecUp, 1, { 0.2f, 0.2f, 0.2f }, 5.f);
		}
	}
	else if (m_nAniCurrentState == RUNNING_SPRINT)
	{
		if (int(m_pMesh->GetTrackRate() * 100.f) % 50 <= 2 && int(m_pMesh->GetTrackRate() * 100.f) % 50 >= -2)
		{
			D3DXMATRIXA16 tempMat;
			D3DXMatrixIdentity(&tempMat);
			tempMat._41 = m_vPos.x;
			tempMat._42 = m_vPos.y;
			tempMat._43 = m_vPos.z;
			g_pEffectManager->CreateEllipseDust(&tempMat);
			g_pEffectManager->CreateSprayDust(&tempMat, -m_vDir, 2.f);
		}
	}
	else if (m_nAniCurrentState == DASH_RUNNING)
	{
		if (int(m_pMesh->GetTrackRate() * 100.f) % 100 <= 2 && int(m_pMesh->GetTrackRate() * 100.f) % 100 >= -2)
		{
			D3DXMATRIXA16 tempMat;
			D3DXMatrixIdentity(&tempMat);
			tempMat._41 = m_vPos.x;
			tempMat._42 = m_vPos.y;
			tempMat._43 = m_vPos.z;
			g_pEffectManager->CreateSprayDust(&tempMat, -m_vDir, 4.f);
		}
		if (int(m_pMesh->GetTrackRate() * 100.f) % 50 <= 2 && int(m_pMesh->GetTrackRate() * 100.f) % 50 >= -2)
		{
			D3DXMATRIXA16 tempMat;
			D3DXMatrixIdentity(&tempMat);
			tempMat._41 = m_vPos.x;
			tempMat._42 = m_vPos.y;
			tempMat._43 = m_vPos.z;
			g_pEffectManager->CreateEllipseDust(&tempMat);
		}
	}
	else if (m_nAniCurrentState == COMBO1_SMASH)
	{
		if (int(m_pMesh->GetTrackRate() * 100.f) % 100 <= 2 && int(m_pMesh->GetTrackRate() * 100.f) % 100 >= -2)
		{
			D3DXMATRIXA16 tempMat;
			D3DXMatrixIdentity(&tempMat);
			tempMat._41 = m_vPos.x;
			tempMat._42 = m_vPos.y;
			tempMat._43 = m_vPos.z;
			g_pEffectManager->CreateSprayDust(&tempMat, m_vDir, 4.f);
		}
		if (m_pMesh->GetTrackRate() >= 0.05f && m_pMesh->GetTrackRate() <= 0.2f)
		{
			g_pEffectManager->AddSwingEffect("PIONA", m_vecWearItem[0]->GetSwingEffectVec().m_vecEffect_Swing_Up, m_vecWearItem[0]->GetSwingEffectVec().m_vecEffect_Swing_Down, true);
		}
	}
	else if (m_nAniCurrentState == COMBO4_SMASH)
	{
		float fAniRate = m_pMesh->GetTrackRate();
		if (fAniRate >= 0.31f && fAniRate <= 0.33f)
		{
			D3DXMATRIXA16 tempMat;
			D3DXMatrixIdentity(&tempMat);
			tempMat._41 = m_vPos.x;
			tempMat._42 = m_vPos.y;
			tempMat._43 = m_vPos.z;
			g_pEffectManager->CreateWindEllipse(D3DXVECTOR3(1.f, 1.f, 1.f), D3DXVECTOR3(35, 0, 0), 2, m_vecAttackBox[2].pmatSticking);
			m_matSvaeAttackPoint = *m_vecAttackBox[2].pmatSticking;
		}
		if (int(fAniRate * 100) % 5 == 0 && fAniRate >= 0.31f && fAniRate <= 0.4f)
		{
			g_pEffectManager->CreateWindEllipseLine(D3DXVECTOR3(1.f, 1.f, 1.f), D3DXVECTOR3(35, 0, 0), 2, &m_matSvaeAttackPoint);
		}
		if (fAniRate >= 0.29f && fAniRate <= 0.4f)
		{
			if (int(fAniRate * 100) % 3 == 0)
				g_pEffectManager->CreateWindKick(D3DXVECTOR3(1.f, 1.f, 1.f), D3DXVECTOR3(35, 0, 0), m_vecAttackBox[2].pmatSticking);
		}

	}
	else if (m_nAniCurrentState == SP_SHIELD_ASSAULT)
	{
		float fAniRate = m_pMesh->GetTrackRate();

		if (fAniRate >= 0.1f && fAniRate <= 0.14f)
		{
			if (!g_pEffectManager->GetYellowRing())
				g_pEffectManager->CreateYellowRing(&m_matShiledSkill[1], 15.f);

		}

		if (fAniRate >= 0.31f && fAniRate <= 0.65f)
		{
			if (int(fAniRate * 100) % 5 == 0)
			{
				g_pEffectManager->CreatePWindEllipse(D3DXVECTOR3(0.0001f, 0.0001f, 0.0001f), D3DXVECTOR3(-10, 0, 0), 0.7f, &m_matShiledSkill[0]);
				g_pEffectManager->CreatePWindEllipseLine(D3DXVECTOR3(0.0001f, 0.0001f, 0.0001f), D3DXVECTOR3(-10, 0, 0), 0.7f, &m_matShiledSkill[0]);

			}
			if (int(fAniRate * 100) % 2 == 0)
			{
				D3DXMATRIXA16 matAtkWorld = m_matWorld;
				D3DXVECTOR3	vecUp = { -2, matAtkWorld._42, 0 };
				D3DXVECTOR3	vecDown = { 2, matAtkWorld._42, 0 };

				D3DXVec3TransformCoord(&vecUp, &vecUp, &matAtkWorld);
				D3DXVec3TransformCoord(&vecDown, &vecDown, &matAtkWorld);

				g_pEffectManager->CreateDust(vecUp, 1, { 0.2f, 0.2f, 0.2f }, 5.f, { -0.1f, 0, 0 });
				g_pEffectManager->CreateDust(vecDown, 1, { 0.2f, 0.2f, 0.2f }, 5.f, { 0.1f, 0, 0 });
			}
		}

		if (fAniRate >= 0.65f && fAniRate <= 0.68f)
		{
			g_pEffectManager->CreateCountAtk(D3DXVECTOR3(0.1f, 0.1f, 0.1f), D3DXVECTOR3(15, 0, 0), false, 0.75f, &m_matShiledSkill[2]);
		}

	}
	else if (m_nAniCurrentState == COMBO2_SMASH)
	{
		float fAniRate = m_pMesh->GetTrackRate();

		if (fAniRate >= 0.27f && fAniRate <= 0.29f)
		{
			g_pEffectManager->CreateCountAtk(D3DXVECTOR3(0.1f, 0.1f, 0.1f), D3DXVECTOR3(15, 0, 0),false, 0.75f, &m_matShiledSkill[2]);
		}
	}
	else if (m_nAniCurrentState == COUNTER_ATTACK)
	{
		float fAniRate = m_pMesh->GetTrackRate();

		if (fAniRate >= 0.13f && fAniRate <= 0.15f)
		{
			g_pEffectManager->CreateCountAtk(D3DXVECTOR3(0.1f, 0.1f, 0.1f), D3DXVECTOR3(15, 0, 0), false, 0.75f, &m_matShiledSkill[2]);
		}
	}
}

void cObj_Fiona::AttackShiftMove()
{
	m_eCharState = ATTACK;
	m_vRot.y = g_pCamera->GetRotYdir().y;
	UpdateRotation();
	UpdateDirection();
}

void cObj_Fiona::PaladinTransform()
{
	cSkinnedMesh* pTempMesh;

	pTempMesh = m_pMesh;
	m_pMesh = m_pMesh_paladin;
	m_pMesh_paladin = pTempMesh;

	m_pMesh->ConnectHitBox(m_mapHitBox, NULL);

	D3DXMATRIXA16 mat1;
	D3DXMatrixTranslation(&mat1, 99999, 99999, 99999);
	m_pMesh_paladin->Update(mat1);

	//m_pmatSword = m_pMesh->SearchMat("ValveBiped_Anim_Attachment_RH");
	//m_vecWearItem[0]->SetParent(m_pmatSword);
	//
	//
	//m_pmatSshield = m_pMesh->SearchMat("ValveBiped_Bip01_L_Forearm");
	//m_vecWearItem[1]->SetParent(m_pmatSshield);

	vector<string> boxName;
	boxName.push_back("ValveBiped_Anim_Attachment_LH");
	boxName.push_back("ValveBiped_Anim_Attachment_RH");
	boxName.push_back("ValveBiped_Bip01_L_Calf");
	boxName.push_back("ValveBiped_Bip01_R_Calf");


	m_pMesh->ConnectHitBox(boxName, m_vecAttackBox, NULL);
}

void cObj_Fiona::Slicing()
{
	m_nSlicingCount = 2;
	//g_pSoundManager->play("베는소리", 0.3f);
	m_pMesh->SetAnimaionSpeed(m_fAniSpeed * 0.87f);
}

void cObj_Fiona::ChangeEquip(int index)
{
	SAFE_DELETE(m_pMesh);
	cSkinnedMesh* mesh;


	switch (index)
	{
	case 0:
		mesh = m_pMesh_Shoe;
		break;
	case 1:
		mesh = m_pMesh_Dress;
		break;
	default:
		break;
	}

	cSkinnedMesh* pTempMesh;

	pTempMesh = m_pMesh;
	m_pMesh = mesh;
	mesh = pTempMesh;

	m_pMesh->SwitchAnimationBlend(STANDING_IDLE);

	m_pMesh->ConnectHitBox(m_mapHitBox, NULL);

	m_pmatSword = m_pMesh->SearchMat("ValveBiped_Anim_Attachment_RH");
	m_vecWearItem[0]->SetParent(m_pmatSword);
	
	m_pmatSshield = m_pMesh->SearchMat("ValveBiped_Bip01_L_Forearm");
	m_vecWearItem[1]->SetParent(m_pmatSshield);
	
	
	vector<string> boxName;
	boxName.push_back("ValveBiped_Anim_Attachment_LH");
	boxName.push_back("ValveBiped_Anim_Attachment_RH");
	boxName.push_back("ValveBiped_Bip01_L_Calf");
	boxName.push_back("ValveBiped_Bip01_R_Calf");
	
	
	m_pMesh->ConnectHitBox(boxName, m_vecAttackBox, NULL);
}