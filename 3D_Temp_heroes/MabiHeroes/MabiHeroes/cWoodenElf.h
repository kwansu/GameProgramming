#pragma once
#include "cEnemy.h"

namespace ns_WOODEN
{
#define fTURN_SPEED				90
#define fRUN_SPEED				60
#define fTURN_MAX_ANGLE			50
#define fATTACK_MAX_ANGLE		40
#define fAVOID_MAX_DISTANCE		15
#define fTRACE_ANGLE_SPEED		60
#define fAPPROACH_DISTANCE		60 

#define fHP_MAX					3000
}

class cWoodenElf :
	public cEnemy
{
private:
	enum eWOODEND_ANISTATE;

	// wear
	cWearItem*		m_pBow;
	D3DXMATRIXA16*	m_pmatAttach;

public:
	cWoodenElf();
	~cWoodenElf();

private:
	// cCreature override
	void SetupCreature()	override;
	void UpdateCreature()	override;
	void RenderCreature()	override;
	void AniSituation()		override;
	void AnimationRateProcessLocal(float fAniRate)	override;

	// AI행동
	void AICommand();
	void ActionTrace();
	void ActionStep();
	void ActionMovement();

	void Damaged(float fDamege, cGameObject* pAttacker, bool isSmash);
};


enum cWoodenElf::eWOODEND_ANISTATE
{
	대기,
	왼쪽돌기,
	오른쪽돌기,
	도발,
	도발희귀,
	앞스탭,
	뒷스탭,
	왼스탭,
	오른스탭,
	뛰기,
	데미지_앞쪽,
	데미지_뒤쪽,
	데미지_왼쪽,
	데미지_오른쪽,
	쓰러지기,
	쓰러진상태,
	일어나기,
	점프시작,
	점프중,
	점프끝,
	활쏘기,
	무기스왑,
	강력한_점프어택,
};
