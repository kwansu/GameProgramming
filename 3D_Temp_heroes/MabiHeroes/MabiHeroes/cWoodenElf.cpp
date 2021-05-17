#include "stdafx.h"
#include "cWoodenElf.h"


cWoodenElf::cWoodenElf()
{
	m_fMoveRadius = 4.3f;
	m_fAttackRange = 80;
	m_fDetectionRange = 130;
}


cWoodenElf::~cWoodenElf()
{
}

void cWoodenElf::SetupCreature()
{
	m_pMesh = new cSkinnedMesh;

	m_pMesh->Load("./3dObject/woodenelf/", "woodenelf.X", m_stBoundingSphere);

	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, 0.2f, 0.2f, 0.2f);

	D3DXMATRIXA16 matR;
	D3DXMatrixRotationY(&matR, D3DXToRadian(180));
	SetOriginMatrix(matS * matR);

	m_pmatAttach = m_pMesh->SearchMat("ValveBiped_Anim_Attachment_RH");
	m_pBow = new cWearItem;
	m_pBow->Setup("bow.x", m_pmatAttach);

	//LoadHitBox("./GameData/lavasat.txt", matS);

	//m_stFireBall.stAttackBox.vHalfSize = D3DXVECTOR3(3, 3, 3);

	m_nHp = fHP_MAX;
}

void cWoodenElf::UpdateCreature()
{
	UpdateTransform();

	if (IsFindTarget(m_vToTargetDir, m_fDist))
	{
		m_fDistAngle = BetweenCosAngleFromTarget(m_vToTargetDir, m_isClock);
		m_fDistAngle = D3DXToDegree(acos(m_fDistAngle));

		if (m_eActState == ACTION_COMMAND)
			AICommand();
		else if (m_eActState == ACTION_TRACE)
			ActionTrace();
	}

	float fAngle = m_fTurnSpeed * g_fDeltaTime;
	if (m_isActiveTurn && m_fDistAngle > fAngle)
	{
		fAngle = (m_isClock ? -fAngle : fAngle);
		m_vRot.y += fAngle;
		UpdateDirection();
	}

	if (g_pKeyManager->IsOnceKeyDown('J'))
	{
		m_nAniCurrentState = ++m_nAniCurrentState % 23;
	}
}

void cWoodenElf::RenderCreature()
{
	m_pBow->Render();
}

void cWoodenElf::AniSituation()
{
	SetReserveAnimation(���);
	m_isActiveTurn = false;

	switch (m_nAniCurrentState)
	{
	case ���:
		m_eActState = ACTION_COMMAND;
		m_isEnableReserve = false;
		break;
	case ���ʵ���: case �����ʵ���:
		m_fTurnSpeed = fTURN_SPEED;
		m_isActiveTurn = true;
		break;
	case �ٱ�:
		m_isActiveTurn = true;
		m_isEnableReserve = false;
		break;
	case ��������:
		SetReserveAnimation(����������);
		break;
	case ����������:
		SetReserveAnimation(�Ͼ��);
		break;
	case ��������:
		SetReserveAnimation(������);
		break;
	case ������:
		m_isEnableReserve = false;
		break;
	case Ȱ���:
		break;
	}
}

void cWoodenElf::AnimationRateProcessLocal(float fAniRate)
{
	m_pBow->Update();
}

void cWoodenElf::AICommand()
{
	m_eActState = ACTION_ATTACK;

	if (m_fDistAngle > fATTACK_MAX_ANGLE)
	{
		if (m_fDistAngle > fTURN_MAX_ANGLE)
			m_nAniCurrentState = m_isClock ? ���ʵ��� : �����ʵ���;
		else
		{
			m_isActiveTurn = true;
			m_fTurnSpeed = fTURN_SPEED;
			m_eActState = ACTION_COMMAND;
		}
	}
	else if(m_fDist > m_fAttackRange)
	{
		m_eActState = ACTION_TRACE;
	}
	else
	{
		int r = rand() % 20;

		if (r > 15)
			m_eActState = ACTION_STEP;
		else
			m_nAniCurrentState = Ȱ���;
	}
}

void cWoodenElf::ActionTrace()
{
	if (m_fDist < fAPPROACH_DISTANCE)
	{
		m_eActState = ACTION_COMMAND;
		return;
	}

	if (m_nAniCurrentState == �ٱ�)
		m_vPos += m_vDir * fRUN_SPEED * g_fDeltaTime;
	else
		m_nAniCurrentState = �ٱ�;

	if (m_fDistAngle > fTRACE_ANGLE_SPEED)
		m_eActState = ACTION_COMMAND;

	if (m_fDistAngle > fTRACE_ANGLE_SPEED)
		m_eActState = ACTION_COMMAND;
}

void cWoodenElf::ActionStep()
{
}

void cWoodenElf::ActionMovement()
{
	switch (m_nAniCurrentState)
	{
	case �ٱ�:
		m_vPos += m_vDir * g_fDeltaTime * fRUN_SPEED;
		break;
	case �ս���:
		m_vPos += m_vDir * g_fDeltaTime * m_fSpeed;
		break;
	case �޽���:
		m_vPos += -m_vDir * g_fDeltaTime * m_fSpeed;
		break;
	case �޽���:
		m_vPos += -m_vRight * g_fDeltaTime * m_fSpeed;
		break;
	case ��������:
		m_vPos += m_vRight * g_fDeltaTime * m_fSpeed;
		break;
	}
}

void cWoodenElf::Damaged(float fDamege, cGameObject * pAttacker, bool isSmash)
{
	m_nHp -= fDamege;

	if (isSmash)
	{
		m_vDir = m_vPos - pAttacker->GetPosition();

		m_eActState = ACTION_ATTACK;
		m_nAniCurrentState = ��������;
		m_nAniPrevIndexState = ��������;
		m_pMesh->SwitchAnimationBlend(��������);
		SetShiftMove(m_vDir, fDamege * 0.3f, 0, 0.6f);
	}
	else
	{
		if (m_fDistAngle < 45)
		{
			m_nAniCurrentState = ������_����;
		}
		else if (m_fDistAngle > 135)
		{
			m_nAniCurrentState = ������_����;
		}
		else if (m_isClock)
		{
			m_nAniCurrentState = ������_������;
		}
		else
		{
			m_nAniCurrentState = ������_����;
		}
	}
}
