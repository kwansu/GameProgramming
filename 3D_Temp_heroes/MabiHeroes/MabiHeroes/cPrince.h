#pragma once
#include "cEnemy.h"

namespace ns_PRINCE
{
#define fTURN_SPEED				110
#define fRUN_SPEED				90
#define fFIREBALL_MAX_DIST		140
#define fTURN_MAX_ANGLE			50
#define fATTACK_MAX_ANGLE		45
#define fTRACE_ANGLE_SPEED		60

#define fHP_MAX					30000
#define fSTAMINA_MAX			10000
}

class cPrince :
	public cEnemy
{
private:
	enum ePRINCE_ANISTATE;

	// boss down
	int					m_nDamaged;
	int					m_nDownCount;

public:
	cPrince();
	~cPrince();

private:
	// cCreature override
	void SetupCreature()	override;
	void UpdateCreature()	override;
	void AniSituation()		override;
	void AnimationRateProcessLocal(float fAniRate)	override;

	// AI행동
	void AICommand();
	void ActionTrace();

	void Damaged(float fDamege, cGameObject* pAttacker, bool isSmash);
};


enum cPrince::ePRINCE_ANISTATE
{
	대기,
	간지걷기,
	바보처럼뛰기,
	왼쪽돌기,
	오른쪽돌기,
	체력다빠짐,
	마이아파함,
	데미지_앞,
	데미지_왼쪽,
	데미지_오른쪽,
	데미지_뒤쪽,
	그로기시작,
	그로기중,
	그로기끝,
	그냥찌르기,
	연속치기,
	연속콤보2,
	두번휘두르기,
	두번때리기_고장,
	옆으로두번찌르기,
	모아서양손치기,
	왼손올려치기,
	왼손처내기,		// 왼손 공격
	이상하게왼손치기,	// 오른쪽 공격
	찌르기_고장,
	찌르고돌아치기,	// 앞쪽에서 뒤돌아 치기
	삼단치기_훼이크다XXX,
	파이어볼1,
	파이어볼2,
	양손들어파이어볼,
	양손모아파이어볼,
	회전파이어볼,
};
