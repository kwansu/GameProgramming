#include "stdafx.h"
#include "cPrince.h"
using namespace ns_PRINCE;


cPrince::cPrince()
{
	m_fMoveRadius = 6.f;
	m_fAttackRange = 30;
	m_fDetectionRange = 200;
}

cPrince::~cPrince()
{
}

void cPrince::SetupCreature()
{
	m_pMesh = new cSkinnedMesh;

	m_pMesh->Load("./3dObject/Prince/", "prince_ani32.X", m_stBoundingSphere);

	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, 0.22f, 0.22f, 0.22f);

	D3DXMATRIXA16 matR;
	D3DXMatrixRotationY(&matR, D3DXToRadian(180));
	SetOriginMatrix(matS * matR);

	//LoadHitBox("./GameData/lavasat.txt", matS);

	//m_stFireBall.stAttackBox.vHalfSize = D3DXVECTOR3(3, 3, 3);

	m_nHp = fHP_MAX;
	m_nDamaged = 9;

	m_nStamina = fSTAMINA_MAX;
}

void cPrince::UpdateCreature()
{
	UpdateTransform();

	if (IsFindTarget(m_vToTargetDir, m_fDist))
	{
		m_fDistAngle = BetweenCosAngleFromTarget(m_vToTargetDir, m_isClock);
		m_fDistAngle = D3DXToDegree(acos(m_fDistAngle));

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


	if (m_eActState == ACTION_TRACE)
		ActionTrace();

	if (g_pKeyManager->IsOnceKeyDown('N'))
	{
		m_nAniCurrentState = �����޺�2;
	}

	if (g_pKeyManager->IsOnceKeyDown('M'))
	{
		m_nAniCurrentState = ����ġ��;
	}

	if (g_pKeyManager->IsOnceKeyDown('H'))
	{
		m_nAniCurrentState = �����ġ��;
	}
}

void cPrince::AniSituation()
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
	case �ٺ�ó���ٱ�:
		m_isActiveTurn = true;
		m_isEnableReserve = false;
		break;
	case ������_��:
		SetShiftMove(-m_vDir, 100, 0, 0.21f);
		break;
	case ������_����:
		SetShiftMove(-m_vRight, 100, 0, 0.21f);
		break;
	case ������_������:
		SetShiftMove(m_vRight, 100, 0, 0.18f);
		break;
	case ������_����:
		SetShiftMove(m_vDir, 100, 0, 0.20f);
		break;
	case �׷α����:
		SetShiftMove(-m_vDir, 100, 0.2f, 0.55f);
		SetReserveAnimation(�׷α���);
		break;
	case �׷α���:
		m_isEnableReserve = false;
		m_nDownCount = 120;
		break;
	case �׷αⳡ:
		SetShiftMove(m_vDir, 100, 0.17f, 0.43f);
		break;
	case �׳����:
		// 0.49	0.61
		SetShiftMove(m_vDir, 100, 0.48f, 0.61f);
		m_nStamina -= 300;
		break;
	case ����ġ��:
		// 0.16	0.3
		// 0.52	0.67
		if (rand() % 3 == 0)
			SetReserveAnimation(�����޺�2, 0.75f);

		SetShiftMove(m_vDir, 100, 0.52f, 0.6f);
		m_nStamina -= 500;
		break;
	case �����޺�2:
		// 0.09	0.28	right
		// 0.28	0.48	left
		SetShiftMove(m_vDir, 100, 0.09f, 0.45f);
		m_nStamina -= 600;
		break;
	case �ι��ֵθ���:
		// 0.39	0.53	right
		// 0.53	0.7		left
		SetShiftMove(m_vDir, 100, 0.40f, 0.7f);
		m_nStamina -= 450;
		break;
	case �����ει����:
		// 0.29	0.43	right
		// 0.59	0.73	right
		SetShiftMove(m_vRight, 100, 0.29f, 0.43f);
		m_nAttackCombo = 0;
		m_nStamina -= 450;
		break;
	case ��Ƽ����ġ��:
		// 0.43	0.60	right/left
		SetShiftMove(m_vDir, 100, 0.43f, 0.58f);
		m_nStamina -= 400;
		break;
	case �޼տ÷�ġ��:
		// 0.35	0.60	left
		SetShiftMove(m_vDir, 100, 0.39f, 0.62f);
		m_nStamina -= 250;
		break;
	case �޼�ó����:
		// 0.27	0.55	left
		m_fTurnSpeed = fTURN_SPEED;
		m_nStamina -= 200;
		break;
	case �̻��ϰԿ޼�ġ��:
		// 0.27	0.59	left
		m_fTurnSpeed = fTURN_SPEED;
		m_nStamina -= 250;
		break;
	case �����ġ��:
		// 0.16	0.28	right
		// 0.3	0.48	left
		SetShiftMove(m_vDir, 200, 0.16f, 0.26f);
		m_nAttackCombo = 0;
		m_nStamina -= 650;
		break;
	case ���ġ��_����ũ��XXX:
		// 0.16	0.25	right
		// 0.4	0.51	right
		// 0.61	0.72	right
		SetShiftMove(m_vRight, 100, 0.16f, 0.25f);
		m_nAttackCombo = 0;
		m_nStamina -= 650;
		break;
	case ��յ�����̾:
		SetShiftMove(-m_vDir, 50, 0.86f, 0.9f);
		break;
	case ȸ�����̾:
		SetShiftMove(m_vDir, 60, 0.7f, 0.8f);
		break;
	}
}

void cPrince::AnimationRateProcessLocal(float fAniRate)
{
	switch (m_nAniCurrentState)
	{
	case �����ει����:
		if (fAniRate > 0.50 && m_nAttackCombo == 0)
		{
			SetShiftMove(m_vRight, 100, 0.58f, 0.64f);
			++m_nAttackCombo;
		}
		break;

	case �޼�ó����:
		if (fAniRate > 0.27 && fAniRate < 0.55)
		{
			m_isActiveTurn = true;
		}
		else
			m_isActiveTurn = false;
		break;

	case �̻��ϰԿ޼�ġ��:
		if (fAniRate > 0.39 && fAniRate < 0.59)
		{
			m_isActiveTurn = true;
		}
		else
			m_isActiveTurn = false;
		break;

	case �����ġ��:
		if (fAniRate > 0.27 && m_nAttackCombo == 0)
		{
			SetShiftMove(-m_vDir, 420, 0.3f, 0.39f);
			++m_nAttackCombo;
		}
		else if (fAniRate > 0.3f && fAniRate < 0.38f)
		{
			m_vRot.y += 3.5f;
		}
		break;

	case ���ġ��_����ũ��XXX:
		if (fAniRate > 0.35 && m_nAttackCombo == 0)
		{
			SetShiftMove(m_vRight, 100, 0.4f, 0.47f);
			++m_nAttackCombo;
		}
		else if (fAniRate > 0.5 && m_nAttackCombo == 1)
		{
			SetShiftMove(m_vRight, 100, 0.64f, 0.75f);
			++m_nAttackCombo;
		}
		break;

	case �׷α���:
		if (--m_nDownCount < 0)
		{
			m_nAniCurrentState = �׷αⳡ;
		}
		break;
	}
}

void cPrince::AICommand()
{
	m_eActState = ACTION_ATTACK;

	if (m_nStamina < 0)
	{
		m_nAniCurrentState = ü�´ٺ���;
		m_nStamina = fSTAMINA_MAX;
		return;
	}

	int r = rand() % 20;

	if (m_fDistAngle > fATTACK_MAX_ANGLE)
	{
		if (m_fDist <= m_fAttackRange)
		{
			// ���� ����
			if (r > 13 && m_fDistAngle < 120)
			{
				if (m_isClock)
					m_nAniCurrentState = �޼�ó����;
				else
					m_nAniCurrentState = r > 17 ? ���ġ��_����ũ��XXX : �̻��ϰԿ޼�ġ��;

				return;
			}
			else if (r < 3)
			{
				m_nAniCurrentState = ȸ�����̾;
				return;
			}
			else if (r < 7)
			{
				m_nAniCurrentState = �����ġ��;
				return;
			}
		}

		if (m_fDistAngle > fTURN_MAX_ANGLE)
			m_nAniCurrentState = m_isClock ? ���ʵ��� : �����ʵ���;
		else
		{
			m_isActiveTurn = true;
			m_fTurnSpeed = fTURN_SPEED;
			m_eActState = ACTION_COMMAND;
		}
	}
	else if (m_fDist > fFIREBALL_MAX_DIST)
	{
		// ���� ������, �ٰ�����
		m_fTurnSpeed = fTRACE_ANGLE_SPEED;
		m_eActState = ACTION_TRACE;
		m_nAniCurrentState = �ٺ�ó���ٱ�;
	}
	else if (m_fDist > m_fAttackRange)
	{
		// ���̾ ���� ����
		if (r > 17)
			m_nAniCurrentState = ��ո�����̾;
		else if (r > 15)
			m_nAniCurrentState = ��յ�����̾;
		else if (r > 12)
			m_nAniCurrentState = ���̾2;
		else if (r > 10)
			m_nAniCurrentState = ���̾1;
		else
			m_eActState = ACTION_TRACE;
	}
	else
	{
		// ���� ���� ���� ����
		if (r > 18)
			m_nAniCurrentState = ��ո�����̾;
		else if(r > 15)
			m_nAniCurrentState = �ι��ֵθ���;
		else if (r > 11)
			m_nAniCurrentState = ����ġ��;
		else if (r > 8)
			m_nAniCurrentState = ��Ƽ����ġ��;
		else if (r > 5)
			m_nAniCurrentState = �����ġ��;
		else if (r > 3)
			m_nAniCurrentState = �׳����;
		else if (m_isClock)
			m_nAniCurrentState = �޼տ÷�ġ��;
		else if (r > 1)
			m_nAniCurrentState = ���ġ��_����ũ��XXX;
		else
			m_nAniCurrentState = �����ει����;
	}
}

void cPrince::ActionTrace()
{
	if (m_fDist < m_fAttackRange)
	{
		m_eActState = ACTION_COMMAND;
		return;
	}

	if (m_nAniCurrentState == �ٺ�ó���ٱ�)
		m_vPos += m_vDir * fRUN_SPEED * g_fDeltaTime;
	else
		m_nAniCurrentState = �ٺ�ó���ٱ�;

	if(m_fDistAngle > fTRACE_ANGLE_SPEED)
		m_eActState = ACTION_COMMAND;
}

void cPrince::Damaged(float fDamege, cGameObject * pAttacker, bool isSmash)
{
	m_nHp -= fDamege;

	if (isSmash &&m_nHp / 3000 <= m_nDamaged && m_nAniCurrentState != ü�´ٺ���)
	{
		--m_nDamaged;
		if (m_nDamaged % 3 == 0)
		{
			m_nAniCurrentState = �׷α����;
			m_fAniSpeed = 0.9f;
		}
		else
		{
			if (m_fDistAngle < 45)
			{
				m_nAniCurrentState = ������_����;
			}
			else if (m_fDistAngle > 135)
			{
				m_nAniCurrentState = ������_��;
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
}
