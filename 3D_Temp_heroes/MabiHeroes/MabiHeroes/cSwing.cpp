#include "stdafx.h"
#include "cSwing.h"


cSwing::cSwing()
{
}


cSwing::~cSwing()
{
}
void cSwing::AddSwing(string CreatureName, D3DXVECTOR3 vecUp, D3DXVECTOR3 vecDown, bool isWhite)
{
	vector<stSwting>*		pTemp;
	vector<stSwingRect>*	pTempRect;
	pTemp = &m_mapSwing[CreatureName];
	pTemp->push_back(stSwting(vecUp, vecDown));

	int size = pTemp->size();
	if (size >= 2)
	{
		pTempRect = &m_mapSwingRect[CreatureName];
		int Rectsize = pTempRect->size();
		if (Rectsize < size)
		{
			stSwingRect tempRect;
			tempRect.stRectSwing.clear();
			tempRect.stbLife = true;
			tempRect.stfAlpha = 255;
			tempRect.stCreatureName = CreatureName;
			tempRect.stIsWhite = isWhite;


			ST_PCT_VERTEX temp;
			temp.c = D3DCOLOR_ARGB(255, 255, 255, 255);
			temp.p = (*pTemp)[pTemp->size() - 1].stUpVec;
			temp.t = { 1, 0 };
			tempRect.stRectSwing.push_back(temp);

			temp.c = D3DCOLOR_ARGB(255, 255, 255, 255);
			temp.p = (*pTemp)[pTemp->size() - 1].stDownVec;
			temp.t = { 1, 1 };
			tempRect.stRectSwing.push_back(temp);

			temp.c = D3DCOLOR_ARGB(255, 255, 255, 255);
			temp.p = (*pTemp)[pTemp->size() - 2].stDownVec;
			temp.t = { 0, 1 };
			tempRect.stRectSwing.push_back(temp);

			temp.c = D3DCOLOR_ARGB(255, 255, 255, 255);
			temp.p = (*pTemp)[pTemp->size() - 2].stDownVec;
			temp.t = { 0, 1 };
			tempRect.stRectSwing.push_back(temp);

			temp.c = D3DCOLOR_ARGB(255, 255, 255, 255);
			temp.p = (*pTemp)[pTemp->size() - 2].stUpVec;
			temp.t = { 0, 0 };
			tempRect.stRectSwing.push_back(temp);

			temp.c = D3DCOLOR_ARGB(255, 255, 255, 255);
			temp.p = (*pTemp)[pTemp->size() - 1].stUpVec;
			temp.t = { 1, 0 };
			tempRect.stRectSwing.push_back(temp);


			pTempRect->push_back(tempRect);

			for (int i = 0; i < pTempRect->size(); ++i)
			{
				if (i == 0)
				{
					vector<stSwingRect>* temp1 = &m_mapSwingRect[CreatureName];
					vector<ST_PCT_VERTEX>* temp2 = &(*temp1)[i].stRectSwing;

					temp.c = D3DCOLOR_ARGB(255, 255, 255, 255);
					temp.p = (*pTemp)[pTemp->size() - 1].stUpVec;
					temp.t = { 1, 0 };
					(*temp2).push_back(temp);


					temp.c = D3DCOLOR_ARGB(255, 255, 255, 255);
					temp.p = (*pTemp)[pTemp->size() - 1].stDownVec;
					temp.t = { 1, 1 };
					(*temp2).push_back(temp);


					temp.c = D3DCOLOR_ARGB(255, 255, 255, 255);
					temp.p = (*pTemp)[pTemp->size() - 2].stDownVec;
					temp.t = { 0, 1 };
					(*temp2).push_back(temp);

					temp.c = D3DCOLOR_ARGB(255, 255, 255, 255);
					temp.p = (*pTemp)[pTemp->size() - 2].stDownVec;
					temp.t = { 0, 1 };
					(*temp2).push_back(temp);

					temp.c = D3DCOLOR_ARGB(255, 255, 255, 255);
					temp.p = (*pTemp)[pTemp->size() - 2].stUpVec;
					temp.t = { 0, 0 };
					(*temp2).push_back(temp);


					temp.c = D3DCOLOR_ARGB(255, 255, 255, 255);
					temp.p = (*pTemp)[pTemp->size() - 1].stUpVec;
					temp.t = { 1, 0 };
					(*temp2).push_back(temp);


					int changeSize = (*temp1)[i].stRectSwing.size();
					int forNum = (changeSize - 1) / 6;
					int circleA = (changeSize + 5) / 6;
					for (int o = 0; o < forNum; ++o)
					{
						float t_A = (float)(1.f / float(forNum + 1)) * (float)(o + 1);
						float t_B = (float)(1.f / float(forNum + 1)) * (float)(o);

						(*temp1)[i].stfAlpha = 255.f;
						(*temp1)[i].stfDeleteTime = 0.f;
						(*temp1)[i].stRectSwing[(6 * (o + 1)) - 1].t = { t_A, 0 };
						(*temp1)[i].stRectSwing[(6 * (o + 1)) - 2].t = { t_B, 0 };
						(*temp1)[i].stRectSwing[(6 * (o + 1)) - 3].t = { t_B , 1 };
						(*temp1)[i].stRectSwing[(6 * (o + 1)) - 4].t = { t_B , 1 };
						(*temp1)[i].stRectSwing[(6 * (o + 1)) - 5].t = { t_A , 1 };
						(*temp1)[i].stRectSwing[(6 * (o + 1)) - 6].t = { t_A, 0 };
					}
				}
			}
		}
	}
}

void cSwing::Update()
{
	for (m_mapiSwingRect = m_mapSwingRect.begin(); m_mapiSwingRect != m_mapSwingRect.end();)
	{
		vector<stSwingRect>* tempSwingRt = &(*m_mapiSwingRect).second;


		if (tempSwingRt[0].size())
		{

			if ((*tempSwingRt)[0].stfAlpha < 31)
			{
				m_mapSwing[(*m_mapiSwingRect).second[0].stCreatureName].clear();
				m_mapiSwingRect = m_mapSwingRect.erase(m_mapiSwingRect);
			}
			else
			{
				(*tempSwingRt)[0].stfAlpha -= 30;
				int size = (*tempSwingRt)[0].stRectSwing.size();
				for (int io = 0; io < size; ++io)
				{
					(*m_mapiSwingRect).second[0].stRectSwing[io].c = D3DCOLOR_ARGB((*tempSwingRt)[0].stfAlpha, (*tempSwingRt)[0].stfAlpha, (*tempSwingRt)[0].stfAlpha, (*tempSwingRt)[0].stfAlpha);
				}

				++m_mapiSwingRect;
			}			
		}
	}
}

void cSwing::Reder()
{


	g_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);


	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);




	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetFVF(ST_PCT_VERTEX::FVF);

	for (m_mapiSwingRect = m_mapSwingRect.begin(); m_mapiSwingRect != m_mapSwingRect.end(); ++m_mapiSwingRect)
	{

		vector<stSwingRect>* tempSwingRt = &m_mapiSwingRect->second;
		int size = tempSwingRt->size();

		if ((*tempSwingRt).size())
		{
			vector<ST_PCT_VERTEX> tempSaveVec;
			int sz = ((*tempSwingRt)[0].stRectSwing.size()) * 2;
			tempSaveVec.resize(sz);

			for (int i = 0; i < sz / 2; ++i)
			{
				tempSaveVec[i] = (*tempSwingRt)[0].stRectSwing[i];
			}

			
			for (int i = sz / 2; i < sz; i += 6)
			{
				tempSaveVec[i + 0] = (*tempSwingRt)[0].stRectSwing[i - (sz / 2) + 0];
				tempSaveVec[i + 1] = (*tempSwingRt)[0].stRectSwing[i - (sz / 2) + 2];
				tempSaveVec[i + 2] = (*tempSwingRt)[0].stRectSwing[i - (sz / 2) + 1];
				tempSaveVec[i + 3] = (*tempSwingRt)[0].stRectSwing[i - (sz / 2) + 3];
				tempSaveVec[i + 4] = (*tempSwingRt)[0].stRectSwing[i - (sz / 2) + 5];
				tempSaveVec[i + 5] = (*tempSwingRt)[0].stRectSwing[i - (sz / 2) + 4];
			}

			if( (*m_mapiSwingRect).second[(*m_mapiSwingRect).second.size() - 1].stIsWhite)
				g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture("./EffectImage/swing2.png"));
			else
				g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture("./EffectImage/swing1.png"));


			g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
				sz / 3,
				&tempSaveVec[0],
				sizeof(ST_PCT_VERTEX));

		}
	}


	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}
