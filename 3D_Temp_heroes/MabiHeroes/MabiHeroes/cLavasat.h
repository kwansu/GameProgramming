#pragma once
#include "cEnemy.h"

namespace ns_Lavasat
{
#define fSHORT_RUSH_DISTANCE	100
#define fSWOOP_MAX_DISTANCE		250
#define fAVOID_MAX_DISTANCE		40
#define fTURN_SPEED				90
#define fRUN_SPEED				150
#define fTURN_MAX_ANGLE			50
#define fATTACK_MAX_ANGLE		35
#define TRACE_ANGLE_SPEED		25
}

class cLavasat :
	public cEnemy
{
private:
	enum eLAVA_ANISTATE;

	// 브레스용 투사체
	ST_MISILE				m_stFireBall;

	bool					m_isRun;

	// boss down
	int						m_nDamaged;
	int						m_nDownCount;

	// effect
	ST_COLLISION_BOX_STICK	matCollision[4];
	bool					m_isStomp;

public:
	cLavasat();
	~cLavasat();

private:
	// cCreature override
	void SetupCreature()	override;
	void UpdateCreature()	override;
	void RenderCreature()	override;
	void AniSituation()		override;
	void AnimationRateProcessLocal(float fAniRate)	override;

	// AI행동
	void AICommand();
	void ActionAvoid();
	void ActionFireBall();
	void ActionRodeo(float fAniRate);
	void ActionRodeoTurn(float fAniRate);

	void Damaged(float fDamege, cGameObject* pAttacker, bool isSmash);

	void AllAttackBoxEnable(float fDamage, bool isSmash, float fStartRate, float fEndRate);

	void Effect();
};


enum cLavasat::eLAVA_ANISTATE
{
	대기,
	왼쪽돌기,
	오른쪽돌기,
	왼쪽점프,
	오른쪽점프,
	포효,
	짧은돌진,
	달리는중,
	왼손불꽃싸다구,
	오른손불꽃싸다구,
	올려치기,
	내려치기,
	스톰프,
	로데오,
	로데오회전,
	뒷점프,
	죽는동작,
	피없어아파하기,
	쓰러짐,
	쓰러진상태,
	일어섬,
	데미지_뒤,
	데미지_바닥,
	데미지_왼쪽,
	데미지_오른쪽,
	돌진시작,
	돌진중,
	브레스,
	뒷점프브레스,
	시네마틱1,
	시네마틱2,};


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


