#pragma once
#include "cCreature.h"

enum MonsterType
{
	MONSTER_SKELARCHER,
	MONSTER_BOSS,
	MONSTER_NULL
};

static D3DXVECTOR3* s_vpPlayerPosition;

class cEnemy : public cCreature
{
protected:
	enum eENEMY_ACTION;
	eENEMY_ACTION	m_eActState;

	MonsterType		ID;
	float			m_fDetectionRange;
	float			m_fAttackRange;
	float			m_fSpeed;

	// command info
	D3DXVECTOR3		m_vToTargetDir;
	float			m_fDist;
	float			m_fDistAngle;
	bool			m_isClock;
	int				m_nAttackCombo;

	// rotation reserve
	bool			m_isActiveTurn;
	float			m_fTurnSpeed;

public:
	static cCreature*	s_pTarget;

public:
	cEnemy();
	~cEnemy();

	virtual void SetupCreature() override;
	virtual void UpdateCreature() override;
	virtual void RenderCreature() override;
	virtual void ReleaseCreature() override;

	virtual void temp_KeyStateControl();
	virtual void UpdateAnimation() {}

	// ���� AI�Լ�
	virtual bool IsFindTarget(OUT D3DXVECTOR3& vToTargetDir, OUT float& fDistance);
	virtual float BetweenCosAngleFromTarget(const D3DXVECTOR3& vToTargetDir, OUT bool& isClock);	// ĳ������ m_vDir���� �ڻ��ΰ��� ���� ����

	//	STATE_NORMAL,			/* �⺻ ���� */
	//	STATE_MOVE,				/* �ȱ� ���� */
	//	STATE_RUN,				/* �ٱ� ���� */
	//	STATE_ATTACK,			/* ���� ���� */
	//	STATE_KNOCKBACK,		/* �˹� ���� */
	//	STATE_TIRED,			/* ���� ���� */
	//	STATE_ROLLRUN,			/* ������ ���� */
	//	STATE_KNOCKDOWN,		/* ������ ���� */
	//	STATE_DOWNUP,			/* �Ͼ�� ���� */
	//	STATE_DEATH				/* ���� ���� */
};


enum cEnemy::eENEMY_ACTION
{
	ACTION_COMMAND,
	ACTION_ATTACK,
	ACTION_TRACE,
	ACTION_STEP
};