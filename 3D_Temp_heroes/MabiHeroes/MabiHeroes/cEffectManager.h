#pragma once
#include "cDust.h"

#define g_pEffectManager cEffectManager::GetInstance()

class cSparkParticle;
class cSwing;

class cEffectManager
{
	SINGLETON(cEffectManager);


private:
	vector<cDust*>						m_vSparkParticle;
	vector<cDust*>::iterator			m_viSparkParticle;

	int									m_aaaaaa;

	cSwing*								m_pSwing;
	cSkinnedMesh*						m_pCireleWindMesh[8];
		
	bool								m_isYellowRing;
	float								fTime;

	D3DXVECTOR3							m_vecTestPos;
	bool								m_bisFireBall;

public:

	void Setup();
	void Render();
	void Update();
	bool GetYellowRing() { return m_isYellowRing; }
	void SetYellowRing(bool b) { m_isYellowRing = b; }

	cSkinnedMesh* GetCircleWindMesh(int n) { return m_pCireleWindMesh[n]; }

	float GetTime() { return fTime; }

	void CreateEffect(eEFFECT_NUM Dustnum);
	void CreateEllipseDust(D3DXMATRIXA16* pMat);
	void CreateSprayDust(D3DXMATRIXA16* pMat, D3DXVECTOR3 sprayDir, float Power);
	void CreateSlashLine(D3DXVECTOR3 vPos, float fAngle, D3DXMATRIXA16* matR = NULL);
	void CreateWindEllipse(D3DXVECTOR3 vecScaling, D3DXVECTOR3 offset, float maxSize = 2, D3DXMATRIXA16* matR = NULL);
	void CreatePWindEllipse(D3DXVECTOR3 vecScaling, D3DXVECTOR3 offset, float maxSize = 2, D3DXMATRIXA16* matR = NULL);
	void CreateWindEllipseLine(D3DXVECTOR3 vecScaling, D3DXVECTOR3 offset, float maxSize = 2, D3DXMATRIXA16* matR = NULL);
	void CreatePWindEllipseLine(D3DXVECTOR3 vecScaling, D3DXVECTOR3 offset, float maxSize = 2, D3DXMATRIXA16* matR = NULL);
	void CreateWindKick(D3DXVECTOR3 vecScaling, D3DXVECTOR3 offset, D3DXMATRIXA16* matR = NULL);
	void CreateWindLine(float fAngle, D3DXMATRIXA16* matR = NULL);
	void CreateYellowRing(D3DXMATRIXA16 * matR, float fSize = 1.f);
	



	void CreateFireBallEgg(float fLifeTime, D3DXVECTOR3* pvecPos = NULL,  float size = 1.f);
	void CreateFireCloude(D3DXVECTOR3 vecPos, float fMaxsize = 1.f);
	void CreateFireTail(D3DXVECTOR3 vecPos, float fStartsize = 1.f);



	void CreateBlast(D3DXVECTOR3 vecPos, float fStartsize = 1.f);
	void CreateBlastDust(D3DXVECTOR3 vecPos, float fStartsize = 1.f);
	void CreateBlastCloude(D3DXVECTOR3 vecPos, float fStartsize = 1.f);


	void AddSwingEffect(string CreatureName, D3DXVECTOR3 Up, D3DXVECTOR3 Down, bool isWhite = false);





	void CreateDust(D3DXVECTOR3 vecPos, float fSize = 1.f, D3DXVECTOR3 vecScallingRate = { 1, 1, 1 }, float fAlphaDeCreasingRate = 1.f, D3DXVECTOR3 moveDir = { 0, 0, 0 });


	void CreateCountAtk(D3DXVECTOR3 vecScaling, D3DXVECTOR3 offset, bool isRedCircle = false, float maxSize = 2, D3DXMATRIXA16* matR = NULL);
};

