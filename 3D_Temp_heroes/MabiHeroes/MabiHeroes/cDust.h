
#pragma once
#define DUST_ALPHA_ELLIPSE_DECREASE			5
#define DUST_ALPHA_SPTAY_DECREASE			3
#define SLASH_ALPHA_DECREASE				10
#define DUST_ELLIPS_NUM						10
#define DUST_SPRAY_NUM						15
#define SLASH_LINE_NUM						2
#define WIND_LINE_NUM						10


enum eEFFECT_NUM
{
	DUST_ELLIPS,							// 0          
	DUST_SPRAY,								// 1         
	SLASH_LINE,								// 2         
	SWING_LINE,								// 3        // 다른 개념의 이펙트 ( 여기서 그리거나 작업하지 않음)
	WIND_ELLIPSE,							// 4         
	WIHD_LINE,								// 5         
	WIND_ELLIPSELINE,						// 6         
	WIND_KCIK,								// 7         
	WIND_PELLIPSE,							// 8         
	WIND_PELLIPSELINE,						// 9         
	YELLOW_RING,							// 10       // 방돌 시작이펙트 
	COUNT_ATK,								// 11		// 카운터 어텍.
	DUST,									// 12		// 흙먼지 기본 


	FIRE_BALL_EGG,							// 13
	FIRE_CLOUDE,							// 14
	FIRE_Tail,								// 15
	BLAST,									// 16
	BLAST_DUST,								// 17
	BLAST_CLOUD,							// 18
};

struct stEffcet
{
	vector<ST_PCT_VERTEX>	m_vecVertex;

	D3DXMATRIXA16*			m_pmatParent;
	D3DXMATRIXA16			m_matWorld;
	D3DXMATRIXA16			m_matSaveWorld;
	D3DXMATRIXA16*			m_pmatSaveWorld;


	D3DXMATRIXA16			m_matR;


	D3DXVECTOR3				m_vPos;
	D3DXVECTOR3*			m_pVPos;
	D3DXVECTOR3				m_vMoveDir;

	int						m_fAlpha;
	float					m_fDecreaseAlpha;
	float					m_fLifeCount;
	float					m_fSprayPower;
	float					m_fGravity;
	bool					m_bLife;
	bool					m_isRedCircle;

	D3DXVECTOR3				m_vScale;
	D3DXVECTOR3				m_vIncreaseScale;
	D3DXVECTOR3				m_vDecreaseScale;
	D3DXVECTOR3				m_vRotation;
	D3DXVECTOR3				m_vAngle;

	eEFFECT_NUM				m_EffectNum;

	D3DXVECTOR3				m_vecOffeSet;

	/////////// wind Ellipse ////////////
	vector<LPD3DXMESH>		m_vWind;
	int						m_nStage;
	float					m_fRoolSpeed;
	LPD3DXMATERIAL			m_arrMtl[2];
	float					m_fMaxSize;
	/////////// wind Line ///////////////
	float					m_fStartRadius;
	float					m_MoveSpeed;
	///////////FierBallEgg///////////////
	D3DXVECTOR3				m_vecTarget;
	float					m_fTarget;
	D3DXVECTOR3				m_vetStartPos;
	/////////////////////////////////////

	stEffcet()
	{
		ST_PCT_VERTEX tempVetex;
		D3DXMATRIX matRX, matRY, matRZ, matWorld;
		m_vScale = D3DXVECTOR3(1, 1, 1);
		D3DXMatrixIdentity(&m_matWorld);
		D3DXMatrixIdentity(&m_matSaveWorld);
		D3DXMatrixIdentity(&m_matR);
		m_isRedCircle = false;
		m_bLife = true;
		m_fAlpha = 255;
		m_fSprayPower = 0.f;
		m_fGravity = 0.f;
		m_pmatParent = NULL;
		m_nStage = 0.f;
		m_vAngle = { 0, 0, 0 };
		m_vPos = { 0, 0, 0 };
		m_vMoveDir = { 0, 0, 0 };
		m_fStartRadius = 0.f;
		m_vScale = { 1, 1, 1 };
		m_vecOffeSet = { 0, 0, 0 };
		m_vIncreaseScale = m_vDecreaseScale = { 0, 0, 0 };
		m_MoveSpeed = 0.f;
		m_fRoolSpeed = m_fTarget = 0.f;
		m_fDecreaseAlpha = 0;
		m_vecTarget = { 0, 0, 0 };
		m_vetStartPos = { 0, 0, 0 };
		m_pVPos = NULL;


	}

	void CreateEllipseDust(float fRadius, D3DXMATRIXA16* matWorld);

	void CreateSprayDust(D3DXVECTOR3 vPos, D3DXVECTOR3 vMoveDir, float fSparyPower = 0.f);	//	sprayPower Max = 29.99f;

	void CreateSlashLine(D3DXVECTOR3 vPos, float fAngle, D3DXMATRIXA16* matR = NULL);

	void CreateWindEllipse(D3DXVECTOR3 vecScaling, cSkinnedMesh* pMesh1, cSkinnedMesh* pMesh2, D3DXVECTOR3 offset, float maxsize = 2, D3DXMATRIXA16 * matR = NULL);

	void CreateWindEllipseLine(D3DXVECTOR3 vecScaling, cSkinnedMesh* pMesh1, cSkinnedMesh* pMesh2, D3DXVECTOR3 offset, float maxsize = 2, D3DXMATRIXA16 * matR = NULL);

	void CreatePWindEllipse(D3DXVECTOR3 vecScaling, cSkinnedMesh* pMesh1, cSkinnedMesh* pMesh2, D3DXVECTOR3 offset, float maxsize = 2, D3DXMATRIXA16 * matR = NULL);

	void CreatePWindEllipseLine(D3DXVECTOR3 vecScaling, cSkinnedMesh* pMesh1, cSkinnedMesh* pMesh2, D3DXVECTOR3 offset, float maxsize = 2, D3DXMATRIXA16 * matR = NULL);

	void CreateWindKick(D3DXVECTOR3 vecScaling, cSkinnedMesh* pMesh1, cSkinnedMesh* pMesh2, D3DXVECTOR3 offset, D3DXMATRIXA16 * matR = NULL);

	void CreateWindLine(float fAngle, D3DXMATRIXA16* matR = NULL);

	void CreateYellowRing(D3DXMATRIXA16 * matR, float fSize = 1.f);

	void CreateDust(D3DXVECTOR3 vecPos, float fSize = 1.f, D3DXVECTOR3 vecScalling = { 1, 1, 1 }, float fAlphaDeCreasingRate = 1.f, D3DXVECTOR3 moveDir = { 0, 0, 0 });					// 기본 먼지

	void CreateCountAtk(D3DXVECTOR3 vecScaling, cSkinnedMesh* pMesh1, cSkinnedMesh* pMesh2, cSkinnedMesh* pMesh3, cSkinnedMesh* pMesh4, D3DXVECTOR3 offset, bool bIsRedCircle = false, float maxsize = 2, D3DXMATRIXA16 * matR = NULL);

	void CreateFireBallEgg(D3DXVECTOR3* pvecPos, float fLifeTime, float Size = 0.f);
	void CreateFireCloude(D3DXVECTOR3 vecPos, float fMaxsize = 1.f);
	void CreateFireTail(D3DXVECTOR3 vecPos, float fStartsize = 1.f);
	void CreateBlast(D3DXVECTOR3 vecPos, float fStartsize = 1.f);
	void CreateBlastDust(D3DXVECTOR3 vecPos, float fStartsize = 1.f);
	void CreateBlastCloude(D3DXVECTOR3 vecPos, float fStartsize = 1.f);

	void UpdateAlpha()
	{
		int size = 0;
		switch (m_EffectNum)
		{
		case DUST_ELLIPS:
			if (m_fAlpha < DUST_ALPHA_ELLIPSE_DECREASE + 1)
				m_bLife = false;

			m_fAlpha -= DUST_ALPHA_ELLIPSE_DECREASE;
			size = m_vecVertex.size();
			for (int i = 0; i < size; ++i)
			{
				m_vecVertex[i].c = D3DCOLOR_ARGB(m_fAlpha, 255, 212, 212);
			}
			break;

		case DUST_SPRAY:
			if (m_fAlpha < DUST_ALPHA_SPTAY_DECREASE + 1)
				m_bLife = false;

			m_fAlpha -= DUST_ALPHA_SPTAY_DECREASE;
			size = m_vecVertex.size();
			for (int i = 0; i < size; ++i)
			{
				m_vecVertex[i].c = D3DCOLOR_ARGB(m_fAlpha, 255, 212, 212);
			}
			break;
		case SLASH_LINE:
			if (m_fAlpha < SLASH_ALPHA_DECREASE + 1)
				m_bLife = false;

			m_fAlpha -= SLASH_ALPHA_DECREASE;
			size = m_vecVertex.size();
			for (int i = 0; i < size; ++i)
			{
				m_vecVertex[i].c = D3DCOLOR_ARGB(m_fAlpha, 255, 212, 212);
			}
			break;
		case YELLOW_RING:
			if (m_fAlpha < SLASH_ALPHA_DECREASE + 1)
				m_bLife = false;

			m_fAlpha -= SLASH_ALPHA_DECREASE;
			size = m_vecVertex.size();
			for (int i = 0; i < size; ++i)
			{
				m_vecVertex[i].c = D3DCOLOR_ARGB(m_fAlpha, 255, 212, 212);
			}
			break;
		case DUST:
			if (m_fAlpha < m_fDecreaseAlpha + 1)
				m_bLife = false;

			m_fAlpha -= m_fDecreaseAlpha;
			size = m_vecVertex.size();
			for (int i = 0; i < size; ++i)
			{
				m_vecVertex[i].c = D3DCOLOR_ARGB(m_fAlpha, m_fAlpha, m_fAlpha, m_fAlpha);
			}
			break;
		}

	}
	void Update();




};





class cDust
{
private:

	vector<stEffcet>					m_vDust;
	vector<stEffcet>::iterator			m_viDust;



public:
	cDust();
	~cDust();

	void Setup(eEFFECT_NUM eDustNum);
	vector<stEffcet>* GetVEffect() { return &m_vDust; }

	void CreateEllipseDust(D3DXMATRIXA16* matWorld);
	void CreateSprayDust(D3DXMATRIXA16* matWorld, D3DXVECTOR3 sprayDir, float fPower = 0.f);
	void CreateSlashLine(D3DXVECTOR3 vPos, float fAngle, D3DXMATRIXA16* matR = NULL);
	void CreateWindEllipse(D3DXVECTOR3 vecScaling, cSkinnedMesh* pMesh1, cSkinnedMesh* pMesh2, D3DXVECTOR3 offset, float maxSize = 2, D3DXMATRIXA16* matR = NULL);
	void CreateWindEllipseLine(D3DXVECTOR3 vecScaling, cSkinnedMesh* pMesh1, cSkinnedMesh* pMesh2, D3DXVECTOR3 offset, float maxSize = 2, D3DXMATRIXA16* matR = NULL);
	void CreatePWindEllipse(D3DXVECTOR3 vecScaling, cSkinnedMesh* pMesh1, cSkinnedMesh* pMesh2, D3DXVECTOR3 offset, float maxSize = 2, D3DXMATRIXA16* matR = NULL);
	void CreatePWindEllipseLine(D3DXVECTOR3 vecScaling, cSkinnedMesh* pMesh1, cSkinnedMesh* pMesh2, D3DXVECTOR3 offset, float maxSize = 2, D3DXMATRIXA16* matR = NULL);
	void CreateWindKick(D3DXVECTOR3 vecScaling, cSkinnedMesh* pMesh1, cSkinnedMesh* pMesh2, D3DXVECTOR3 offset, D3DXMATRIXA16* matR = NULL);
	void CreateWindLine(float fAngle, D3DXMATRIXA16* matR = NULL);
	void CreateYellowRing(D3DXMATRIXA16 * matR, float fSize = 1.f);

	void CreateDust(D3DXVECTOR3 vecPos, float fSize = 1.f, D3DXVECTOR3 vecScalling = { 1, 1, 1 }, float fAlphaDeCreasingRate = 1.f, D3DXVECTOR3 moveDir = { 0, 0, 0 });

	void CreateFireBallEgg(D3DXVECTOR3* pvecPos, float fLifeTime, float Size = 0.f);
	void CreateFireTail(D3DXVECTOR3 vecPos, float fStartsize = 1.f);

	void CreateFireCloude(D3DXVECTOR3 vecPos, float fMaxsize = 1.f);

	void CreateBlast(D3DXVECTOR3 vecPos, float fStartsize = 1.f);
	void CreateBlastDust(D3DXVECTOR3 vecPos, float fStartsize = 1.f);
	void CreateBlastCloude(D3DXVECTOR3 vecPos, float fStartsize = 1.f);

	void Update();
	void Render();
	void Release();


	void CreateCountAtk(D3DXVECTOR3 vecScaling, cSkinnedMesh* pMesh1, cSkinnedMesh* pMesh2, cSkinnedMesh* pMesh3, cSkinnedMesh* pMesh4, D3DXVECTOR3 offset, bool bIsRedCircle = false, float maxsize = 2, D3DXMATRIXA16 * matR = NULL);


	void Billboard(D3DXMATRIXA16* inoutMat, D3DXMATRIXA16* matView);


};

