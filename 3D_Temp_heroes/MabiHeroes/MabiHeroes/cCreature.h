#pragma once
#include "cGameObject.h"
#include "cWearItem.h"

class cSkinnedMesh;
class cWorld;

#define fGRAVITY	2.f

class cCreature : public cGameObject
{
	friend class cWorld;
	friend class cEditScene;

protected:
	enum eCreatureState
	{
		STATE_NORMAL,			/* 기본 상태 */
		STATE_MOVE,				/* 걷기 상태 */
		STATE_RUN,				/* 뛰기 상태 */
		STATE_ATTACK,			/* 공격 상태 */
		STATE_KNOCKBACK,		/* 넉백 상태 */
		STATE_TIRED,			/* 헥헥 상태 */
		STATE_ROLLRUN,			/* 구르기 상태 */
		STATE_KNOCKDOWN,		/* 쓰러짐 상태 */
		STATE_DOWNUP,			/* 일어나는 상태 */
		STATE_DEATH				/* 죽음 상태 */
	};

	struct ST_ShiftMove
	{
		bool		bIsShift;
		D3DXVECTOR3 vShiftDir;
		float		fPower;
		float		fPrevRate;
		float		fStartRate;
		float		fEndRate;
		float		fPrevMovement;
		ST_ShiftMove()
		{
			bIsShift = false;
			vShiftDir = D3DXVECTOR3(0, 0, 0);
			fPower = 0.f;
			fStartRate = 0.f;
			fEndRate = 0.f;
		}
	};

	struct ST_HitAttack
	{
		bool					isActive;
		bool					isSmash;
		float					fStartRate;
		float					fEndRate;
		float					fDamage;
		float					fScale;
		ST_COLLISION_BOX_STICK*	pHitBox;
	};

protected:
	cSkinnedMesh*	m_pMesh;


	D3DXMATRIXA16	m_matOrigin;
	eCreatureState	m_pState;

	ST_ShiftMove	m_stShiftMove;

	// 충돌 실험용
	map<string, ST_COLLISION_BOX_STICK>	m_mapHitBox;
	vector<ST_COLLISION_BOX_STICK>		m_vecAttackBox;

	vector<cGameObject*>				m_vecHitList;
	ST_SPHERE							m_stBoundingSphere;
	D3DXVECTOR3							m_vVelocity;
	// 이동시 사용하는 캡슐의 반지름과 길이, 나중에 정립되면 구조체등으로 묶을 것.
	float								m_fMoveRadius;
	float								m_fMoveHeight;
	bool								m_isPhysics;

	// 애니메이션 처리 변수들
	bool								m_isAttackEnable;
	bool								m_isEnableReserve;
	float								m_fAniSpeed;
	float								m_fReserveChangeRate;
	float								m_fAttackStartRate;
	float								m_fAttackEndRate;
	vector<ST_HitAttack>				m_vecHitAttack;

	// 현재 애니메이션과 예약 애니메이션, 다르면 애니메이션 교체함수 발생.
	int									m_nAniCurrentState;
	int									m_nAniPrevIndexState;
	int									m_nAniReserveState;

	//체력 및 스태미너
	int									m_nHp;
	int									m_nStamina;

public:
	cCreature();
	virtual ~cCreature() = 0;
	void Setup() override;
	void Update() override;
	void Render() override;

	virtual void SetupCreature() {}
	virtual void UpdateCreature() {}
	virtual void RenderCreature() {}
	virtual void ReleaseCreature() {}

private:
	// 애니메이션의 포지션 비율을 이용하는 함수들
	virtual void AnimationRateProcess();
	virtual void AnimationRateProcessLocal(float fAniRate) {}
	virtual void AniSituation() {}
	virtual void ReserveAniUpdate(float fAniRate);
	virtual void ShiftMoveUpdate(float fAniRate);
	virtual void HitAttackUpdate(float fAniRate);
	virtual void Slicing() {}

public:
	virtual void SetShiftMove(D3DXVECTOR3& vShiftDir, float fPower, float fStartRate, float fEndRate);
	// 공격시 히트 공격 시간을 정한다. pHitBox = 공격할 부분, Rate = 애니메이션의 시작과 끝날 
	virtual void SetEnableHitAttack(char* szBoxName, float fDamage, bool isSmash, float fStartRate, float fEndRate);
	virtual void SetEnableHitAttack(int n, float fDamage, bool isSmash, float fStartRate, float fEndRate, float fScale = 1);
	virtual void SetReserveAnimation(int nReserveAni, float fChangeRate = 0.9f, float fAniSpeed = 1.0f);

	// AI용 함수
	virtual bool IsAttacking() { return false; }

	// 히트 박스 관련
	void CreateAllHitBox();
	void LoadHitBox(char* szFile, const D3DXMATRIXA16& matR);
	void RenderHitBox(const D3DXCOLOR* pColor = NULL);
	void RenderAtkBox(const D3DXCOLOR* pColor = NULL);
	void RenderSphere();
	void DebugRender();

	void CalcShiftMovement(float fAniRate);
	void SetOriginMatrix(const D3DXMATRIXA16& mat);
	void SetPysicsState(bool state) { m_isPhysics = state; }

	

	ST_SPHERE& GetBoundingSphere();
};