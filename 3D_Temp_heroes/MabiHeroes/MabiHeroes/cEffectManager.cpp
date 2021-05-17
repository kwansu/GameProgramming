#include "stdafx.h"
#include "cEffectManager.h"
#include "cSparkParticle.h"
#include "cDust.h"
#include "cSwing.h"


DWORD FtoDw(float f)
{
	return *((DWORD*)&f);
}

cEffectManager::cEffectManager()
{
	m_aaaaaa = 0.f;
	m_isYellowRing = m_bisFireBall = false;
	fTime = 0.f;
	m_vecTestPos = { 0, 0, 0 };
	m_pSwing = new cSwing;

	ST_SPHERE temp;
	m_pCireleWindMesh[0] = new cSkinnedMesh;
	m_pCireleWindMesh[0]->Load("./EffectImage/", "OUT.X", temp);
	m_pCireleWindMesh[1] = new cSkinnedMesh;
	m_pCireleWindMesh[1]->Load("./EffectImage/", "IN.X", temp);
	m_pCireleWindMesh[2] = new cSkinnedMesh;
	m_pCireleWindMesh[2]->Load("./EffectImage/", "windfootOut.X", temp);
	m_pCireleWindMesh[3] = new cSkinnedMesh;
	m_pCireleWindMesh[3]->Load("./EffectImage/", "windfootIn.X", temp);


	m_pCireleWindMesh[4] = new cSkinnedMesh;
	m_pCireleWindMesh[4]->Load("./EffectImage/", "count1Out.X", temp);
	m_pCireleWindMesh[5] = new cSkinnedMesh;
	m_pCireleWindMesh[5]->Load("./EffectImage/", "count1In.X", temp);
	m_pCireleWindMesh[6] = new cSkinnedMesh;
	m_pCireleWindMesh[6]->Load("./EffectImage/", "count2Out.X", temp);
	m_pCireleWindMesh[7] = new cSkinnedMesh;
	m_pCireleWindMesh[7]->Load("./EffectImage/", "count2In.X", temp);
}


cEffectManager::~cEffectManager()
{
}

void cEffectManager::Setup()
{
	// 포인트에 텍스쳐를 입힐 수 있게 해줌
	g_pD3DDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, true);

	// 포인트를 확대 축소 할 수 있게 해줌
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE, true);

	// 포인트 사이즈 설정
	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE, FtoDw(0.2f));

	// 포인트 스케일링 Factor값 설정
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_A, FtoDw(0.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_B, FtoDw(0.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_C, FtoDw(1.0f));

	g_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// 텍스쳐 알파 옵션 설정
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	// 포인트 최소 크기
	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE_MIN, FtoDw(0.0f));

	// 포인트 최대 크기
	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE_MAX, FtoDw(100.0f));
}

void cEffectManager::Update()
{
	fTime += g_fDeltaTime;

	if (g_pKeyManager->IsOnceKeyDown(VK_NUMPAD1))
	{
		//D3DXMATRIXA16 tempMat;
		//D3DXMatrixIdentity(&tempMat);
		//tempMat._42 = 10.f;
		//this->CreateEllipseDust(&tempMat);
		D3DXMATRIXA16 tempMatR;
		D3DXMatrixIdentity(&tempMatR);
		D3DXMatrixRotationZ(&tempMatR, D3DXToRadian(90));
		this->CreateCountAtk(D3DXVECTOR3(0.1f, 0.1f, 0.1f), D3DXVECTOR3(0, 0, 0),true, 1, &tempMatR);

		//this->CreateFireCloude({ 0, 0, 0 }, 5);
		//this->CreateFireTail({ 0, 0, 0 }, 5);
	}
	else if (g_pKeyManager->IsOnceKeyDown(VK_NUMPAD2))
	{
		//D3DXMATRIXA16 tempMat;
		//D3DXMatrixIdentity(&tempMat);
		//tempMat._42 = 10.f;
		//this->CreateSprayDust(&tempMat, D3DXVECTOR3(0, 0, 1), 0.f);
	}
	else if (g_pKeyManager->IsOnceKeyDown(VK_NUMPAD3))
	{
		//D3DXVECTOR3 vecTemp = { 0, 10, 0 };
		//this->CreateSlashLine(vecTemp, 0.f);
	}
	else if (g_pKeyManager->IsOnceKeyDown(VK_NUMPAD4))
	{
		m_pSwing->AddSwing("aa", D3DXVECTOR3(m_aaaaaa, 1, 0), D3DXVECTOR3(m_aaaaaa, -1, 0));
		++m_aaaaaa;
	}
	else if (g_pKeyManager->IsOnceKeyDown(VK_NUMPAD5))
	{
		this->CreateWindLine(0.f);
	}
	else if (g_pKeyManager->IsOnceKeyDown(VK_NUMPAD9))
	{
		this->CreateCountAtk(D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(0, 0, 0));
	}
	else if (g_pKeyManager->IsOnceKeyDown(VK_NUMPAD8))
	{
		this->CreateWindEllipseLine(D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(0, 0, 0));
	}
	else if (g_pKeyManager->IsOnceKeyDown(VK_NUMPAD7))
	{
		this->CreateWindKick(D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(0, 0, 0));
	}
	else if (g_pKeyManager->IsOnceKeyDown(VK_NUMPAD6))
	{
		D3DXMATRIXA16 tempWorld;
		D3DXMatrixIdentity(&tempWorld);
		this->CreateYellowRing(&tempWorld, 10);
	}
	else if (g_pKeyManager->IsOnceKeyDown(VK_NUMPAD0))
	{
		this->CreateFireBallEgg(5.f, &m_vecTestPos, 2.f);
		m_bisFireBall = true;

	}


	m_pSwing->Update();


	
	for each(const auto& p in m_vSparkParticle)
	{
		p->Update();
	}

	if(m_bisFireBall)
		m_vecTestPos.x += 0.1f;

	for (m_viSparkParticle = m_vSparkParticle.begin(); m_viSparkParticle != m_vSparkParticle.end();)
	{
		if ((*m_viSparkParticle)->GetVEffect()->size() == 0)
			m_viSparkParticle = m_vSparkParticle.erase(m_viSparkParticle);
		else
			++m_viSparkParticle;
	}
	if (fTime >= 0.07f)
	{
		int size = m_vSparkParticle.size();
		for (int i = 0; i < size; ++i)
		{
			if ((*(*m_vSparkParticle[i]).GetVEffect()).size() && (*(*m_vSparkParticle[i]).GetVEffect())[0].m_EffectNum == 13)
			{
				stEffcet temp = (*(*m_vSparkParticle[i]).GetVEffect())[0];
				D3DXVECTOR3 ballPos;
				if (*temp.m_pVPos == NULL)
					ballPos = { 0, 0, 0 };
				else
					ballPos = *temp.m_pVPos;
				this->CreateFireCloude(ballPos, temp.m_vScale.x);
				this->CreateFireTail(ballPos, temp.m_vScale.x);
			}
		}
		fTime -= 0.07f;
	}
}

void cEffectManager::Render()
{
	for each(const auto& p in m_vSparkParticle)
		p->Render();

	m_pSwing->Reder();
}

void cEffectManager::CreateEffect(eEFFECT_NUM Dustnum)
{
	cDust* pDust = new cDust;
	pDust->Setup(Dustnum);
	m_vSparkParticle.push_back(pDust);


}
void cEffectManager::CreateEllipseDust(D3DXMATRIXA16 * pMat)
{
	cDust* pDust = new cDust;
	pDust->CreateEllipseDust(pMat);
	m_vSparkParticle.push_back(pDust);
}

void cEffectManager::CreateSprayDust(D3DXMATRIXA16 * pMat, D3DXVECTOR3 sprayDir, float Power)
{
	cDust* pDust = new cDust;
	pDust->CreateSprayDust(pMat, sprayDir, Power);
	m_vSparkParticle.push_back(pDust);
}

void cEffectManager::CreateSlashLine(D3DXVECTOR3 vPos, float fAngle, D3DXMATRIXA16 * matR)
{
	cDust* pDust = new cDust;
	pDust->CreateSlashLine(vPos, fAngle, matR);
	m_vSparkParticle.push_back(pDust);
}

void cEffectManager::CreateWindEllipse(D3DXVECTOR3 vecScaling, D3DXVECTOR3 offset, float maxSize, D3DXMATRIXA16 * matR)
{
	cDust* pDust = new cDust;
	pDust->CreateWindEllipse(vecScaling, m_pCireleWindMesh[0], m_pCireleWindMesh[1], offset, maxSize, matR);
	m_vSparkParticle.push_back(pDust);
}
void cEffectManager::CreatePWindEllipse(D3DXVECTOR3 vecScaling, D3DXVECTOR3 offset, float maxSize, D3DXMATRIXA16 * matR)
{
	cDust* pDust = new cDust;
	pDust->CreatePWindEllipse(vecScaling, m_pCireleWindMesh[0], m_pCireleWindMesh[1], offset, maxSize, matR);
	m_vSparkParticle.push_back(pDust);
}

void cEffectManager::CreateWindEllipseLine(D3DXVECTOR3 vecScaling, D3DXVECTOR3 offset, float maxSize, D3DXMATRIXA16 * matR)
{
	cDust* pDust = new cDust;
	pDust->CreateWindEllipseLine(vecScaling, m_pCireleWindMesh[0], m_pCireleWindMesh[1], offset, maxSize, matR);
	m_vSparkParticle.push_back(pDust);
}
void cEffectManager::CreatePWindEllipseLine(D3DXVECTOR3 vecScaling, D3DXVECTOR3 offset, float maxSize, D3DXMATRIXA16 * matR)
{
	cDust* pDust = new cDust;
	pDust->CreatePWindEllipseLine(vecScaling, m_pCireleWindMesh[0], m_pCireleWindMesh[1], offset, maxSize, matR);
	m_vSparkParticle.push_back(pDust);
}

void cEffectManager::CreateWindKick(D3DXVECTOR3 vecScaling, D3DXVECTOR3 offset, D3DXMATRIXA16 * matR)
{
	cDust* pDust = new cDust;
	pDust->CreateWindKick(vecScaling, m_pCireleWindMesh[2], m_pCireleWindMesh[3], offset, matR);
	m_vSparkParticle.push_back(pDust);
}



void cEffectManager::CreateWindLine(float fAngle, D3DXMATRIXA16 * matR)
{
	cDust* pDust = new cDust;
	pDust->CreateWindLine(fAngle, matR);
	m_vSparkParticle.push_back(pDust);
}

void cEffectManager::CreateYellowRing(D3DXMATRIXA16 * matR, float fSize)
{
	m_isYellowRing = true;
	cDust* pDust = new cDust;
	pDust->CreateYellowRing(matR, fSize);
	m_vSparkParticle.push_back(pDust);
}

void cEffectManager::CreateFireBallEgg(float fLifeTime, D3DXVECTOR3* pvecPos, float size)
{
	cDust* pDust = new cDust;
	pDust->CreateFireBallEgg(pvecPos, fLifeTime, size);
	m_vSparkParticle.push_back(pDust);

}

void cEffectManager::CreateFireCloude(D3DXVECTOR3 vecPos, float fMaxsize)
{
	cDust* pDust = new cDust;
	pDust->CreateFireCloude(vecPos, fMaxsize);
	m_vSparkParticle.push_back(pDust);
}

void cEffectManager::CreateFireTail(D3DXVECTOR3 vecPos, float fStartsize)
{
	cDust* pDust = new cDust;
	pDust->CreateFireTail(vecPos, fStartsize);
	m_vSparkParticle.push_back(pDust);
}

void cEffectManager::CreateBlast(D3DXVECTOR3 vecPos, float fStartsize)
{
	cDust* pDust = new cDust;
	pDust->CreateBlast(vecPos, fStartsize);
	m_vSparkParticle.push_back(pDust);
}

void cEffectManager::CreateBlastDust(D3DXVECTOR3 vecPos, float fStartsize)
{
	cDust* pDust = new cDust;
	pDust->CreateBlastDust(vecPos, fStartsize);
	m_vSparkParticle.push_back(pDust);
}

void cEffectManager::CreateBlastCloude(D3DXVECTOR3 vecPos, float fStartsize)
{
	cDust* pDust = new cDust;
	pDust->CreateBlastCloude(vecPos, fStartsize);
	m_vSparkParticle.push_back(pDust);
}


void cEffectManager::AddSwingEffect(string CreatureName, D3DXVECTOR3 Up, D3DXVECTOR3 Down, bool isWhite)
{
	m_pSwing->AddSwing(CreatureName, Up, Down, isWhite);
}

void cEffectManager::CreateDust(D3DXVECTOR3 vecPos, float fSize, D3DXVECTOR3 vecScallingRate, float fAlphaDeCreasingRate, D3DXVECTOR3 moveDir)
{
	cDust* pDust = new cDust;
	pDust->CreateDust(vecPos, fSize, vecScallingRate, fAlphaDeCreasingRate, moveDir);
	m_vSparkParticle.push_back(pDust);
}

void cEffectManager::CreateCountAtk(D3DXVECTOR3 vecScaling, D3DXVECTOR3 offset, bool isRedCircle, float maxSize, D3DXMATRIXA16 * matR)
{
	cDust* pDust = new cDust;
	pDust->CreateCountAtk(vecScaling, m_pCireleWindMesh[4], m_pCireleWindMesh[5], m_pCireleWindMesh[6], m_pCireleWindMesh[7], offset, isRedCircle, maxSize, matR);
	m_vSparkParticle.push_back(pDust);
}
