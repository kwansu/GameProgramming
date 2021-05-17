#include "stdafx.h"
#include "cSparkParticle.h"

#define MAX_SAMPLE 100
cSparkParticle::cSparkParticle()
{
	m_vParticle.resize(MAX_SAMPLE);
	m_vStParticle.resize(MAX_SAMPLE);

	D3DXMatrixIdentity(&m_matWorld);
	for (int i = 0; i < MAX_SAMPLE; ++i)
	{
		ST_PC_VERTEX pcVectex = ST_PC_VERTEX();
		int rnd = rand() % MAX_SAMPLE;
		pcVectex.p.x = 0.1f;
		pcVectex.p.y = 20.f;
		pcVectex.p.z = 0.1f;
		pcVectex.c = D3DCOLOR_ARGB(255, 255, 255, 255);
		//D3DXVec3TransformCoord(&pcVectex.p, &pcVectex.p, &matWorld);
		m_vParticle[i] = pcVectex;


		stParticle* temp = new stParticle;
		temp->m_vecpParticle =  &(m_vParticle[ i ].p);
		temp->m_fSpeed = 0.1f;
		temp->m_fGravity = 0.05f;
		temp->m_fLifeCount = (MAX_SAMPLE - i) * 0.03f;
		temp->m_fRemainCount = 0.5f;
		m_vStParticle[i] = temp;;
	}

}


cSparkParticle::~cSparkParticle()
{
	m_vStParticle.clear();
}

void cSparkParticle::Setup()
{
}

void cSparkParticle::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, false);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture("./EffectImage/texture.png"));
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	// 소스 추가
	if (m_vParticle.size())
	{
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_POINTLIST,
			m_vParticle.size(),
			&m_vParticle[0],
			sizeof(ST_PC_VERTEX));
	}
	//

	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

void cSparkParticle::Update()
{
	int size = m_vStParticle.size();
	float tickTime = g_pTimeManager->GetDeltaTime();
	m_viParticle = m_vParticle.begin();
	for (m_viStParticle = m_vStParticle.begin(); m_viStParticle < m_vStParticle.end(); ++m_viStParticle, ++m_viParticle)
	{
		if ((*m_viStParticle)->m_fLifeCount > 0)
		{
			(*m_viStParticle)->m_vecpParticle->x += 0.03f;
			(*m_viStParticle)->m_fLifeCount -= tickTime;
		}
		else
		{
			if ((*m_viStParticle)->m_fRemainCount > 0)
			{
				(*m_viStParticle)->m_fRemainCount -= tickTime;
			}
			else
			{
				m_viStParticle = m_vStParticle.erase(m_viStParticle);
				m_vParticle.erase(m_viParticle);
				break;
			}
		}
	}
	
}
