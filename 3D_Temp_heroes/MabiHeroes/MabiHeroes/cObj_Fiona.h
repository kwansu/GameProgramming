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

enum FIONA_ANI_STATE				//애니메이션 순서(후입선출)
{									//0번부터~ 시작
/*0*/		PALADIN_TRANSFORM,		//팔라딘 변신
			POTION_BEGIN,			//포션 시작
			POTION_DURING,			//포션 빠는 중
			POTION_END,				//포션 다 빨고 준비 동작
			DASH_ATTACK,			//돌격 우 클릭, 대쉬 공격
/*5*/		TIRED_BEGIN,			//스태미나 부족, 피곤시작
			TIRED_DURING,			//스태미나 부족, 피곤 중	
			TIRED_END,				//스태미나 부족, 피곤 끝
			TIRED_RUN,				//스태미나 부족, 피곤한 뛰기
			FALLING,				//낙하
/*10*/		FALLING_DURING,			//낙하 중
			FALLING_SAFE,			//낙하 안전 착지
			FALLING_DAMAGE,			//낙하 데미지 착지,
			COUNTER_ATTACK,			//스킬2, 방어동작, 반격 카운트 공격
			SP_SHIELD_ASSAULT,		//스킬1, 방패돌격(Z키)
/*15*/		DAMAGE_STRONG_FRONT,	//강 앞 피격, 뒤로 굴러감
			DAMAGE_STRONG_BACK,		//강 뒤 피격, 앞으로 구름
			DASH_RUNNING,			//스페이스바, 앞구르기 대쉬
			DAMAGE_MIDDLE_BEGIN,	//중 앞공격, 시작모션
			DAMAGE_MIDDLE_DURING,	//중 앞공격, 뒤로 밀리면서 땅에 무릎꿇고 있는 연속동작
/*20*/		DAMAGE_MIDDLE_END,		//중 앞공격, 무릎꿇은 상태에서 일어서는 동작
			GUARD_HIT,				//우 클릭, 방패막고 찌르기 공격
			COMBO4_SMASH,			//4콤보 후 우 클릭, 스매쉬 공격
			COMBO3A_SMASH,			//3콤보 후 우 클릭, 스매쉬 공격1
			COMBO3B_SMASH,			//3콤보 후 우 클릭, 스매쉬 공격2	//1,2 연계동작
/*25*/		COMBO2_SMASH,			//2콤보 후 우 클릭, 스매쉬 공격
			COMBO1_SMASH,			//1콤보 후 우 클릭, 스매쉬 공격
			GUARD_BEGIN,			//방패막기, 시작모션
			GUARD_DURING,			//방패막기, 막는모션				스페이스바
			GUARD_END,				//방패막기, 중지모션
/*30*/		GUARD_ATTACK,			//방패막기, 찌르기 공격,			우클릭
			DOWN_BACKWARD,			//강 앞 피격, 뒤로 길게 밀림
			DAMAGE_BACK,			//중	 뒤 피격, 앞으로 짧게 밀림
			DAMAGE_FRONT,			//중	 앞 피격, 뒤로 짧게 밀림
			DOWN_BACK_ROLL,			//뒤 누움, 앞 구르기 기상!		엎어져 있을때 이동키
/*35*/		DOWN_BACK_IDLE,			//뒤 누움, 빈둥거림
			DOWN_FRONT_ROLL,		//앞 누움, 앞 구르기 기상!		엎어져 있을때 이동키
			DOWN_FRONT_IDLE,		//앞 누움, 빈둥거림
			ATTACK_COMBO1,			//좌 클릭, 1콤보
			ATTACK_COMBO2,			//좌 클릭, 2콤보					
/*40*/		ATTACK_COMBO3,			//좌 클릭, 3콤보
			ATTACK_COMBO4,			//좌 클릭, 4콤보
			RUNNING_LOWER,			//논 쉬프트, 가벼운 구보
			RUNNING_SPRINT,			//쉬프트 키, 돌격
			RUNNING_STOP,			//가속도의 법칙, 정지 모션!
/*45*/		STANDING_IDLE			//서서, 빈둥거림
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

	int					m_nCurrentAnim; // 애니메이션 확인용.
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
	// 공격 확인용
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

	//카메라가 양수로 회전할 경우 true, 반대는 false, fCos는 캠과 피오나의 사이각
	bool GetDistanceAngle(float camY, OUT float& fCos);

	bool IsAttacking() override;
	virtual void AnimationRateProcessLocal(float fAniRate) override;


	void Effect();
};