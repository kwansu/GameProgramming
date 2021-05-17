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

	// AI�ൿ
	void AICommand();
	void ActionTrace();
	void ActionStep();
	void ActionMovement();

	void Damaged(float fDamege, cGameObject* pAttacker, bool isSmash);
};


enum cWoodenElf::eWOODEND_ANISTATE
{
	���,
	���ʵ���,
	�����ʵ���,
	����,
	�������,
	�ս���,
	�޽���,
	�޽���,
	��������,
	�ٱ�,
	������_����,
	������_����,
	������_����,
	������_������,
	��������,
	����������,
	�Ͼ��,
	��������,
	������,
	������,
	Ȱ���,
	���⽺��,
	������_��������,
};
