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

	// �극���� ����ü
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

	// AI�ൿ
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
	���,
	���ʵ���,
	�����ʵ���,
	��������,
	����������,
	��ȿ,
	ª������,
	�޸�����,
	�޼պҲɽδٱ�,
	�����պҲɽδٱ�,
	�÷�ġ��,
	����ġ��,
	������,
	�ε���,
	�ε���ȸ��,
	������,
	�״µ���,
	�Ǿ�������ϱ�,
	������,
	����������,
	�Ͼ,
	������_��,
	������_�ٴ�,
	������_����,
	������_������,
	��������,
	������,
	�극��,
	�������극��,
	�ó׸�ƽ1,
	�ó׸�ƽ2,};


/*0	ValveBiped_Bip01				����
1	ValveBiped_Bip01_Head1			�Ӹ�
2	ValveBiped_Bip01_L_Calf			�޴ٸ���
3	ValveBiped_Bip01_L_Foot			�޴ٸ�
4	ValveBiped_Bip01_L_Forearm		�մٸ���
5	ValveBiped_Bip01_L_Hand			�մٸ�
6	ValveBiped_Bip01_Neck			��(�� ����)
7	ValveBiped_Bip01_R_Calf
8	ValveBiped_Bip01_R_Foot
9	ValveBiped_Bip01_R_Forearm
10	ValveBiped_Bip01_R_Hand*/


