#pragma once
#include "cSkinnedMesh.h"
#include "cCreature.h"

#define RUN_SPEED				50
#define	SPRINT_SPEED			80
#define TIRED_RUN_SPEED			20
#define ROTATE_SPEED			1200
#define STAMINA_CONSUME			70
#define	STAMINA_CONSUME_DODGE	76
#define CAM_ACTION_01			20
#define CAM_ACTIOM_02			10



class cWearItem;
class cProgressBar;
class cQuickSlot;
class cEquipment;

enum FIONA_STATE
{
	IDLE,
	TIRED,
	STOP,
	FALLDOWN,
	POTION_DRINK,
	SPRINT,
	RUNNING,
	ROLL_DASH,
	ATTACK,
	DOWN,
	HIT_DAMEGED,
	GUARD
};

enum FIONA_ANI_STATE				//�ִϸ��̼� ����(���Լ���)
{									//0������~ ����
/*0*/		PALADIN_TRANSFORM,		//�ȶ�� ����
			POTION_BEGIN,			//���� ����
			POTION_DURING,			//���� ���� ��
			POTION_END,				//���� �� ���� �غ� ����
			DASH_ATTACK,			//���� �� Ŭ��, �뽬 ����
/*5*/		TIRED_BEGIN,			//���¹̳� ����, �ǰ����
			TIRED_DURING,			//���¹̳� ����, �ǰ� ��	
			TIRED_END,				//���¹̳� ����, �ǰ� ��
			TIRED_RUN,				//���¹̳� ����, �ǰ��� �ٱ�
			FALLING,				//����
/*10*/		FALLING_DURING,			//���� ��
			FALLING_SAFE,			//���� ���� ����
			FALLING_DAMAGE,			//���� ������ ����,
			COUNTER_ATTACK,			//��ų2, ����, �ݰ� ī��Ʈ ����
			SP_SHIELD_ASSAULT,		//��ų1, ���е���(ZŰ)
/*15*/		DAMAGE_STRONG_FRONT,	//�� �� �ǰ�, �ڷ� ������
			DAMAGE_STRONG_BACK,		//�� �� �ǰ�, ������ ����
			DASH_RUNNING,			//�����̽���, �ձ����� �뽬
			DAMAGE_MIDDLE_BEGIN,	//�� �հ���, ���۸��
			DAMAGE_MIDDLE_DURING,	//�� �հ���, �ڷ� �и��鼭 ���� �����ݰ� �ִ� ���ӵ���
/*20*/		DAMAGE_MIDDLE_END,		//�� �հ���, �������� ���¿��� �Ͼ�� ����
			GUARD_HIT,				//�� Ŭ��, ���и��� ��� ����
			COMBO4_SMASH,			//4�޺� �� �� Ŭ��, ���Ž� ����
			COMBO3A_SMASH,			//3�޺� �� �� Ŭ��, ���Ž� ����1
			COMBO3B_SMASH,			//3�޺� �� �� Ŭ��, ���Ž� ����2	//1,2 ���赿��
/*25*/		COMBO2_SMASH,			//2�޺� �� �� Ŭ��, ���Ž� ����
			COMBO1_SMASH,			//1�޺� �� �� Ŭ��, ���Ž� ����
			GUARD_BEGIN,			//���и���, ���۸��
			GUARD_DURING,			//���и���, ���¸��				�����̽���
			GUARD_END,				//���и���, �������
/*30*/		GUARD_ATTACK,			//���и���, ��� ����,			��Ŭ��
			DOWN_BACKWARD,			//�� �� �ǰ�, �ڷ� ��� �и�
			DAMAGE_BACK,			//��	 �� �ǰ�, ������ ª�� �и�
			DAMAGE_FRONT,			//��	 �� �ǰ�, �ڷ� ª�� �и�
			DOWN_BACK_ROLL,			//�� ����, �� ������ ���!		������ ������ �̵�Ű
/*35*/		DOWN_BACK_IDLE,			//�� ����, ��հŸ�
			DOWN_FRONT_ROLL,		//�� ����, �� ������ ���!		������ ������ �̵�Ű
			DOWN_FRONT_IDLE,		//�� ����, ��հŸ�
			ATTACK_COMBO1,			//�� Ŭ��, 1�޺�
			ATTACK_COMBO2,			//�� Ŭ��, 2�޺�					
/*40*/		ATTACK_COMBO3,			//�� Ŭ��, 3�޺�
			ATTACK_COMBO4,			//�� Ŭ��, 4�޺�
			RUNNING_LOWER,			//�� ����Ʈ, ������ ����
			RUNNING_SPRINT,			//����Ʈ Ű, ����
			RUNNING_STOP,			//���ӵ��� ��Ģ, ���� ���!
/*45*/		STANDING_IDLE			//����, ��հŸ�
};

class cObj_Fiona :
	public cCreature
{
private:


private:
	cProgressBar*		m_pProgressBar;
	cQuickSlot*			m_pQuickSlot;
	cEquipment*			m_pEquipment;

	cSkinnedMesh*		m_pMesh_paladin;
	cSkinnedMesh*		m_pMesh_Shoe;
	cSkinnedMesh*		m_pMesh_Dress;

	FIONA_STATE			m_eCharState;

	int					m_nCurrentAnim; // �ִϸ��̼� Ȯ�ο�.
	int					m_nAniCount;
	int					m_nCounterCount;
	int					m_nSlicingCount;

	float				m_fKeyAngle;
	float				m_fSecTime;
	float				m_fFallingTime;
	
	float				m_fAngle;
	float				m_fAttackRate;

	bool				m_isRun;
	bool				m_isSprint;
	bool				m_isRightTurn;

	vector<cWearItem*>	m_vecWearItem;
	D3DXMATRIXA16*		m_pmatSword;
	D3DXMATRIXA16*		m_pmatSshield;
	ST_Camera_Move		m_stCameraMove;

	D3DXVECTOR3			m_vKeyDir;
	// ���� Ȯ�ο�
	bool				m_isAttacking;
	bool				m_isSound;

	int					m_isNextShiftMove;
	float				m_NextShiftMoveTime;
	D3DXMATRIXA16		m_matSvaeAttackPoint;

	D3DXMATRIXA16		m_matShiledSkill[3];
public:
	cObj_Fiona();
	~cObj_Fiona();

	// cGameObject overrid
	virtual void SetupCreature()	override;
	virtual void UpdateCreature() 	override;
	virtual void RenderCreature() 	override;
	virtual void ReleaseCreature()	override;

	void Controller();
	void AniSituation();
	void Damaged(float fDamege, cGameObject* pAttacker, bool isSmash)	override;
	void DiagonalDir();
	void AttackStart();
	void KeyManager();
	void AttackShiftMove();
	void PaladinTransform();
	void Slicing();
	void ChangeEquip(int index);


	float GetMoveSpeed();

	int GetFionaAniState() { return m_nAniCurrentState; }
	void SetFionaAniState(FIONA_ANI_STATE aniState) { m_nAniCurrentState = aniState; }

	//ī�޶� ����� ȸ���� ��� true, �ݴ�� false, fCos�� ķ�� �ǿ����� ���̰�
	bool GetDistanceAngle(float camY, OUT float& fCos);

	bool IsAttacking() override;
	virtual void AnimationRateProcessLocal(float fAniRate) override;


	void Effect();
};