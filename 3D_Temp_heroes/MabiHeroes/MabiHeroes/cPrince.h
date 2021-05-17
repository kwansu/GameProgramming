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

	// AI�ൿ
	void AICommand();
	void ActionTrace();

	void Damaged(float fDamege, cGameObject* pAttacker, bool isSmash);
};


enum cPrince::ePRINCE_ANISTATE
{
	���,
	�����ȱ�,
	�ٺ�ó���ٱ�,
	���ʵ���,
	�����ʵ���,
	ü�´ٺ���,
	���̾�����,
	������_��,
	������_����,
	������_������,
	������_����,
	�׷α����,
	�׷α���,
	�׷αⳡ,
	�׳����,
	����ġ��,
	�����޺�2,
	�ι��ֵθ���,
	�ι�������_����,
	�����ει����,
	��Ƽ����ġ��,
	�޼տ÷�ġ��,
	�޼�ó����,		// �޼� ����
	�̻��ϰԿ޼�ġ��,	// ������ ����
	���_����,
	�����ġ��,	// ���ʿ��� �ڵ��� ġ��
	���ġ��_����ũ��XXX,
	���̾1,
	���̾2,
	��յ�����̾,
	��ո�����̾,
	ȸ�����̾,
};
