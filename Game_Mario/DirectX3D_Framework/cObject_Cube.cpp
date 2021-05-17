#include "stdafx.h"
#include "cObject_Cube.h"


cObject_Cube::cObject_Cube()
	: m_pCollider(NULL)
{
	m_aLocalPos.push_back(cVec3(-1, -1, -1));
	m_aLocalPos.push_back(cVec3(-1, 1, -1));
	m_aLocalPos.push_back(cVec3(1, 1, -1));
	m_aLocalPos.push_back(cVec3(1, -1, -1));
	m_aLocalPos.push_back(cVec3(-1, -1, 1));
	m_aLocalPos.push_back(cVec3(-1, 1, 1));
	m_aLocalPos.push_back(cVec3(1, 1, 1));
	m_aLocalPos.push_back(cVec3(1, -1, 1));

	D3DCOLOR c;
	c = D3DCOLOR_XRGB(210, 210, 210);
	m_aVertexPC.push_back(Vertex_PC(cVec3(-1, -1, -1), c));
	m_aVertexPC.push_back(Vertex_PC(cVec3(-1, 1, -1), c));
	m_aVertexPC.push_back(Vertex_PC(cVec3(1, 1, -1), c));
	m_aVertexPC.push_back(Vertex_PC(cVec3(-1, -1, -1), c));
	m_aVertexPC.push_back(Vertex_PC(cVec3(1, 1, -1), c));
	m_aVertexPC.push_back(Vertex_PC(cVec3(1, -1, -1), c));

	c = D3DCOLOR_XRGB(83, 83, 83);
	m_aVertexPC.push_back(Vertex_PC(cVec3(-1, -1, 1), c));
	m_aVertexPC.push_back(Vertex_PC(cVec3(1, 1, 1), c));
	m_aVertexPC.push_back(Vertex_PC(cVec3(-1, 1, 1), c));
	m_aVertexPC.push_back(Vertex_PC(cVec3(-1, -1, 1), c));
	m_aVertexPC.push_back(Vertex_PC(cVec3(1, -1, 1), c));
	m_aVertexPC.push_back(Vertex_PC(cVec3(1, 1, 1), c));

	c = D3DCOLOR_XRGB(113, 113, 113);
	m_aVertexPC.push_back(Vertex_PC(cVec3(-1, -1, 1), c));
	m_aVertexPC.push_back(Vertex_PC(cVec3(-1, 1, 1), c));
	m_aVertexPC.push_back(Vertex_PC(cVec3(-1, 1, -1), c));
	m_aVertexPC.push_back(Vertex_PC(cVec3(-1, -1, 1), c));
	m_aVertexPC.push_back(Vertex_PC(cVec3(-1, 1, -1), c));
	m_aVertexPC.push_back(Vertex_PC(cVec3(-1, -1, -1), c));

	c = D3DCOLOR_XRGB(143, 143, 143);
	m_aVertexPC.push_back(Vertex_PC(cVec3(1, -1, -1), c));
	m_aVertexPC.push_back(Vertex_PC(cVec3(1, 1, -1), c));
	m_aVertexPC.push_back(Vertex_PC(cVec3(1, 1, 1), c));
	m_aVertexPC.push_back(Vertex_PC(cVec3(1, -1, -1), c));
	m_aVertexPC.push_back(Vertex_PC(cVec3(1, 1, 1), c));
	m_aVertexPC.push_back(Vertex_PC(cVec3(1, -1, 1), c));

	c = D3DCOLOR_XRGB(173, 173, 173);
	m_aVertexPC.push_back(Vertex_PC(cVec3(-1, 1, -1), c));
	m_aVertexPC.push_back(Vertex_PC(cVec3(-1, 1, 1), c));
	m_aVertexPC.push_back(Vertex_PC(cVec3(1, 1, 1), c));
	m_aVertexPC.push_back(Vertex_PC(cVec3(-1, 1, -1), c));
	m_aVertexPC.push_back(Vertex_PC(cVec3(1, 1, 1), c));
	m_aVertexPC.push_back(Vertex_PC(cVec3(1, 1, -1), c));

	c = D3DCOLOR_XRGB(203, 203, 203);
	m_aVertexPC.push_back(Vertex_PC(cVec3(-1, -1, 1), c));
	m_aVertexPC.push_back(Vertex_PC(cVec3(-1, -1, -1), c));
	m_aVertexPC.push_back(Vertex_PC(cVec3(1, -1, -1), c));
	m_aVertexPC.push_back(Vertex_PC(cVec3(-1, -1, 1), c));
	m_aVertexPC.push_back(Vertex_PC(cVec3(1, -1, -1), c));
	m_aVertexPC.push_back(Vertex_PC(cVec3(1, -1, 1), c));
}


cObject_Cube::~cObject_Cube()
{
	SAFE_DELETE(m_pCollider);
}


void cObject_Cube::Setup()
{
}


void cObject_Cube::Update()
{
}


void cObject_Cube::Render()
{
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWolrd);
	g_pDevice->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_aVertexPC.size() / 3, &m_aVertexPC[0], sizeof(Vertex_PC));
}


bool cObject_Cube::CubeCollision(cObject_Cube* pObject)
{
	UpdateDirection();
	pObject->UpdateDirection();

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

		if (D3DXVec3Dot(&vecPositive, &m_vLook) < 0) continue;
		if (D3DXVec3Dot(&vecPositive, &m_vUp) < 0) continue;
		if (D3DXVec3Dot(&vecPositive, &m_vRight) < 0) continue;
		if (D3DXVec3Dot(&vecNegative, &m_vLook) > 0) continue;
		if (D3DXVec3Dot(&vecNegative, &m_vUp) > 0) continue;
		if (D3DXVec3Dot(&vecNegative, &m_vRight) > 0) continue;

		return true;
	}
	return false;
}


bool cObject_Cube::IsCollision(cObject_Cube* pObject)
{
	return (CubeCollision(pObject) || pObject->CubeCollision(this));
}

bool cObject_Cube::CollisionDetection(cVec3* pvOut, cObject_Cube* pConflictor)
{
	cVec3 vMin, vMax, vMinT, vMaxT;
	TransformVertexMin(&vMin);
	TransformVertexMax(&vMax);
	pConflictor->TransformVertexMin(&vMinT);
	pConflictor->TransformVertexMax(&vMaxT);
	
	if (vMin.x > vMaxT.x || vMinT.x > vMax.x)	
		return false;
	pvOut->x = (vMax.x - vMinT.x > vMaxT.x - vMin.x) ?
		vMaxT.x - vMin.x : -(vMax.x - vMinT.x);

	if (vMin.y > vMaxT.y || vMinT.y > vMax.y)	
		return false;
	pvOut->y = (vMax.y - vMinT.y > vMaxT.y - vMin.y) ?
		vMaxT.y - vMin.y : -(vMax.y - vMinT.y);

	if (vMin.z > vMaxT.z || vMinT.z > vMax.z)	
		return false;
	pvOut->z = (vMax.z - vMinT.z > vMaxT.z - vMin.z) ?
		vMaxT.z - vMin.z : -(vMax.z - vMinT.z);

	return true;
}


void cObject_Cube::TransformVertexMin(cVec3* pvOut)
{
	cVec3 vTrans;

	D3DXVec3TransformCoord(pvOut, &m_aLocalPos[0], &m_matWolrd);
	for (int i = 1; i < 8; ++i)
	{
		D3DXVec3TransformCoord(&vTrans, &m_aLocalPos[i], &m_matWolrd);
		D3DXVec3Minimize(pvOut, pvOut, &vTrans);
	}
}


void cObject_Cube::TransformVertexMax(cVec3* pvOut)
{
	cVec3 vTrans;

	for (int i = 0; i < 8; ++i)
	{
		D3DXVec3TransformCoord(&vTrans, &m_aLocalPos[i], &m_matWolrd);
		D3DXVec3Maximize(pvOut, pvOut, &vTrans);
	}
}



void cObject_Cube::SetLocalSize(float sx, float sy, float sz)
{
	int size = m_aVertexPC.size();
	for (int i = 0; i < size; ++i)
	{
		m_aVertexPC[i].pos.x *= sx;
		m_aVertexPC[i].pos.y *= sy;
		m_aVertexPC[i].pos.z *= sz;
	}
	size = m_aLocalPos.size();
	for (int i = 0; i < size; ++i)
	{
		m_aLocalPos[i].x *= sx;
		m_aLocalPos[i].y *= sy;
		m_aLocalPos[i].z *= sz;
	}
}


cCollider* cObject_Cube::GetCollider()
{
	if (m_pCollider)
		return m_pCollider;

	return NULL;
}
