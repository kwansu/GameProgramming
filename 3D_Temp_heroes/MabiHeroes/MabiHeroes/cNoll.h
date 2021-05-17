#pragma once
#include "cEnemy.h"


/*

놀은 케릭터가 180도 돌아가 있음.
디릭센 활용시 주의하기.

*/
enum eNOLL_STATE
{
	NOLL_STATE_NOMAL,
	NOLL_STATE_DIE,
	NOLL_STATE_WALK,
	NOLL_STATE_HIT,
	NOLL_STATE_HITFLYING,
	NOLL_STATE_ATTACK,
	NOLL_STATE_TURN,
	NOLL_STATE_END
};
enum eNOLL_ANINUM
{
	NOLL_ANI_TURN_LEFT,
	NOLL_ANI_TURN_RIGHT,
	NOLL_ANI_FLY_ATTACK,
	NOLL_ANI_DOUBLE_ATTACK,
	NOLL_ANI_SMASH_ATTACK,
	NOLL_ANI_HIT2,
	NOLL_ANI_HIT1,
	NOLL_ANI_KNOCK_BACK_STAND_UP,
	NOLL_ANI_KNOCK_BACK_ING,
	NOLL_ANI_KNOCK_BACK_START,
	NOLL_ANI_FOUR_FOOT_BACK_JUMP,
	NOLL_ANI_TWO_FOOT_BACK_JUMP,
	NOLL_ANI_NOMAL,
	NOLL_ANI_WALK_RIGHT,
	NOLL_ANI_WALK_LEFT,
	NOLL_ANI_WALK_BACK,
	NOLL_ANI_WALK_FRONT,
	NOLL_ANI_END
};


class cWearItem;


class cNoll : public cEnemy
{
private:
	float			m_saveTime;
	int				m_statePriority[7];
	eNOLL_STATE		m_currentState;
	eNOLL_STATE		m_oldState;


	float			m_attackDilay;
	bool			m_isFight;

	int				m_playAniNum;
	float			m_Hp;		//	임시
	D3DXVECTOR3*	m_pTarget;
	cGameObject*	m_pTargetObj;


	cWearItem*		m_hammer;

	D3DXMATRIXA16*	m_pmatClub;
public:
	cNoll();
	~cNoll();

	void ManagedState();
	void AnimationToState();						// 에니매이션 체인지

	void SetTarget(D3DXVECTOR3* pTarget) { m_pTarget = pTarget; }
	void SetTargetObj(cGameObject* pTarget) { m_pTargetObj = pTarget; }
	void CircleAttackDilay();
	void CompulsionAnimation();
	void NollShiftMoveUpdate();
	void Slicing();

	virtual void SetupCreature() override;
	virtual void ReleaseCreature() override;
	virtual void UpdateCreature() override;
	virtual void RenderCreature() override;
	virtual void Damaged(float fDamege, cGameObject* pAttacker, bool isSmash) override;

	D3DXVECTOR3 GetDirection() override;

	void AnimationRateProcessLocal(float fAniRate) override;
};

