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

	// 공통 AI함수
	virtual bool IsFindTarget(OUT D3DXVECTOR3& vToTargetDir, OUT float& fDistance);
	virtual float BetweenCosAngleFromTarget(const D3DXVECTOR3& vToTargetDir, OUT bool& isClock);	// 캐릭터의 m_vDir과의 코사인값과 방향 리턴

	//	STATE_NORMAL,			/* 기본 상태 */
	//	STATE_MOVE,				/* 걷기 상태 */
	//	STATE_RUN,				/* 뛰기 상태 */
	//	STATE_ATTACK,			/* 공격 상태 */
	//	STATE_KNOCKBACK,		/* 넉백 상태 */
	//	STATE_TIRED,			/* 헥헥 상태 */
	//	STATE_ROLLRUN,			/* 구르기 상태 */
	//	STATE_KNOCKDOWN,		/* 쓰러짐 상태 */
	//	STATE_DOWNUP,			/* 일어나는 상태 */
	//	STATE_DEATH				/* 죽음 상태 */
};


enum cEnemy::eENEMY_ACTION
{
	ACTION_COMMAND,
	ACTION_ATTACK,
	ACTION_TRACE,
	ACTION_STEP
};