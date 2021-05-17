#include "stdafx.h"
#include "cObject_Mole.h"


int* cObject_Mole::s_pActiveCount = NULL;
int* cObject_Mole::s_pDeathCount = NULL;

cObject_Mole::cObject_Mole()
	: m_bActice(false), m_nLive(0)
{
	D3DXMatrixScaling(&m_matScale, 3.5f, MOLE_HEIGHT, 3.5f);
	g_pGraphics->GetPumpkin(&m_pTexture);

	m_aVertexPT.push_back(stVertex_PT(cVec3(-1, -1, 1), cVec2(1 / 3.f, 1)));
	m_aVertexPT.push_back(stVertex_PT(cVec3(-1, 1, 1), cVec2(1 / 3.f, 0.5f)));
	m_aVertexPT.push_back(stVertex_PT(cVec3(-1, 1, -1), cVec2(2 / 3.f, 0.5f)));
	m_aVertexPT.push_back(stVertex_PT(cVec3(-1, -1, 1), cVec2(1 / 3.f, 1)));
	m_aVertexPT.push_back(stVertex_PT(cVec3(-1, 1, -1), cVec2(2 / 3.f, 0.5f)));
	m_aVertexPT.push_back(stVertex_PT(cVec3(-1, -1, -1), cVec2(2 / 3.f, 1)));

	m_aVertexPT.push_back(stVertex_PT(cVec3(-1, 1, -1), cVec2(0, 0.5f)));
	m_aVertexPT.push_back(stVertex_PT(cVec3(-1, 1, 1), cVec2(0, 0)));
	m_aVertexPT.push_back(stVertex_PT(cVec3(1, 1, 1), cVec2(1/3.f, 0)));
	m_aVertexPT.push_back(stVertex_PT(cVec3(-1, 1, -1), cVec2(0, 0.5f)));
	m_aVertexPT.push_back(stVertex_PT(cVec3(1, 1, 1), cVec2(1 / 3.f, 0)));
	m_aVertexPT.push_back(stVertex_PT(cVec3(1, 1, -1), cVec2(1/3.f, 0.5f)));

	m_aVertexPT.push_back(stVertex_PT(cVec3(1, -1, -1), cVec2(0, 1)));
	m_aVertexPT.push_back(stVertex_PT(cVec3(1, 1, -1), cVec2(0, 0.5f)));
	m_aVertexPT.push_back(stVertex_PT(cVec3(1, 1, 1), cVec2(1/3.f, 0.5f)));
	m_aVertexPT.push_back(stVertex_PT(cVec3(1, -1, -1), cVec2(0, 1)));
	m_aVertexPT.push_back(stVertex_PT(cVec3(1, 1, 1), cVec2(1 / 3.f, 0.5f)));
	m_aVertexPT.push_back(stVertex_PT(cVec3(1, -1, 1), cVec2(1/3.f, 1)));

	m_aVertexPT.push_back(stVertex_PT(cVec3(-1, -1, 1), cVec2(0, 1)));
	m_aVertexPT.push_back(stVertex_PT(cVec3(1, 1, 1), cVec2(1 / 3.f, 0.5f)));
	m_aVertexPT.push_back(stVertex_PT(cVec3(-1, 1, 1), cVec2(0, 0.5f)));
	m_aVertexPT.push_back(stVertex_PT(cVec3(-1, -1, 1), cVec2(0, 1)));
	m_aVertexPT.push_back(stVertex_PT(cVec3(1, -1, 1), cVec2(1 / 3.f, 1)));
	m_aVertexPT.push_back(stVertex_PT(cVec3(1, 1, 1), cVec2(1 / 3.f, 0.5f)));

	m_aVertexPT.push_back(stVertex_PT(cVec3(-1, -1, -1), cVec2(1 / 3.f, 1)));
	m_aVertexPT.push_back(stVertex_PT(cVec3(-1, 1, -1), cVec2(1 / 3.f, 0.5f)));
	m_aVertexPT.push_back(stVertex_PT(cVec3(1, 1, -1), cVec2(0, 0.5f)));
	m_aVertexPT.push_back(stVertex_PT(cVec3(-1, -1, -1), cVec2(1 / 3.f, 1)));
	m_aVertexPT.push_back(stVertex_PT(cVec3(1, 1, -1), cVec2(0, 0.5f)));
	m_aVertexPT.push_back(stVertex_PT(cVec3(1, -1, -1), cVec2(0, 1)));
}


cObject_Mole::~cObject_Mole()
{
}


void cObject_Mole::Setup()
{
	m_aVertexPT[0].texPos = cVec2(1 / 3.f, 1);
	m_aVertexPT[1].texPos = cVec2(1 / 3.f, 0.5f);
	m_aVertexPT[2].texPos = cVec2(2 / 3.f, 0.5f);
	m_aVertexPT[3].texPos = cVec2(1 / 3.f, 1);
	m_aVertexPT[4].texPos = cVec2(2 / 3.f, 0.5f);
	m_aVertexPT[5].texPos = cVec2(2 / 3.f, 1);

	m_nLive = g_nStage;
	m_bActice = true;
	m_bUp = true;
	(*s_pActiveCount)++;

	m_tEventTime = g_tCurrentTime + (rand() % ((MOLE_ACTIVE_TIME)/g_nStage));
}


void cObject_Mole::Update()
{
	if (m_bActice)
	{
		if (m_nLive)
		{
			if (g_tCurrentTime >= m_tEventTime)
				m_vecPos.y += MOLE_MOVE_SPEED * (m_bUp ? 1 : -1);

			if (m_bUp && m_vecPos.y >= MOLE_HEIGHT)
			{
				m_bUp = false;
				m_tEventTime = g_tCurrentTime + MOLE_IDLE_TIME;
			}
		}
		else
			m_vecPos.y -= MOLE_MOVE_SPEED;

		if (m_vecPos.y <= -MOLE_HEIGHT)
		{
			m_bActice = false;
			--(*s_pActiveCount);
			if (m_nLive > 0 && !m_bUp)
				--(*s_pDeathCount);
		}
	}

	UpdateWorldMatrix();
}


void cObject_Mole::Render()
{
	cObject_Cube::Render();
}


void cObject_Mole::Collision()
{
	--m_nLive;

	g_bCollision = true;

	if (!m_nLive)
	{
		m_aVertexPT[0].texPos = cVec2(1, 1);
		m_aVertexPT[1].texPos = cVec2(1, 0.5f);
		m_aVertexPT[2].texPos = cVec2(2 / 3.f, 0.5f);
		m_aVertexPT[3].texPos = cVec2(1, 1);
		m_aVertexPT[4].texPos = cVec2(2 / 3.f, 0.5f);
		m_aVertexPT[5].texPos = cVec2(2 / 3.f, 1);
	}
}


bool cObject_Mole::IsLive()
{
	return m_nLive;
}
