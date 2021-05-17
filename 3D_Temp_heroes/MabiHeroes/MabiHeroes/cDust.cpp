#include "stdafx.h"
#include "cDust.h"

#define FIRE_BALL_EFFECT_TIME		100.f
#define BLAST_EFFECT_TIME			2.f

cDust::cDust()
{
}


cDust::~cDust()
{
}

void cDust::Setup(eEFFECT_NUM eDustNum)
{
	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
}

void cDust::CreateEllipseDust(D3DXMATRIXA16* matWorld)
{
	for (int i = 0; i < DUST_ELLIPS_NUM; ++i)
	{
		stEffcet  tempDllipseDust;
		tempDllipseDust.CreateEllipseDust(1.f, matWorld);
		m_vDust.push_back(tempDllipseDust);
	}
}

void cDust::CreateSprayDust(D3DXMATRIXA16 * matWorld, D3DXVECTOR3 sprayDir, float fPower)
{
	for (int i = 0; i < DUST_SPRAY_NUM; ++i)
	{
		stEffcet  tempDllipseDust;
		D3DXVECTOR3 vecPos;
		vecPos.x = matWorld->_41;
		vecPos.y = matWorld->_42;
		vecPos.z = matWorld->_43;
		tempDllipseDust.CreateSprayDust(vecPos, sprayDir);
		m_vDust.push_back(tempDllipseDust);
	}
}

void cDust::CreateSlashLine(D3DXVECTOR3 vPos, float fAngle, D3DXMATRIXA16* matR)
{
	D3DXMATRIXA16	matTemp;
	D3DXMatrixIdentity(&matTemp);
	D3DXMatrixTranslation(&matTemp, 0, 10, 0);

	D3DXMATRIXA16 matView;
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matView, 0, &matView);

	D3DXVECTOR3 vecPos;
	vecPos = vPos;

	stEffcet  tempDllipseDust;
	tempDllipseDust.CreateSlashLine(vecPos, fAngle, matR);
	m_vDust.push_back(tempDllipseDust);

}

void cDust::CreateWindEllipse(D3DXVECTOR3 vecScaling, cSkinnedMesh* pMesh1, cSkinnedMesh* pMesh2, D3DXVECTOR3 offset, float maxSize, D3DXMATRIXA16 * matR)
{
	stEffcet newEffect;

	newEffect.m_vAngle.y = float(rand() % 90);
	newEffect.CreateWindEllipse(vecScaling, pMesh1, pMesh2, offset, maxSize, matR);
	m_vDust.push_back(newEffect);
}

void cDust::CreateWindEllipseLine(D3DXVECTOR3 vecScaling, cSkinnedMesh * pMesh1, cSkinnedMesh * pMesh2, D3DXVECTOR3 offset, float maxSize, D3DXMATRIXA16 * matR)
{
	stEffcet newEffect;

	newEffect.m_vAngle.y = float(rand() % 90);
	newEffect.CreateWindEllipseLine(vecScaling, pMesh1, pMesh2, offset, maxSize, matR);
	m_vDust.push_back(newEffect);
}

void cDust::CreatePWindEllipse(D3DXVECTOR3 vecScaling, cSkinnedMesh* pMesh1, cSkinnedMesh* pMesh2, D3DXVECTOR3 offset, float maxSize, D3DXMATRIXA16 * matR)
{
	stEffcet newEffect;

	newEffect.m_vAngle.y = float(rand() % 90);
	newEffect.CreatePWindEllipse(vecScaling, pMesh1, pMesh2, offset, maxSize, matR);
	m_vDust.push_back(newEffect);
}

void cDust::CreatePWindEllipseLine(D3DXVECTOR3 vecScaling, cSkinnedMesh * pMesh1, cSkinnedMesh * pMesh2, D3DXVECTOR3 offset, float maxSize, D3DXMATRIXA16 * matR)
{
	stEffcet newEffect;

	newEffect.m_vAngle.y = float(rand() % 90);
	newEffect.CreatePWindEllipseLine(vecScaling, pMesh1, pMesh2, offset, maxSize, matR);
	m_vDust.push_back(newEffect);
}

void cDust::CreateWindKick(D3DXVECTOR3 vecScaling, cSkinnedMesh * pMesh1, cSkinnedMesh * pMesh2, D3DXVECTOR3 offset, D3DXMATRIXA16 * matR)
{
	stEffcet newEffect;

	newEffect.m_vAngle.y = float(rand() % 90);
	newEffect.CreateWindKick(vecScaling, pMesh1, pMesh2, offset, matR);
	m_vDust.push_back(newEffect);
}

void cDust::CreateCountAtk(D3DXVECTOR3 vecScaling, cSkinnedMesh* pMesh1, cSkinnedMesh* pMesh2, cSkinnedMesh* pMesh3, cSkinnedMesh* pMesh4, D3DXVECTOR3 offset, bool bIsRedCircle, float maxsize, D3DXMATRIXA16 * matR)
{
	stEffcet newEffect;

	newEffect.m_vAngle.y = float(rand() % 90);
	newEffect.CreateCountAtk(vecScaling, pMesh1, pMesh2, pMesh3, pMesh4, offset, bIsRedCircle, maxsize, matR);
	m_vDust.push_back(newEffect);
}

void cDust::CreateWindLine(float fAngle, D3DXMATRIXA16 * pmatWorld)
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	if (pmatWorld)
		matWorld = *pmatWorld;

	stEffcet  tempDllipseDust;
	tempDllipseDust.CreateWindLine(0.f, &matWorld);
	m_vDust.push_back(tempDllipseDust);

}

void cDust::CreateYellowRing(D3DXMATRIXA16 * matR, float fSize)
{
	stEffcet  tempDllipseDust;
	tempDllipseDust.CreateYellowRing(matR, fSize);
	m_vDust.push_back(tempDllipseDust);
}

void cDust::CreateDust(D3DXVECTOR3 vecPos, float fSize, D3DXVECTOR3 vecScalling, float fAlphaDeCreasingRate, D3DXVECTOR3 moveDir)
{
	stEffcet  tempDllipseDust;
	tempDllipseDust.CreateDust(vecPos, fSize, vecScalling, fAlphaDeCreasingRate, moveDir);
	m_vDust.push_back(tempDllipseDust);
}

void cDust::CreateFireBallEgg(D3DXVECTOR3* pvecPos, float fLifeTime, float Size)
{
	stEffcet  tempDllipseDust;
	tempDllipseDust.CreateFireBallEgg(pvecPos, fLifeTime, Size);
	m_vDust.push_back(tempDllipseDust);
}

void cDust::CreateFireTail(D3DXVECTOR3 vecPos, float fStartsize)
{
	stEffcet  tempDllipseDust;
	tempDllipseDust.CreateFireTail(vecPos, fStartsize);
	m_vDust.push_back(tempDllipseDust);
}

void cDust::CreateFireCloude(D3DXVECTOR3 vecPos, float fMaxsize)
{
	stEffcet  tempDllipseDust;
	tempDllipseDust.CreateFireCloude(vecPos, fMaxsize);
	m_vDust.push_back(tempDllipseDust);
}

void cDust::CreateBlast(D3DXVECTOR3 vecPos, float fStartsize)
{
	stEffcet  tempDllipseDust;
	tempDllipseDust.CreateBlast(vecPos, fStartsize);
	m_vDust.push_back(tempDllipseDust);
}

void cDust::CreateBlastDust(D3DXVECTOR3 vecPos, float fStartsize)
{
	stEffcet  tempDllipseDust;
	tempDllipseDust.CreateBlastDust(vecPos, fStartsize);
	m_vDust.push_back(tempDllipseDust);
}

void cDust::CreateBlastCloude(D3DXVECTOR3 vecPos, float fStartsize)
{
	stEffcet  tempDllipseDust;
	tempDllipseDust.CreateBlastCloude(vecPos, fStartsize);
	m_vDust.push_back(tempDllipseDust);
}

void cDust::Update()
{
	stEffcet		tempEffect;
	D3DXMATRIXA16	tempMatR;
	bool			bIsInsert = false;
	for (m_viDust = m_vDust.begin(); m_viDust < m_vDust.end(); )
	{
		if ((*m_viDust).m_bLife)
		{
			(*m_viDust).Update();
			++m_viDust;
		}
		else
		{
			if ((*m_viDust).m_EffectNum == 13)
			{
				D3DXMatrixIdentity(&tempMatR);
				D3DXMatrixRotationZ(&tempMatR, D3DXToRadian(90));
				tempMatR._41 = (*m_viDust).m_pVPos->x;
				tempMatR._42 = (*m_viDust).m_pVPos->y;
				tempMatR._43 = (*m_viDust).m_pVPos->z;
				tempEffect.CreateCountAtk({ 1, 1, 1 }, g_pEffectManager->GetCircleWindMesh(4), g_pEffectManager->GetCircleWindMesh(5),
					g_pEffectManager->GetCircleWindMesh(6), g_pEffectManager->GetCircleWindMesh(7), { 0, 0, 0 }, true, 2, &tempMatR);
				bIsInsert = true;
			}
			m_viDust = m_vDust.erase(m_viDust);
		}
	}
	if (bIsInsert)
		m_vDust.push_back(tempEffect);
}
void cDust::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);


	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	D3DXMATRIXA16 matView;
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matView, 0, &matView);

	g_pD3DDevice->SetFVF(ST_PCT_VERTEX::FVF);

	for (int i = 0; i < m_vDust.size(); ++i)
	{
		stEffcet SearchEffect = m_vDust[i];
		if (SearchEffect.m_bLife)
		{

			D3DXMATRIXA16	matT;
			if (SearchEffect.m_EffectNum == 13)
			{
				if (SearchEffect.m_pVPos == NULL)
					D3DXMatrixTranslation(&matT, 0, 0, 0);
				else
					D3DXMatrixTranslation(&matT, SearchEffect.m_pVPos->x, SearchEffect.m_pVPos->y, SearchEffect.m_pVPos->z);
			}
			else
			{
				D3DXMatrixTranslation(&matT, SearchEffect.m_vPos.x, SearchEffect.m_vPos.y, SearchEffect.m_vPos.z);
			}
			D3DXMATRIXA16	matS;
			D3DXMATRIXA16 mulmatView;
			switch (SearchEffect.m_EffectNum)
			{
			case 0:
				D3DXMatrixScaling(&matS, SearchEffect.m_vScale.x, SearchEffect.m_vScale.y, SearchEffect.m_vScale.z);
				SearchEffect.m_matWorld = matS *  SearchEffect.m_matR * matT * SearchEffect.m_matSaveWorld;

				g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture("./EffectImage/puff5.png"));

				mulmatView = matS * matView;
				Billboard(&SearchEffect.m_matWorld, &mulmatView);

				break;
			case 1:
				D3DXMatrixScaling(&matS, SearchEffect.m_vScale.x, SearchEffect.m_vScale.y, SearchEffect.m_vScale.z);
				SearchEffect.m_matWorld = matS *  SearchEffect.m_matR * matT;
				g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture("./EffectImage/Dust2.png"));

				mulmatView = matS * matView;
				Billboard(&SearchEffect.m_matWorld, &mulmatView);
				break;

			case 2:
				if (i == 0)
					g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture("./EffectImage/slashLine2.png"));
				else
					g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture("./EffectImage/slashLine1.png"));
				D3DXMatrixScaling(&matS, SearchEffect.m_vScale.x, SearchEffect.m_vScale.y, SearchEffect.m_vScale.z);
				SearchEffect.m_matWorld = matS * matT * SearchEffect.m_matR;
				break;
			case 4:
			case 8:
				if (i == 0)
					g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture("./EffectImage/ring_outer_wind01.png"));
				D3DXMatrixScaling(&matS, SearchEffect.m_vScale.x, SearchEffect.m_vScale.y, SearchEffect.m_vScale.z);

				break;
			case 6:
			case 9:
				if (i == 0)
					g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture("./EffectImage/ship01_gray.png"));
				D3DXMatrixScaling(&matS, SearchEffect.m_vScale.x, SearchEffect.m_vScale.y, SearchEffect.m_vScale.z);
				break;
			case 11:
				D3DXMatrixScaling(&matS, SearchEffect.m_vScale.x, SearchEffect.m_vScale.y, SearchEffect.m_vScale.z);
				break;

			case 7:
				if (i == 0)
					g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture("./EffectImage/shine_circle_01.png"));
				D3DXMatrixScaling(&matS, SearchEffect.m_vScale.x, SearchEffect.m_vScale.y, SearchEffect.m_vScale.z);

				break;
			case 5:
				if (i == 0)
					g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture("./EffectImage/speedLine.png"));
				D3DXMatrixScaling(&matS, SearchEffect.m_vScale.x, SearchEffect.m_vScale.y, SearchEffect.m_vScale.z);
				//SearchEffect.m_matWorld = matS *  SearchEffect.m_matR * matT;
				D3DXMatrixIdentity(&SearchEffect.m_matWorld);
				SearchEffect.m_matWorld *= matS * matT* SearchEffect.m_matR;
				break;
			case 10:
				if (i == 0)
					g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture("./EffectImage/ring2.png"));
				D3DXMatrixScaling(&matS, SearchEffect.m_vScale.x, SearchEffect.m_vScale.y, SearchEffect.m_vScale.z);
				D3DXMatrixIdentity(&SearchEffect.m_matWorld);
				SearchEffect.m_matWorld *= matS * SearchEffect.m_matSaveWorld;
				break;
			case 12:

				if (i == 0)
					g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture("./EffectImage/dust_bright.png"));
				D3DXMatrixScaling(&matS, SearchEffect.m_vScale.x, SearchEffect.m_vScale.y, SearchEffect.m_vScale.z);
				D3DXMatrixIdentity(&SearchEffect.m_matWorld);
				SearchEffect.m_matWorld *= matS * matT;
				mulmatView = matS * matView;
				Billboard(&SearchEffect.m_matWorld, &mulmatView);
				break;

			case 13:

				if (i == 0)
					g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture("./EffectImage/EllpiseFire.png"));

				D3DXMatrixScaling(&matS, SearchEffect.m_vScale.x - 2.f, SearchEffect.m_vScale.y - 2.f, SearchEffect.m_vScale.z - 2.f);
				D3DXMatrixIdentity(&SearchEffect.m_matWorld);
				SearchEffect.m_matWorld *= matS * matT;
				mulmatView = matS * matView;
				Billboard(&SearchEffect.m_matWorld, &mulmatView);
				break;

			case 14:
				if (i == 0)
				{
					g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture("./EffectImage/Dust0.png"));
				}

				D3DXMatrixScaling(&matS, SearchEffect.m_vScale.x - 2.f, SearchEffect.m_vScale.y - 2.f, SearchEffect.m_vScale.z - 2.f);
				D3DXMatrixIdentity(&SearchEffect.m_matWorld);
				SearchEffect.m_matWorld *= matS * matT;
				mulmatView = matS * SearchEffect.m_matR* matView;
				Billboard(&SearchEffect.m_matWorld, &mulmatView);
				break;

			case 15:
				if (i == 0)
				{
					int rnd = rand() % 4;

					if (rnd == 0)
						g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture("./EffectImage/fireTail1.png"));
					else if (rnd == 1)
						g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture("./EffectImage/fireTail2.png"));
					else if (rnd == 2)
						g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture("./EffectImage/fireTail3.png"));
					else
						g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture("./EffectImage/fireTail4.png"));
				}
				D3DXMatrixScaling(&matS, SearchEffect.m_vScale.x, SearchEffect.m_vScale.y, SearchEffect.m_vScale.z);
				D3DXMatrixIdentity(&SearchEffect.m_matWorld);
				SearchEffect.m_matWorld *= matS * matT;
				mulmatView = matS * SearchEffect.m_matR * matView;
				Billboard(&SearchEffect.m_matWorld, &mulmatView);
				break;


			case 16:
				if (i == 0)
					g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture("./EffectImage/explosion1.png"));

				D3DXMatrixScaling(&matS, SearchEffect.m_vScale.x, SearchEffect.m_vScale.y, SearchEffect.m_vScale.z);
				D3DXMatrixIdentity(&SearchEffect.m_matWorld);
				SearchEffect.m_matWorld *= matS * matT;
				mulmatView = matS * SearchEffect.m_matR* matView;
				Billboard(&SearchEffect.m_matWorld, &mulmatView);
				break;

			case 17:
				if (i == 0)
				{
					g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture("./EffectImage/explotionDust1.png"));
					//int rnd = rand() % 2;
					//if (rnd == 0)
					//	g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture("./EffectImage/explotionDust1.png"));
					//else 
					//	g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture("./EffectImage/explotionDust2.png"));
				}

				D3DXMatrixScaling(&matS, SearchEffect.m_vScale.x, SearchEffect.m_vScale.y, SearchEffect.m_vScale.z);
				D3DXMatrixIdentity(&SearchEffect.m_matWorld);
				SearchEffect.m_matWorld *= matS * matT;
				mulmatView = matS * SearchEffect.m_matR* matView;
				Billboard(&SearchEffect.m_matWorld, &mulmatView);
				break;

			case 18:
				if (i == 0)
					g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture("./EffectImage/explotionDust3.png"));

				D3DXMatrixScaling(&matS, SearchEffect.m_vScale.x, SearchEffect.m_vScale.y, SearchEffect.m_vScale.z);
				D3DXMatrixIdentity(&SearchEffect.m_matWorld);
				SearchEffect.m_matWorld *= matS * matT;
				mulmatView = matS * SearchEffect.m_matR* matView;
				Billboard(&SearchEffect.m_matWorld, &mulmatView);
				break;
			}

			if (SearchEffect.m_EffectNum <= 2 || SearchEffect.m_EffectNum == 5 || SearchEffect.m_EffectNum == 10
				|| SearchEffect.m_EffectNum == 12 || SearchEffect.m_EffectNum == 13 || SearchEffect.m_EffectNum == 14
				|| SearchEffect.m_EffectNum == 15 || SearchEffect.m_EffectNum == 16 || SearchEffect.m_EffectNum == 17
				|| SearchEffect.m_EffectNum == 18)
			{

				if (SearchEffect.m_EffectNum == 12)
				{
					g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
					g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
					g_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				}
				else if (SearchEffect.m_EffectNum == 13)
				{
					g_pD3DDevice->SetTransform(D3DTS_WORLD, &SearchEffect.m_matWorld);
					g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
						SearchEffect.m_vecVertex.size() / 3,
						&SearchEffect.m_vecVertex[0],
						sizeof(ST_PCT_VERTEX));
					g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture("./EffectImage/Fire-a.png"));

					D3DXMatrixScaling(&matS, SearchEffect.m_vScale.x, SearchEffect.m_vScale.y, SearchEffect.m_vScale.z);
					D3DXMatrixIdentity(&SearchEffect.m_matWorld);
					SearchEffect.m_matWorld *= matS * matT;
					mulmatView = matS * SearchEffect.m_matR * matView;

					Billboard(&SearchEffect.m_matWorld, &mulmatView);


				}

				g_pD3DDevice->SetTransform(D3DTS_WORLD, &SearchEffect.m_matWorld);
				g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
					SearchEffect.m_vecVertex.size() / 3,
					&SearchEffect.m_vecVertex[0],
					sizeof(ST_PCT_VERTEX));

			}
			else
			{
				int WindSize = SearchEffect.m_vWind.size();
				for (int nWindsize = 0; nWindsize < WindSize; ++nWindsize)
				{
					D3DXMatrixIdentity(&SearchEffect.m_matWorld);
					D3DXMATRIXA16 tempSaveMat;

					////////////////////////////////////////////////////////////////////////////////////////////  방패돌격시 방패 앞의 위치로만 그림
					if (SearchEffect.m_EffectNum == 8 || SearchEffect.m_EffectNum == 9)
						tempSaveMat = *SearchEffect.m_pmatSaveWorld;
					else
						tempSaveMat = SearchEffect.m_matSaveWorld;
					////////////////////////////////////////////////////////////////////////////////////////////

					D3DXVECTOR3 tempVec = { 0, 0, 10 };
					D3DXVec3TransformCoord(&tempVec, &tempVec, &tempSaveMat);
					D3DXMATRIXA16 tempMatT;
					D3DXMatrixIdentity(&tempMatT);
					D3DXMatrixTranslation(&tempMatT, SearchEffect.m_vecOffeSet.x, SearchEffect.m_vecOffeSet.y, SearchEffect.m_vecOffeSet.z);
					D3DMATERIAL9	tempMtl;
					ZeroMemory(&tempMtl, sizeof(tempMtl));
					tempMtl.Ambient = D3DXCOLOR(1, 1, 1, 0);
					////////////////////////////////////////////////////////////////////////////////////////////  방패 반격시 텍스쳐 여러개 띄우기 위함임.
					if (SearchEffect.m_EffectNum == 11 && (nWindsize == 0 || nWindsize == 1))
					{
						if (!SearchEffect.m_isRedCircle)
							g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture("./EffectImage/count.png"));
						else
							g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture("./EffectImage/countRed.png"));
					}
					else if (SearchEffect.m_EffectNum == 11 && (nWindsize == 2 || nWindsize == 3))
					{
						g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture("./EffectImage/count2.png"));
						tempMatT._41 += SearchEffect.m_vMoveDir.x;
					}
					////////////////////////////////////////////////////////////////////////////////////////////

					SearchEffect.m_matWorld *= matS* SearchEffect.m_matR  * tempMatT * tempSaveMat;

					g_pD3DDevice->SetTransform(D3DTS_WORLD, &SearchEffect.m_matWorld);
					g_pD3DDevice->SetMaterial(&tempMtl);
					(*SearchEffect.m_vWind[nWindsize]).DrawSubset(0);

				}
			}
		}
	}

	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);

	//g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
}

void cDust::Release()
{
}



void cDust::Billboard(D3DXMATRIXA16 * inoutMat, D3DXMATRIXA16 * matView)
{
	inoutMat->_11 = matView->_11;
	inoutMat->_12 = matView->_12;
	inoutMat->_13 = matView->_13;

	inoutMat->_21 = matView->_21;
	inoutMat->_22 = matView->_22;
	inoutMat->_23 = matView->_23;

	inoutMat->_31 = matView->_31;
	inoutMat->_32 = matView->_32;
	inoutMat->_33 = matView->_33;
}



void stEffcet::CreateEllipseDust(float fRadius, D3DXMATRIXA16* matWorld)
{
	m_EffectNum = DUST_ELLIPS;
	ST_PCT_VERTEX tempVetex;
	D3DXMATRIX matRX, matRY, matRZ, tempmatWorld;
	m_vScale = D3DXVECTOR3(1, 1, 1);
	m_pmatParent = NULL;
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matSaveWorld);
	D3DXMatrixIdentity(&m_matR);
	m_bLife = true;
	m_fAlpha = 255;
	m_fSprayPower = 0.f;
	m_fGravity = 0.f;

	m_vPos = D3DXVECTOR3(fRadius, 0, 0);
	m_vPos.y = 1.f;
	m_vAngle = D3DXVECTOR3(
		D3DXToRadian(rand() % 500 / 10.0f),
		D3DXToRadian(rand() % 3600 / 10.0f),
		0);

	m_matSaveWorld = *matWorld;
	D3DXMatrixRotationX(&matRX, m_vAngle.x);
	D3DXMatrixRotationY(&matRY, m_vAngle.y);
	D3DXMatrixRotationZ(&matRZ, m_vAngle.z);
	tempmatWorld = matRX * matRY * matRZ;

	D3DXVec3TransformCoord(
		&m_vPos,
		&m_vPos,
		&tempmatWorld);

	tempVetex.c = D3DCOLOR_ARGB(m_fAlpha, 255, 212, 212);

	tempVetex.p = D3DXVECTOR3(-1, -1, 0);
	tempVetex.t = D3DXVECTOR2(0, 1);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(-1, 1, 0);
	tempVetex.t = D3DXVECTOR2(0, 0);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(1, 1, 0);
	tempVetex.t = D3DXVECTOR2(1, 0);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(-1, -1, 0);
	tempVetex.t = D3DXVECTOR2(0, 1);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(1, 1, 0);
	tempVetex.t = D3DXVECTOR2(1, 0);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(1, -1, 0);
	tempVetex.t = D3DXVECTOR2(1, 1);
	m_vecVertex.push_back(tempVetex);
}

void stEffcet::CreateSprayDust(D3DXVECTOR3 vPos, D3DXVECTOR3 vMoveDir, float fSparyPower)
{
	m_EffectNum = DUST_SPRAY;
	ST_PCT_VERTEX tempVetex;
	D3DXMATRIX matRX, matRY, matRZ, matWorld;
	m_vScale = D3DXVECTOR3(1, 1, 1);
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matR);
	m_bLife = true;
	m_fAlpha = 200 + rand() % 55;
	m_fSprayPower = 0.f;
	m_fGravity = 0.f;
	m_fSprayPower = (rand() % 45) / (30.f - fSparyPower);					// 분사 힘 설정.

	D3DXMatrixIdentity(&m_matWorld);
	m_vScale = D3DXVECTOR3(0.01f, 0.01f, 0.01f);
	m_vPos = vPos;
	m_vMoveDir = D3DXVECTOR3(1, 0, 0);

	m_vMoveDir.x = (vMoveDir.x);
	m_vMoveDir.y = 0;
	m_vMoveDir.z = (vMoveDir.z);

	tempVetex.c = D3DCOLOR_ARGB(m_fAlpha, 255, 212, 212);

	tempVetex.p = D3DXVECTOR3(-1, -1, 0);
	tempVetex.t = D3DXVECTOR2(0, 1);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(-1, 1, 0);
	tempVetex.t = D3DXVECTOR2(0, 0);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(1, 1, 0);
	tempVetex.t = D3DXVECTOR2(1, 0);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(-1, -1, 0);
	tempVetex.t = D3DXVECTOR2(0, 1);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(1, 1, 0);
	tempVetex.t = D3DXVECTOR2(1, 0);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(1, -1, 0);
	tempVetex.t = D3DXVECTOR2(1, 1);
	m_vecVertex.push_back(tempVetex);
}

void stEffcet::CreateSlashLine(D3DXVECTOR3 vPos, float fAngle, D3DXMATRIXA16* matR)
{
	m_EffectNum = SLASH_LINE;
	ST_PCT_VERTEX tempVetex;
	D3DXMATRIX matRX, matRY, matRZ, matWorld;
	m_vScale = D3DXVECTOR3(1, 1, 1);
	D3DXMatrixIdentity(&m_matWorld);
	m_bLife = true;
	m_fAlpha = 200 + rand() % 55;
	m_fSprayPower = 0.f;
	m_fGravity = 0.f;

	////////////////////////////////////////////////////////////////////////////////////////

	m_fSprayPower = (rand() % 45) / 30.f;					// 분사 힘 설정.

	D3DXMatrixIdentity(&m_matWorld);

	m_vScale = D3DXVECTOR3(0.01f, 0.01f, 0.01f);
	D3DXMATRIXA16 matLineRotate;

	if (rand() % 2)
	{
		float fRand = float(rand() % 50) / 50.f;
		m_vMoveDir.x = -2.f + fRand;
	}
	else
	{
		float fRand = float(rand() % 50) / 50.f;
		m_vMoveDir.x = +2.f - fRand;
	}

	float angle = D3DXToRadian((rand() % 10) - 5);

	D3DXMatrixIdentity(&matLineRotate);
	D3DXMatrixRotationZ(&matLineRotate, angle);

	m_vMoveDir.y = 0;
	m_vMoveDir.z = 0;

	m_vScale = D3DXVECTOR3(1.f, 1.f, 1.f);
	m_vPos = vPos;
	if (!matR)
	{
		D3DXMatrixIdentity(&m_matR);
		m_matR *= matLineRotate;
	}
	else
		m_matR = *matR * matLineRotate;


	tempVetex.c = D3DCOLOR_ARGB(m_fAlpha, 255, 212, 212);

	tempVetex.p = D3DXVECTOR3(-1, -1, 0);
	tempVetex.t = D3DXVECTOR2(0, 1);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(-1, 1, 0);
	tempVetex.t = D3DXVECTOR2(0, 0);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(1, 1, 0);
	tempVetex.t = D3DXVECTOR2(1, 0);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(-1, -1, 0);
	tempVetex.t = D3DXVECTOR2(0, 1);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(1, 1, 0);
	tempVetex.t = D3DXVECTOR2(1, 0);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(1, -1, 0);
	tempVetex.t = D3DXVECTOR2(1, 1);
	m_vecVertex.push_back(tempVetex);

	int size = m_vecVertex.size();

	D3DXMATRIXA16	tempmatR;
	for (int i = 0; i < 360; i += 45)
	{
		D3DXMatrixIdentity(&tempmatR);
		D3DXMatrixRotationX(&tempmatR, D3DXToRadian(i));
		for (int i = 0; i < size; ++i)
		{
			ST_PCT_VERTEX	tempVec;
			tempVec = m_vecVertex[i];
			D3DXVec3TransformCoord(&tempVec.p, &tempVec.p, &tempmatR);
			m_vecVertex.push_back(tempVec);
		}
	}


}

void stEffcet::CreateWindEllipse(D3DXVECTOR3 vecScaling, cSkinnedMesh* pMesh1, cSkinnedMesh* pMesh2, D3DXVECTOR3 offset, float maxsize, D3DXMATRIXA16 * matR)
{
	m_EffectNum = WIND_ELLIPSE;
	m_fMaxSize = maxsize;
	m_vecOffeSet = offset;


	D3DXMATRIXA16 matParent;
	D3DXMatrixIdentity(&matParent);

	LPD3DXMESH	pCopyMesh;

	LPD3DXMESH	mesh;
	if (matR)
		m_matSaveWorld = *matR;

	m_fRoolSpeed = float(rand() % 100) / 100.f + 1 * (m_fMaxSize / 2.f);
	m_vScale = vecScaling;
	mesh = pMesh1->GetRootBone()->pMeshContainer->MeshData.pMesh;
	mesh->CloneMeshFVF(mesh->GetOptions(), mesh->GetFVF(), g_pD3DDevice, &pCopyMesh);
	m_vWind.push_back(pCopyMesh);

	mesh = pMesh2->GetRootBone()->pMeshContainer->MeshData.pMesh;
	mesh->CloneMeshFVF(mesh->GetOptions(), mesh->GetFVF(), g_pD3DDevice, &pCopyMesh);
	m_vWind.push_back(pCopyMesh);

	m_bLife = true;

}

void stEffcet::CreatePWindEllipse(D3DXVECTOR3 vecScaling, cSkinnedMesh* pMesh1, cSkinnedMesh* pMesh2, D3DXVECTOR3 offset, float maxsize, D3DXMATRIXA16 * matR)
{
	m_EffectNum = WIND_PELLIPSE;
	m_fMaxSize = maxsize;
	m_vecOffeSet = offset;


	D3DXMATRIXA16 matParent;
	D3DXMatrixIdentity(&matParent);

	LPD3DXMESH	pCopyMesh;

	LPD3DXMESH	mesh;

	if (matR)
		m_pmatSaveWorld = matR;

	m_fRoolSpeed = float(rand() % 100) / 100.f + 1 * (m_fMaxSize / 2.f);


	m_vScale = vecScaling;
	mesh = pMesh1->GetRootBone()->pMeshContainer->MeshData.pMesh;
	mesh->CloneMeshFVF(mesh->GetOptions(), mesh->GetFVF(), g_pD3DDevice, &pCopyMesh);
	m_vWind.push_back(pCopyMesh);

	mesh = pMesh2->GetRootBone()->pMeshContainer->MeshData.pMesh;
	mesh->CloneMeshFVF(mesh->GetOptions(), mesh->GetFVF(), g_pD3DDevice, &pCopyMesh);
	m_vWind.push_back(pCopyMesh);

	m_bLife = true;

}

void stEffcet::CreateWindEllipseLine(D3DXVECTOR3 vecScaling, cSkinnedMesh * pMesh1, cSkinnedMesh * pMesh2, D3DXVECTOR3 offset, float maxsize, D3DXMATRIXA16 * matR)
{
	m_EffectNum = WIND_ELLIPSELINE;
	m_fMaxSize = maxsize;
	m_vecOffeSet = offset;


	D3DXMATRIXA16 matParent;
	D3DXMatrixIdentity(&matParent);

	LPD3DXMESH	pCopyMesh;

	LPD3DXMESH	mesh;

	if (matR)
		m_matSaveWorld = *matR;

	m_vAngle.z = rand() % 360;

	m_vScale = { 1, 1, 1 };

	mesh = pMesh1->GetRootBone()->pMeshContainer->MeshData.pMesh;
	mesh->CloneMeshFVF(mesh->GetOptions(), mesh->GetFVF(), g_pD3DDevice, &pCopyMesh);
	m_vWind.push_back(pCopyMesh);

	mesh = pMesh2->GetRootBone()->pMeshContainer->MeshData.pMesh;
	mesh->CloneMeshFVF(mesh->GetOptions(), mesh->GetFVF(), g_pD3DDevice, &pCopyMesh);
	m_vWind.push_back(pCopyMesh);

	m_bLife = true;
}

void stEffcet::CreatePWindEllipseLine(D3DXVECTOR3 vecScaling, cSkinnedMesh * pMesh1, cSkinnedMesh * pMesh2, D3DXVECTOR3 offset, float maxsize, D3DXMATRIXA16 * matR)
{
	m_EffectNum = WIND_PELLIPSELINE;
	m_fMaxSize = maxsize;
	m_vecOffeSet = offset;


	D3DXMATRIXA16 matParent;
	D3DXMatrixIdentity(&matParent);

	LPD3DXMESH	pCopyMesh;

	LPD3DXMESH	mesh;

	if (matR)
		m_pmatSaveWorld = matR;

	m_vAngle.z = rand() % 360;

	m_vScale = vecScaling;

	mesh = pMesh1->GetRootBone()->pMeshContainer->MeshData.pMesh;
	mesh->CloneMeshFVF(mesh->GetOptions(), mesh->GetFVF(), g_pD3DDevice, &pCopyMesh);
	m_vWind.push_back(pCopyMesh);

	mesh = pMesh2->GetRootBone()->pMeshContainer->MeshData.pMesh;
	mesh->CloneMeshFVF(mesh->GetOptions(), mesh->GetFVF(), g_pD3DDevice, &pCopyMesh);
	m_vWind.push_back(pCopyMesh);

	m_bLife = true;
}

void stEffcet::CreateWindKick(D3DXVECTOR3 vecScaling, cSkinnedMesh * pMesh1, cSkinnedMesh * pMesh2, D3DXVECTOR3 offset, D3DXMATRIXA16 * matR)
{
	m_EffectNum = WIND_KCIK;
	m_vecOffeSet = offset;

	D3DXMATRIXA16 matParent;
	D3DXMatrixIdentity(&matParent);

	LPD3DXMESH	pCopyMesh;

	LPD3DXMESH	mesh;

	if (matR)
		m_matSaveWorld = *matR;

	m_vAngle.z = rand() % 360;

	m_vScale = { 1, 1, 1 };

	mesh = pMesh1->GetRootBone()->pMeshContainer->MeshData.pMesh;
	mesh->CloneMeshFVF(mesh->GetOptions(), mesh->GetFVF(), g_pD3DDevice, &pCopyMesh);
	m_vWind.push_back(pCopyMesh);

	mesh = pMesh2->GetRootBone()->pMeshContainer->MeshData.pMesh;
	mesh->CloneMeshFVF(mesh->GetOptions(), mesh->GetFVF(), g_pD3DDevice, &pCopyMesh);
	m_vWind.push_back(pCopyMesh);

	m_bLife = true;
}

void stEffcet::CreateWindLine(float fAngle, D3DXMATRIXA16 * matR)
{
	m_EffectNum = WIHD_LINE;

	ST_PCT_VERTEX tempVetex;

	tempVetex.c = D3DCOLOR_ARGB(m_fAlpha, 255, 212, 212);

	m_MoveSpeed = float(rand() % 5) / 10.f + 0.5f;
	m_vPos.x = float(rand() % 30) / 1.f + 10;
	m_fStartRadius = m_vPos.x;
	float randWidth = m_vPos.x * 0.3f;

	m_vAngle.z = rand() % 360;

	D3DXMatrixRotationZ(&m_matR, D3DXToDegree(m_vAngle.z));

	tempVetex.p = D3DXVECTOR3(-randWidth, -randWidth * 0.2f, 0);
	tempVetex.t = D3DXVECTOR2(0, 1);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(-randWidth, randWidth * 0.3f, 0);
	tempVetex.t = D3DXVECTOR2(0, 0);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(randWidth, randWidth * 0.3f, 0);
	tempVetex.t = D3DXVECTOR2(1, 0);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(-randWidth, -randWidth * 0.2f, 0);
	tempVetex.t = D3DXVECTOR2(0, 1);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(randWidth, randWidth * 0.3f, 0);
	tempVetex.t = D3DXVECTOR2(1, 0);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(randWidth, -randWidth * 0.2f, 0);
	tempVetex.t = D3DXVECTOR2(1, 1);
	m_vecVertex.push_back(tempVetex);

}

void stEffcet::CreateYellowRing(D3DXMATRIXA16 * matR, float fSize)
{
	m_EffectNum = YELLOW_RING;

	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matR);

	m_matSaveWorld = *matR;

	m_bLife = true;
	ST_PCT_VERTEX tempVetex;
	D3DXMATRIX matRX, matRY, matRZ, matWorld;
	m_vScale = D3DXVECTOR3(1 * fSize, 1 * fSize, 1 * fSize);
	m_fAlpha = 200 + rand() % 55;
	m_vAngle.z = rand() % 360;

	D3DXMatrixRotationZ(&matRZ, D3DXToRadian(m_vAngle.z));

	m_matR = matRX * matRY * matRZ;

	tempVetex.c = D3DCOLOR_ARGB(m_fAlpha, 255, 212, 212);

	tempVetex.p = D3DXVECTOR3(-1, -1, 0);
	tempVetex.t = D3DXVECTOR2(0, 1);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(-1, 1, 0);
	tempVetex.t = D3DXVECTOR2(0, 0);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(1, 1, 0);
	tempVetex.t = D3DXVECTOR2(1, 0);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(-1, -1, 0);
	tempVetex.t = D3DXVECTOR2(0, 1);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(1, 1, 0);
	tempVetex.t = D3DXVECTOR2(1, 0);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(1, -1, 0);
	tempVetex.t = D3DXVECTOR2(1, 1);
	m_vecVertex.push_back(tempVetex);

	D3DXMATRIXA16 rotationR;
	D3DXMatrixIdentity(&rotationR);
	D3DXMatrixRotationX(&rotationR, D3DXToRadian(180));
	int size = m_vecVertex.size();
	for (int i = 0; i < size; ++i)
	{
		ST_PCT_VERTEX tempVec = m_vecVertex[i];
		D3DXVec3TransformCoord(&tempVec.p, &tempVec.p, &rotationR);
		m_vecVertex.push_back(tempVec);
	}



}

void stEffcet::CreateDust(D3DXVECTOR3 vecPos, float fSize, D3DXVECTOR3 vecScalling, float fAlphaDeCreasingRate, D3DXVECTOR3 moveDir)
{
	m_EffectNum = DUST;
	ST_PCT_VERTEX tempVetex;
	D3DXMATRIX matRX, matRY, matRZ, tempmatWorld;
	m_vScale = D3DXVECTOR3(1, 1, 1);
	m_pmatParent = NULL;
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matSaveWorld);
	D3DXMatrixIdentity(&m_matR);
	m_bLife = true;
	m_fAlpha = 255;
	m_fSprayPower = 0.f;
	m_fGravity = 0.f;

	m_vPos = vecPos;
	m_vIncreaseScale = vecScalling;
	m_fDecreaseAlpha = fAlphaDeCreasingRate;
	m_vMoveDir = moveDir;


	tempVetex.c = D3DCOLOR_ARGB(m_fAlpha, m_fAlpha, m_fAlpha, m_fAlpha);

	tempVetex.p = D3DXVECTOR3(-1, -1, 0);
	tempVetex.t = D3DXVECTOR2(0, 1);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(-1, 1, 0);
	tempVetex.t = D3DXVECTOR2(0, 0);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(1, 1, 0);
	tempVetex.t = D3DXVECTOR2(1, 0);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(-1, -1, 0);
	tempVetex.t = D3DXVECTOR2(0, 1);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(1, 1, 0);
	tempVetex.t = D3DXVECTOR2(1, 0);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(1, -1, 0);
	tempVetex.t = D3DXVECTOR2(1, 1);
	m_vecVertex.push_back(tempVetex);



}

void stEffcet::CreateCountAtk(D3DXVECTOR3 vecScaling, cSkinnedMesh* pMesh1, cSkinnedMesh* pMesh2, cSkinnedMesh* pMesh3, cSkinnedMesh* pMesh4, D3DXVECTOR3 offset, bool bIsRedCircle, float maxsize, D3DXMATRIXA16 * matR)
{
	m_EffectNum = COUNT_ATK;
	m_fMaxSize = maxsize;
	m_vecOffeSet = offset;
	m_isRedCircle = bIsRedCircle;


	if (matR)
		m_matSaveWorld = *matR;

	LPD3DXMESH	pCopyMesh;

	LPD3DXMESH	mesh;


	if (matR)
		m_matSaveWorld = *matR;

	m_fRoolSpeed = float(rand() % 100) / 100.f + 1 * (m_fMaxSize / 2.f);


	m_vScale = vecScaling;
	mesh = pMesh1->GetRootBone()->pMeshContainer->MeshData.pMesh;
	mesh->CloneMeshFVF(mesh->GetOptions(), mesh->GetFVF(), g_pD3DDevice, &pCopyMesh);
	m_vWind.push_back(pCopyMesh);

	mesh = pMesh2->GetRootBone()->pMeshContainer->MeshData.pMesh;
	mesh->CloneMeshFVF(mesh->GetOptions(), mesh->GetFVF(), g_pD3DDevice, &pCopyMesh);
	m_vWind.push_back(pCopyMesh);

	mesh = pMesh3->GetRootBone()->pMeshContainer->MeshData.pMesh;
	mesh->CloneMeshFVF(mesh->GetOptions(), mesh->GetFVF(), g_pD3DDevice, &pCopyMesh);
	m_vWind.push_back(pCopyMesh);

	mesh = pMesh4->GetRootBone()->pMeshContainer->MeshData.pMesh;
	mesh->CloneMeshFVF(mesh->GetOptions(), mesh->GetFVF(), g_pD3DDevice, &pCopyMesh);
	m_vWind.push_back(pCopyMesh);

	m_bLife = true;
}

void stEffcet::CreateFireBallEgg(D3DXVECTOR3* pvecPos, float fLifeTime, float Size)
{

	m_EffectNum = FIRE_BALL_EGG;
	ST_PCT_VERTEX tempVetex;
	D3DXMATRIX matRX, matRY, matRZ, tempmatWorld;
	m_pmatParent = NULL;
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matSaveWorld);
	D3DXMatrixIdentity(&m_matR);

	m_fLifeCount = fLifeTime;
	m_bLife = true;
	m_fAlpha = 255;
	m_fSprayPower = 0.f;
	m_fGravity = 0.f;
	m_vDecreaseScale = { Size / 100.f , Size / 100.f, Size / 100.f };
	m_vScale = { Size, Size, Size };
	m_pVPos = pvecPos;

	tempVetex.c = D3DCOLOR_ARGB(m_fAlpha, m_fAlpha, m_fAlpha, m_fAlpha);

	tempVetex.p = D3DXVECTOR3(-1, -1, 0);
	tempVetex.t = D3DXVECTOR2(0, 1);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(-1, 1, 0);
	tempVetex.t = D3DXVECTOR2(0, 0);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(1, 1, 0);
	tempVetex.t = D3DXVECTOR2(1, 0);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(-1, -1, 0);
	tempVetex.t = D3DXVECTOR2(0, 1);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(1, 1, 0);
	tempVetex.t = D3DXVECTOR2(1, 0);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(1, -1, 0);
	tempVetex.t = D3DXVECTOR2(1, 1);
	m_vecVertex.push_back(tempVetex);
}

void stEffcet::CreateFireCloude(D3DXVECTOR3 vecPos, float fMaxsize)
{
	m_EffectNum = FIRE_CLOUDE;
	ST_PCT_VERTEX tempVetex;

	m_vPos = vecPos;
	m_vScale = { 0, 0, 0 };
	m_fMaxSize = fMaxsize;
	m_vIncreaseScale = { fMaxsize / (fMaxsize * FIRE_BALL_EFFECT_TIME), fMaxsize / (fMaxsize * FIRE_BALL_EFFECT_TIME) , fMaxsize / (fMaxsize * FIRE_BALL_EFFECT_TIME) };
	m_MoveSpeed = float(rand() % 10) / 100;
	m_vAngle.z = rand() % 360;

	tempVetex.c = D3DCOLOR_ARGB(m_fAlpha, m_fAlpha, m_fAlpha, m_fAlpha);

	tempVetex.p = D3DXVECTOR3(-1, -1, 0);
	tempVetex.t = D3DXVECTOR2(0, 1);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(-1, 1, 0);
	tempVetex.t = D3DXVECTOR2(0, 0);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(1, 1, 0);
	tempVetex.t = D3DXVECTOR2(1, 0);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(-1, -1, 0);
	tempVetex.t = D3DXVECTOR2(0, 1);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(1, 1, 0);
	tempVetex.t = D3DXVECTOR2(1, 0);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(1, -1, 0);
	tempVetex.t = D3DXVECTOR2(1, 1);
	m_vecVertex.push_back(tempVetex);
}

void stEffcet::CreateFireTail(D3DXVECTOR3 vecPos, float fStartsize)
{
	m_EffectNum = FIRE_Tail;
	ST_PCT_VERTEX tempVetex;

	m_vPos = vecPos;
	m_vScale = { fStartsize, fStartsize, fStartsize };
	m_vAngle.z = rand() % 360;
	m_MoveSpeed = float(rand() % 10) / 300;

	m_vDecreaseScale = { fStartsize / (fStartsize * FIRE_BALL_EFFECT_TIME), fStartsize / (fStartsize * FIRE_BALL_EFFECT_TIME) , fStartsize / (fStartsize * FIRE_BALL_EFFECT_TIME) };

	tempVetex.c = D3DCOLOR_ARGB(m_fAlpha, m_fAlpha, m_fAlpha, m_fAlpha);

	tempVetex.p = D3DXVECTOR3(-1, -1, 0);
	tempVetex.t = D3DXVECTOR2(0, 1);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(-1, 1, 0);
	tempVetex.t = D3DXVECTOR2(0, 0);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(1, 1, 0);
	tempVetex.t = D3DXVECTOR2(1, 0);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(-1, -1, 0);
	tempVetex.t = D3DXVECTOR2(0, 1);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(1, 1, 0);
	tempVetex.t = D3DXVECTOR2(1, 0);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(1, -1, 0);
	tempVetex.t = D3DXVECTOR2(1, 1);
	m_vecVertex.push_back(tempVetex);
}

void stEffcet::CreateBlast(D3DXVECTOR3 vecPos, float fStartsize)
{
	m_EffectNum = BLAST;
	ST_PCT_VERTEX tempVetex;

	m_vPos = vecPos;
	m_vScale = { 0, 0, 0 };

	m_MoveSpeed = float(rand() % 10) / 300;
	m_fMaxSize = fStartsize;
	m_vIncreaseScale = { fStartsize / (fStartsize * BLAST_EFFECT_TIME), fStartsize / (fStartsize * BLAST_EFFECT_TIME) , fStartsize / (fStartsize * FIRE_BALL_EFFECT_TIME) };

	tempVetex.c = D3DCOLOR_ARGB(m_fAlpha, m_fAlpha, m_fAlpha, m_fAlpha);

	tempVetex.p = D3DXVECTOR3(-1, -1, 0);
	tempVetex.t = D3DXVECTOR2(0, 1);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(-1, 1, 0);
	tempVetex.t = D3DXVECTOR2(0, 0);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(1, 1, 0);
	tempVetex.t = D3DXVECTOR2(1, 0);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(-1, -1, 0);
	tempVetex.t = D3DXVECTOR2(0, 1);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(1, 1, 0);
	tempVetex.t = D3DXVECTOR2(1, 0);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(1, -1, 0);
	tempVetex.t = D3DXVECTOR2(1, 1);
	m_vecVertex.push_back(tempVetex);
}

void stEffcet::CreateBlastDust(D3DXVECTOR3 vecPos, float fStartsize)
{
	m_EffectNum = BLAST_DUST;
	ST_PCT_VERTEX tempVetex;

	m_vPos = vecPos;
	m_vScale = { 0, 0, 0 };
	m_fMaxSize = fStartsize;
	m_MoveSpeed = float(rand() % 10) / 300;

	m_vIncreaseScale = { fStartsize / (fStartsize * BLAST_EFFECT_TIME), fStartsize / (fStartsize * BLAST_EFFECT_TIME) , fStartsize / (fStartsize * FIRE_BALL_EFFECT_TIME) };

	tempVetex.c = D3DCOLOR_ARGB(m_fAlpha, m_fAlpha, m_fAlpha, m_fAlpha);

	tempVetex.p = D3DXVECTOR3(-1, -1, 0);
	tempVetex.t = D3DXVECTOR2(0, 1);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(-1, 1, 0);
	tempVetex.t = D3DXVECTOR2(0, 0);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(1, 1, 0);
	tempVetex.t = D3DXVECTOR2(1, 0);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(-1, -1, 0);
	tempVetex.t = D3DXVECTOR2(0, 1);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(1, 1, 0);
	tempVetex.t = D3DXVECTOR2(1, 0);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(1, -1, 0);
	tempVetex.t = D3DXVECTOR2(1, 1);
	m_vecVertex.push_back(tempVetex);
}

void stEffcet::CreateBlastCloude(D3DXVECTOR3 vecPos, float fStartsize)
{
	m_EffectNum = BLAST_CLOUD;
	ST_PCT_VERTEX tempVetex;

	m_vPos = vecPos;
	m_vScale = { 0, 0, 0 };
	m_fMaxSize = fStartsize;
	m_MoveSpeed = float(rand() % 10) / 300;

	m_vIncreaseScale = { fStartsize / (fStartsize * BLAST_EFFECT_TIME), fStartsize / (fStartsize * BLAST_EFFECT_TIME) , fStartsize / (fStartsize * FIRE_BALL_EFFECT_TIME) };

	tempVetex.c = D3DCOLOR_ARGB(m_fAlpha, m_fAlpha, m_fAlpha, m_fAlpha);

	tempVetex.p = D3DXVECTOR3(-1, -1, 0);
	tempVetex.t = D3DXVECTOR2(0, 1);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(-1, 1, 0);
	tempVetex.t = D3DXVECTOR2(0, 0);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(1, 1, 0);
	tempVetex.t = D3DXVECTOR2(1, 0);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(-1, -1, 0);
	tempVetex.t = D3DXVECTOR2(0, 1);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(1, 1, 0);
	tempVetex.t = D3DXVECTOR2(1, 0);
	m_vecVertex.push_back(tempVetex);

	tempVetex.p = D3DXVECTOR3(1, -1, 0);
	tempVetex.t = D3DXVECTOR2(1, 1);
	m_vecVertex.push_back(tempVetex);
}





void stEffcet::Update()
{
	{
		UpdateAlpha();
		D3DXMATRIXA16 matRY, matRX, matRZ;
		switch (m_EffectNum)
		{
		case DUST_ELLIPS:
			m_vPos.x += m_vPos.x * 0.01f;
			m_vPos.y += m_vPos.y * 0.01f;
			m_vPos.z += m_vPos.z * 0.01f;
			break;

		case DUST_SPRAY:
			m_fGravity += 0.006f;
			m_vPos.x += (m_vMoveDir.x * 0.8f) * m_fSprayPower * 0.05f;
			m_vPos.y += m_fSprayPower * 0.08f - m_fGravity;
			m_vPos.z += (m_vMoveDir.z * 0.8f) * m_fSprayPower * 0.05f;
			m_vScale.x += m_fSprayPower * 0.2f;
			m_vScale.y += m_fSprayPower * 0.2f;
			m_vScale.z += m_fSprayPower * 0.2f;
			break;
		case SLASH_LINE:
			//m_fGravity += 0.0025f;
			m_vPos.x += (m_vMoveDir.x * 1.5f) * m_fSprayPower * 0.05f;
			//m_vPos.y += m_fSprayPower * 0.08f - m_fGravity;
			//m_vPos.z += (m_vMoveDir.z * 0.8f) * m_fSprayPower * 0.05f;
			m_vScale.x += m_fSprayPower * 6.f;
			m_vScale.y += m_fSprayPower * 3.f;
			m_vScale.z += m_fSprayPower * 1;
			break;

		case WIND_ELLIPSE:
			//m_vPos.x += (m_vMoveDir.x * 1.5f) * m_fSprayPower * 0.05f;
			m_vAngle.y += 40 * m_fRoolSpeed;
			D3DXMatrixIdentity(&matRY);
			D3DXMatrixIdentity(&matRX);
			D3DXMatrixIdentity(&matRZ);
			D3DXMatrixRotationY(&matRY, D3DXToRadian(m_vAngle.y));
			D3DXMatrixRotationZ(&matRX, D3DXToRadian(-90));
			m_matR = matRY * matRX;
			if (m_vScale.x > 0.f && m_vScale.y > 0.f && m_vScale.z > 0.f)
			{
				m_vScale.x += 0.03f * m_fRoolSpeed;
				m_vScale.y += 0.03f * m_fRoolSpeed;
				m_vScale.z += 0.03f * m_fRoolSpeed;
			}
			if (m_vScale.x >= m_fMaxSize)
				m_bLife = false;

			break;
		case WIND_PELLIPSE:
			//m_vPos.x += (m_vMoveDir.x * 1.5f) * m_fSprayPower * 0.05f;
			m_vAngle.y += 40 * m_fRoolSpeed;
			D3DXMatrixIdentity(&matRY);
			D3DXMatrixIdentity(&matRX);
			D3DXMatrixIdentity(&matRZ);
			D3DXMatrixRotationY(&matRY, D3DXToRadian(m_vAngle.y));
			D3DXMatrixRotationZ(&matRX, D3DXToRadian(-270));
			m_matR = matRY * matRX;
			if (m_vScale.x > 0.f && m_vScale.y > 0.f && m_vScale.z > 0.f)
			{
				m_vScale.x += 0.03f * m_fRoolSpeed;
				m_vScale.y += 0.03f * m_fRoolSpeed;
				m_vScale.z += 0.03f * m_fRoolSpeed;
			}
			if (m_vScale.x >= m_fMaxSize)
				m_bLife = false;

			break;

		case WIND_PELLIPSELINE:

			D3DXMatrixIdentity(&matRY);
			D3DXMatrixIdentity(&matRX);
			D3DXMatrixIdentity(&matRZ);
			D3DXMatrixRotationY(&matRY, D3DXToRadian(m_vAngle.y));
			D3DXMatrixRotationZ(&matRX, D3DXToRadian(-270));

			m_matR = matRY * matRX;

			if (m_vScale.x < m_fMaxSize)
			{
				m_vScale.x += 0.12f;
				m_vScale.y += 0.12f;
				m_vScale.z += 0.12f;
				m_fAlpha -= 10.f;
			}
			else
				m_bLife = false;
			break;

		case WIND_ELLIPSELINE:

			D3DXMatrixIdentity(&matRY);
			D3DXMatrixIdentity(&matRX);
			D3DXMatrixIdentity(&matRZ);
			D3DXMatrixRotationY(&matRY, D3DXToRadian(m_vAngle.y));
			D3DXMatrixRotationZ(&matRX, D3DXToRadian(-90));

			m_matR = matRY * matRX;

			if (m_vScale.x < m_fMaxSize)
			{
				m_vScale.x += 0.12f;
				m_vScale.y += 0.12f;
				m_vScale.z += 0.12f;
				m_fAlpha -= 10.f;
			}
			else
				m_bLife = false;

			break;

		case WIND_KCIK:
			//m_vPos.x += (m_vMoveDir.x * 1.5f) * m_fSprayPower * 0.05f;

			D3DXMatrixIdentity(&matRY);
			D3DXMatrixIdentity(&matRX);
			D3DXMatrixIdentity(&matRZ);
			D3DXMatrixRotationY(&matRY, D3DXToRadian(m_vAngle.y));
			D3DXMatrixRotationZ(&matRX, D3DXToRadian(-90));

			m_matR = matRY * matRX;

			if (m_vScale.x < 5.f)
			{
				m_vScale.x += 0.4f;
				m_vScale.y += 0.4f;
				m_vScale.z += 0.8f;
				m_fAlpha -= 5.f;
			}
			else
				m_bLife = false;

			break;



		case WIHD_LINE:
			m_vPos.x -= m_MoveSpeed;

			if (m_vScale.x > 0.f && m_vScale.y > 0.f && m_vScale.z > 0.f)
			{
				m_vScale.x = m_vPos.x / m_fStartRadius;
				m_vScale.y = m_vPos.x / m_fStartRadius;
				m_vScale.z = m_vPos.x / m_fStartRadius;
			}
			else
				m_bLife = false;
			break;



		case YELLOW_RING:
			if (m_vScale.x > 0.f && m_vScale.y > 0.f && m_vScale.z > 0.f)
			{
				m_vScale.x -= 0.9f;
				m_vScale.y -= 0.9f;
				m_vScale.z -= 0.9f;
				// UpdateAlpah 에서 지움.
			}
			else
			{
				m_bLife = false;
				g_pEffectManager->SetYellowRing(false);
			}
			break;


		case COUNT_ATK:

			D3DXMatrixIdentity(&matRY);
			D3DXMatrixIdentity(&matRX);
			D3DXMatrixIdentity(&matRZ);
			D3DXMatrixRotationY(&matRY, D3DXToRadian(m_vAngle.y));
			D3DXMatrixRotationZ(&matRX, D3DXToRadian(-270));

			m_matR = matRY * matRX;

			if (m_vScale.x < m_fMaxSize)
			{
				m_vScale.x += 0.045f;
				m_vScale.y += 0.045f;
				m_vScale.z += 0.045f;
				m_fAlpha -= 10.f;
				if (!m_isRedCircle)
					m_vMoveDir.x += 0.5f;
				else
					m_vMoveDir.x += 0.25f;
			}
			else
				m_bLife = false;
			break;

		case DUST:
			m_vPos.x += m_vMoveDir.x;
			m_vPos.y += m_vMoveDir.y;
			m_vPos.z += m_vMoveDir.z;
			m_vScale.x += m_vIncreaseScale.x;
			m_vScale.y += m_vIncreaseScale.y;
			m_vScale.z += m_vIncreaseScale.z;

			break;

		case FIRE_BALL_EGG:

			D3DXMatrixIdentity(&matRZ);
			D3DXMatrixRotationZ(&matRZ, D3DXToRadian(m_vAngle.z));
			m_matR = matRZ;
			m_vAngle.z += 1.f;
			if (m_fLifeCount <= 0)
				m_bLife = false;
			else
				m_fLifeCount -= g_fDeltaTime;
			break;

		case FIRE_CLOUDE:
			if (m_vScale.x >= m_fMaxSize)
				m_bLife = false;
			else
			{

				D3DXMatrixIdentity(&matRZ);
				D3DXMatrixRotationZ(&matRZ, D3DXToRadian(m_vAngle.z));
				m_matR = matRZ;
				m_vAngle.z += 1.f;
				m_fAlpha -= 5.f;
				m_vPos.y += m_MoveSpeed;
				m_vScale.x += m_vIncreaseScale.x;
				m_vScale.y += m_vIncreaseScale.y;
				m_vScale.z += m_vIncreaseScale.z;
			}
			break;

		case FIRE_Tail:

			if (m_vScale.x <= 0.f)
				m_bLife = false;
			else
			{
				D3DXMatrixIdentity(&matRZ);
				D3DXMatrixRotationZ(&matRZ, D3DXToRadian(m_vAngle.z));
				m_matR = matRZ;
				m_vAngle.z += 1.f;

				m_vPos.y += m_MoveSpeed;
				m_vScale.x -= m_vDecreaseScale.x;
				m_vScale.y -= m_vDecreaseScale.y;
				m_vScale.z -= m_vDecreaseScale.z;
			}
			break;

		case BLAST:						// 16
		case BLAST_DUST:				// 17
			if (m_vScale.x >= m_fMaxSize)
				m_bLife = false;
			else
			{
				m_vPos.y += m_vIncreaseScale.x;
				m_fAlpha -= 5.f;
				m_vScale.x += m_vIncreaseScale.x;
				m_vScale.y += m_vIncreaseScale.y;
				m_vScale.z += m_vIncreaseScale.z;
			}
			break;
		case BLAST_CLOUD:				// 18
			if (m_vScale.x >= m_fMaxSize)
				m_bLife = false;
			else
			{
				m_fAlpha -= 5.f;
				m_vScale.x += m_vIncreaseScale.x;
				m_vScale.y += m_vIncreaseScale.y;
				m_vScale.z += m_vIncreaseScale.z;
			}
			break;


		}
	}
}



