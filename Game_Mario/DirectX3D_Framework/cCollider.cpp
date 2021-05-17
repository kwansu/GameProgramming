#include "stdafx.h"
#include "cCollider.h"


cCollider::cCollider(cMatrixA* pmatWorld)
	: m_aVertex(NULL), m_pmatWorld(NULL)
{
	m_pmatWorld = pmatWorld;
}


cCollider::~cCollider()
{
}


void cCollider::Setup(vector<cVec3>* paVertex)
{
	int size = paVertex->size();
	for (int i = 0; i < size; ++i)
		m_aVertex.push_back((*paVertex)[i]);
}


void cCollider::Update()
{
	m_vMin = cVec3(FLT_MAX, FLT_MAX, FLT_MAX);
	m_vMax = cVec3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
	cVec3 vTransMax, vTransMin;

	int size = m_aVertex.size();

	D3DXVec3TransformCoord(&vTransMin, &m_aVertex[0], m_pmatWorld);
	D3DXVec3TransformCoord(&vTransMax, &m_aVertex[0], m_pmatWorld);

	for (int i = 1; i < size; ++i)
	{
		D3DXVec3TransformCoord(&vTransMin, &m_aVertex[i], m_pmatWorld);
		D3DXVec3Minimize(&m_vMin, &m_vMin, &vTransMin);
		D3DXVec3TransformCoord(&vTransMax, &m_aVertex[i], m_pmatWorld);
		D3DXVec3Maximize(&m_vMax, &m_vMax, &vTransMax);
	}
}


void cCollider::Render()
{
}


bool cCollider::InterceptCube(cVec3* pvOut, cCollider* pCollider)
{
//	Update();
	pCollider->Update();
	cVec3 vMax = pCollider->m_vMax;
	cVec3 vMin = pCollider->m_vMin;

	if (m_vMin.x > vMax.x || vMin.x > m_vMax.x)
		return false;
	pvOut->x = (m_vMax.x - vMin.x > vMax.x - m_vMin.x) ?
		vMax.x - m_vMin.x : -(m_vMax.x - vMin.x);

	if (m_vMin.y > vMax.y || vMin.y > m_vMax.y)
		return false;
	pvOut->y = (m_vMax.y - vMin.y > vMax.y - m_vMin.y) ?
		vMax.y - m_vMin.y : -(m_vMax.y - vMin.y);

	if (m_vMin.z > vMax.z || vMin.z > m_vMax.z)
		return false;
	pvOut->z = (m_vMax.z - vMin.z > vMax.z - m_vMin.z) ?
		vMax.z - m_vMin.z : -(m_vMax.z - vMin.z);

	return true;
}


void cCollider::SetMinMax(cCollider* pCollider)
{
	//pCollider->Update();
	cVec3 vMax = pCollider->m_vMax;
	cVec3 vMin = pCollider->m_vMin;

	D3DXVec3Minimize(&m_vMin, &m_vMin, &vMin);
	D3DXVec3Maximize(&m_vMax, &m_vMax, &vMax);
}
