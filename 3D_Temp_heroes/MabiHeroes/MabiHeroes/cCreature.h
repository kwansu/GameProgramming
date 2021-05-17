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
		STATE_NORMAL,			/* �⺻ ���� */
		STATE_MOVE,				/* �ȱ� ���� */
		STATE_RUN,				/* �ٱ� ���� */
		STATE_ATTACK,			/* ���� ���� */
		STATE_KNOCKBACK,		/* �˹� ���� */
		STATE_TIRED,			/* ���� ���� */
		STATE_ROLLRUN,			/* ������ ���� */
		STATE_KNOCKDOWN,		/* ������ ���� */
		STATE_DOWNUP,			/* �Ͼ�� ���� */
		STATE_DEATH				/* ���� ���� */
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

	// �浹 �����
	map<string, ST_COLLISION_BOX_STICK>	m_mapHitBox;
	vector<ST_COLLISION_BOX_STICK>		m_vecAttackBox;

	vector<cGameObject*>				m_vecHitList;
	ST_SPHERE							m_stBoundingSphere;
	D3DXVECTOR3							m_vVelocity;
	// �̵��� ����ϴ� ĸ���� �������� ����, ���߿� �����Ǹ� ����ü������ ���� ��.
	float								m_fMoveRadius;
	float								m_fMoveHeight;
	bool								m_isPhysics;

	// �ִϸ��̼� ó�� ������
	bool								m_isAttackEnable;
	bool								m_isEnableReserve;
	float								m_fAniSpeed;
	float								m_fReserveChangeRate;
	float								m_fAttackStartRate;
	float								m_fAttackEndRate;
	vector<ST_HitAttack>				m_vecHitAttack;

	// ���� �ִϸ��̼ǰ� ���� �ִϸ��̼�, �ٸ��� �ִϸ��̼� ��ü�Լ� �߻�.
	int									m_nAniCurrentState;
	int									m_nAniPrevIndexState;
	int									m_nAniReserveState;

	//ü�� �� ���¹̳�
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
	// �ִϸ��̼��� ������ ������ �̿��ϴ� �Լ���
	virtual void AnimationRateProcess();
	virtual void AnimationRateProcessLocal(float fAniRate) {}
	virtual void AniSituation() {}
	virtual void ReserveAniUpdate(float fAniRate);
	virtual void ShiftMoveUpdate(float fAniRate);
	virtual void HitAttackUpdate(float fAniRate);
	virtual void Slicing() {}

public:
	virtual void SetShiftMove(D3DXVECTOR3& vShiftDir, float fPower, float fStartRate, float fEndRate);
	// ���ݽ� ��Ʈ ���� �ð��� ���Ѵ�. pHitBox = ������ �κ�, Rate = �ִϸ��̼��� ���۰� ���� 
	virtual void SetEnableHitAttack(char* szBoxName, float fDamage, bool isSmash, float fStartRate, float fEndRate);
	virtual void SetEnableHitAttack(int n, float fDamage, bool isSmash, float fStartRate, float fEndRate, float fScale = 1);
	virtual void SetReserveAnimation(int nReserveAni, float fChangeRate = 0.9f, float fAniSpeed = 1.0f);

	// AI�� �Լ�
	virtual bool IsAttacking() { return false; }

	// ��Ʈ �ڽ� ����
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