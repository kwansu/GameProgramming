#include "stdafx.h"
#include "cStep.h"


cStep::cStep()
{
	m_ID = "STEP";
}


cStep::~cStep()
{
}

void cStep::Setup()
{
	m_pMesh = new cSkinnedMesh;
	ST_SPHERE a;
	m_pMesh->Load("./MapData/woodHouse/", "woodHouse.X", a);
}

void cStep::Update()
{
	UpdateTransform();
	m_pMesh->Update(m_matWorld);
}

void cStep::Render()
{
	if (m_pMesh)
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
		m_pMesh->RenderInAnimateObject();
	}
}
