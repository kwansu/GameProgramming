#include "stdafx.h"
#include "cObject_Cube.h"


cObject_Cube::cObject_Cube()
	: m_pTexture(NULL)
{
	m_aLocalPos.push_back(cVec3(-1, -1, -1));
	m_aLocalPos.push_back(cVec3(-1,  1, -1));
	m_aLocalPos.push_back(cVec3( 1,  1, -1));
	m_aLocalPos.push_back(cVec3( 1, -1, -1));
	m_aLocalPos.push_back(cVec3(-1, -1,  1));
	m_aLocalPos.push_back(cVec3(-1,  1,  1));
	m_aLocalPos.push_back(cVec3( 1,  1,  1));
	m_aLocalPos.push_back(cVec3( 1, -1,  1));

	D3DCOLOR c;
	c = D3DCOLOR_XRGB(53, 53, 53);
	m_aVertexPC.push_back(stVertex_PC(D3DXVECTOR3(-1, -1, -1), c));
	m_aVertexPC.push_back(stVertex_PC(D3DXVECTOR3(-1, 1, -1), c));
	m_aVertexPC.push_back(stVertex_PC(D3DXVECTOR3(1, 1, -1), c));
	m_aVertexPC.push_back(stVertex_PC(D3DXVECTOR3(-1, -1, -1), c));
	m_aVertexPC.push_back(stVertex_PC(D3DXVECTOR3(1, 1, -1), c));
	m_aVertexPC.push_back(stVertex_PC(D3DXVECTOR3(1, -1, -1), c));

	c = D3DCOLOR_XRGB(83, 83, 83);
	m_aVertexPC.push_back(stVertex_PC(D3DXVECTOR3(-1, -1, 1), c));
	m_aVertexPC.push_back(stVertex_PC(D3DXVECTOR3(1, 1, 1), c));
	m_aVertexPC.push_back(stVertex_PC(D3DXVECTOR3(-1, 1, 1), c));
	m_aVertexPC.push_back(stVertex_PC(D3DXVECTOR3(-1, -1, 1), c));
	m_aVertexPC.push_back(stVertex_PC(D3DXVECTOR3(1, -1, 1), c));
	m_aVertexPC.push_back(stVertex_PC(D3DXVECTOR3(1, 1, 1), c));

	c = D3DCOLOR_XRGB(113, 113, 113);
	m_aVertexPC.push_back(stVertex_PC(D3DXVECTOR3(-1, -1, 1), c));
	m_aVertexPC.push_back(stVertex_PC(D3DXVECTOR3(-1, 1, 1), c));
	m_aVertexPC.push_back(stVertex_PC(D3DXVECTOR3(-1, 1, -1), c));
	m_aVertexPC.push_back(stVertex_PC(D3DXVECTOR3(-1, -1, 1), c));
	m_aVertexPC.push_back(stVertex_PC(D3DXVECTOR3(-1, 1, -1), c));
	m_aVertexPC.push_back(stVertex_PC(D3DXVECTOR3(-1, -1, -1), c));

	c = D3DCOLOR_XRGB(143, 143, 143);
	m_aVertexPC.push_back(stVertex_PC(D3DXVECTOR3(1, -1, -1), c));
	m_aVertexPC.push_back(stVertex_PC(D3DXVECTOR3(1, 1, -1), c));
	m_aVertexPC.push_back(stVertex_PC(D3DXVECTOR3(1, 1, 1), c));
	m_aVertexPC.push_back(stVertex_PC(D3DXVECTOR3(1, -1, -1), c));
	m_aVertexPC.push_back(stVertex_PC(D3DXVECTOR3(1, 1, 1), c));
	m_aVertexPC.push_back(stVertex_PC(D3DXVECTOR3(1, -1, 1), c));

	c = D3DCOLOR_XRGB(173, 173, 173);
	m_aVertexPC.push_back(stVertex_PC(D3DXVECTOR3(-1, 1, -1), c));
	m_aVertexPC.push_back(stVertex_PC(D3DXVECTOR3(-1, 1, 1), c));
	m_aVertexPC.push_back(stVertex_PC(D3DXVECTOR3(1, 1, 1), c));
	m_aVertexPC.push_back(stVertex_PC(D3DXVECTOR3(-1, 1, -1), c));
	m_aVertexPC.push_back(stVertex_PC(D3DXVECTOR3(1, 1, 1), c));
	m_aVertexPC.push_back(stVertex_PC(D3DXVECTOR3(1, 1, -1), c));

	c = D3DCOLOR_XRGB(203, 203, 203);
	m_aVertexPC.push_back(stVertex_PC(D3DXVECTOR3(-1, -1, 1), c));
	m_aVertexPC.push_back(stVertex_PC(D3DXVECTOR3(-1, -1, -1), c));
	m_aVertexPC.push_back(stVertex_PC(D3DXVECTOR3(1, -1, -1), c));
	m_aVertexPC.push_back(stVertex_PC(D3DXVECTOR3(-1, -1, 1), c));
	m_aVertexPC.push_back(stVertex_PC(D3DXVECTOR3(1, -1, -1), c));
	m_aVertexPC.push_back(stVertex_PC(D3DXVECTOR3(1, -1, 1), c));
}


cObject_Cube::~cObject_Cube()
{
	g_pGraphics->GetPumpkin(&m_pTexture);
}


void cObject_Cube::Setup()
{
}


void cObject_Cube::Update()
{
}


void cObject_Cube::Render()
{
	g_pDDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	if (m_pTexture)
	{
		g_pDDevice->SetTexture(0, m_pTexture);
		g_pDDevice->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
		g_pDDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
			m_aVertexPT.size() / 3, &m_aVertexPT[0], sizeof(stVertex_PT));
		g_pDDevice->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
	}
	else
	{
		g_pDDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
			m_aVertexPC.size() / 3, &m_aVertexPC[0], sizeof(stVertex_PC));
	}
}


bool cObject_Cube::CubeCollision(cObject_Cube* pObject)
{
	UpdateDirectionVector();
	pObject->UpdateDirectionVector();
	
	for (int i = 0; i < 8; ++i)
	{
		cVec3 vecPos1 = m_aLocalPos[6];
		cVec3 vecPos2 = m_aLocalPos[i];

		TransformVector(&vecPos1);
		pObject->TransformVector(&vecPos2);
		cVec3 vecPositive = vecPos1 - vecPos2;

		vecPos1 = m_aLocalPos[0];
		TransformVector(&vecPos1);
		cVec3 vecNegative = vecPos1 - vecPos2;

		if (D3DXVec3Dot(&vecPositive, &m_vecLook) < 0) continue;
		if (D3DXVec3Dot(&vecPositive, &m_vecUp) < 0) continue;
		if (D3DXVec3Dot(&vecPositive, &m_vecRight) < 0) continue;
		if (D3DXVec3Dot(&vecNegative, &m_vecLook) > 0) continue;
		if (D3DXVec3Dot(&vecNegative, &m_vecUp) > 0) continue;
		if (D3DXVec3Dot(&vecNegative, &m_vecRight) > 0) continue;
		
		return true;
	}
	return false;
}


bool cObject_Cube::IsCollision(cObject_Cube* pObject)
{
	return (CubeCollision(pObject) || pObject->CubeCollision(this));
}
