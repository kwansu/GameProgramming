#include "stdafx.h"
#include "cTerrain.h"


cTerrain::cTerrain()
	: m_pMesh(NULL)
{
}


cTerrain::~cTerrain()
{
}

void cTerrain::Setup()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	
	if (!m_pMesh)
	{
		ST_SPHERE a;
		m_pMesh = new cSkinnedMesh;
		m_pMesh->Load("./MapData/", "map.X", a);
	}

	D3DXMatrixScaling(&matWorld, 0.1f, 0.1f, 0.1f);

	matWorld._41 = -30;
	matWorld._42 = -10;

	m_pMesh->Update(matWorld);
}

void cTerrain::Render()
{
	m_pMesh->Render();
}
