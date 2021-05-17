#include "stdafx.h"
#include "cObject_Plane.h"


cObject_Plane::cObject_Plane()
	: m_fInterval(0), m_fVelocity(0), m_fMaxInterval(0)
{
	m_pTexture = g_pGraphics->m_ptexGround;

	m_aVertexPNT.push_back(Vertex_PNT(cVec3(-1, -1, -1), cVec3(-1, -1, -1), cVec2(0, 1)));
	m_aVertexPNT.push_back(Vertex_PNT(cVec3(-1, 1, -1), cVec3(-1, 1, -1), cVec2(0, 0)));
	m_aVertexPNT.push_back(Vertex_PNT(cVec3(1, 1, -1), cVec3(1, 1, -1), cVec2(0, 1)));
	m_aVertexPNT.push_back(Vertex_PNT(cVec3(-1, -1, -1), cVec3(-1, -1, -1), cVec2(0, 1)));
	m_aVertexPNT.push_back(Vertex_PNT(cVec3(1, 1, -1), cVec3(1, 1, -1), cVec2(1, 0)));
	m_aVertexPNT.push_back(Vertex_PNT(cVec3(1, -1, -1), cVec3(1, -1, -1), cVec2(1, 1)));
			   						
	m_aVertexPNT.push_back(Vertex_PNT(cVec3(-1, -1, 1),cVec3(-1, -1, 1), cVec2(0, 1)));
	m_aVertexPNT.push_back(Vertex_PNT(cVec3(1, 1, 1), cVec3(1, 1, 1), cVec2(1, 0)));
	m_aVertexPNT.push_back(Vertex_PNT(cVec3(-1, 1, 1), cVec3(-1, 1, 1), cVec2(0, 0)));
	m_aVertexPNT.push_back(Vertex_PNT(cVec3(-1, -1, 1),cVec3(-1, -1, 1), cVec2(0, 1)));
	m_aVertexPNT.push_back(Vertex_PNT(cVec3(1, -1, 1), cVec3(1, -1, 1), cVec2(1, 1)));
	m_aVertexPNT.push_back(Vertex_PNT(cVec3(1, 1, 1), cVec3(1, 1, 1), cVec2(1, 0)));
			   						
	m_aVertexPNT.push_back(Vertex_PNT(cVec3(-1, -1, 1), cVec3(-1, -1, 1), cVec2(1, 1)));
	m_aVertexPNT.push_back(Vertex_PNT(cVec3(-1, 1, 1), cVec3(-1, 1, 1), cVec2(1, 0)));
	m_aVertexPNT.push_back(Vertex_PNT(cVec3(-1, 1, -1), cVec3(-1, 1, -1), cVec2(0, 0)));
	m_aVertexPNT.push_back(Vertex_PNT(cVec3(-1, -1, 1), cVec3(-1, -1, 1), cVec2(1, 1)));
	m_aVertexPNT.push_back(Vertex_PNT(cVec3(-1, 1, -1), cVec3(-1, 1, -1), cVec2(0, 0)));
	m_aVertexPNT.push_back(Vertex_PNT(cVec3(-1, -1, -1),cVec3(-1, -1, -1), cVec2(0, 1)));
			   						
	m_aVertexPNT.push_back(Vertex_PNT(cVec3(1, -1, -1),cVec3(1, -1, -1), cVec2(0, 1)));
	m_aVertexPNT.push_back(Vertex_PNT(cVec3(1, 1, -1), cVec3(1, 1, -1), cVec2(0, 0)));
	m_aVertexPNT.push_back(Vertex_PNT(cVec3(1, 1, 1), cVec3(1, 1, 1), cVec2(1, 0)));
	m_aVertexPNT.push_back(Vertex_PNT(cVec3(1, -1, -1),cVec3(1, -1, -1), cVec2(0, 1)));
	m_aVertexPNT.push_back(Vertex_PNT(cVec3(1, 1, 1), cVec3(1, 1, 1), cVec2(1, 0)));
	m_aVertexPNT.push_back(Vertex_PNT(cVec3(1, -1, 1), cVec3(1, -1, 1), cVec2(1, 1)));
			   						
	m_aVertexPNT.push_back(Vertex_PNT(cVec3(-1, 1, -1),cVec3(-1, 1, -1), cVec2(0, 1)));
	m_aVertexPNT.push_back(Vertex_PNT(cVec3(-1, 1, 1), cVec3(-1, 1, 1), cVec2(0, 0)));
	m_aVertexPNT.push_back(Vertex_PNT(cVec3(1, 1, 1), cVec3(1, 1, 1), cVec2(1, 0)));
	m_aVertexPNT.push_back(Vertex_PNT(cVec3(-1, 1, -1),cVec3(-1, 1, -1), cVec2(0, 1)));
	m_aVertexPNT.push_back(Vertex_PNT(cVec3(1, 1, 1), cVec3(1, 1, 1), cVec2(1, 0)));
	m_aVertexPNT.push_back(Vertex_PNT(cVec3(1, 1, -1), cVec3(1, 1, -1), cVec2(1, 1)));
			   						
	m_aVertexPNT.push_back(Vertex_PNT(cVec3(-1, -1, 1), cVec3(-1, -1, 1), cVec2(0, 0)));
	m_aVertexPNT.push_back(Vertex_PNT(cVec3(-1, -1, -1), cVec3(-1, -1, -1), cVec2(0, 1)));
	m_aVertexPNT.push_back(Vertex_PNT(cVec3(1, -1, -1), cVec3(1, -1, -1), cVec2(1, 1)));
	m_aVertexPNT.push_back(Vertex_PNT(cVec3(-1, -1, 1), cVec3(-1, -1, 1), cVec2(0, 0)));
	m_aVertexPNT.push_back(Vertex_PNT(cVec3(1, -1, -1), cVec3(1, -1, -1), cVec2(1, 1)));
	m_aVertexPNT.push_back(Vertex_PNT(cVec3(1, -1, 1), cVec3(1, -1, 1), cVec2(1, 0)));
}


cObject_Plane::~cObject_Plane()
{
}


void cObject_Plane::Setup(float sx, float sy, float sz, D3DCOLOR color)
{
	m_pTexture = g_pGraphics->m_ptexGround;
	SetScale(sx, sy, sz);
	UpdateWorld();
	SetColor(color);

	m_pCollider = new cCollider(&m_matWolrd);
	m_pCollider->Setup(&m_aLocalPos);
}


void cObject_Plane::Update()
{
	if (m_bMove)
	{
		if (fabs(m_fInterval) > m_fMaxInterval)
			m_fVelocity *= -1;

		m_fInterval += m_fVelocity;
	}

	D3DXMatrixTranslation(&m_matTrl, m_vPos.x,
		m_vPos.y + m_fInterval, m_vPos.z);
	m_matWolrd = m_matScale * m_matTrl;
}


void cObject_Plane::Render()
{
	if (m_pTexture)
		g_pDevice->SetTexture(0, m_pTexture);
	cObject_Cube::Render();
}


// 기본 50~210사이로 사용중. 합쳐서 RGB를 초과하지않도록
void cObject_Plane::SetColor(D3DCOLOR color)
{
	int size = m_aVertexPC.size();

	for (int i = 0; i < size; ++i)
		m_aVertexPC[i].color += color;
}


void cObject_Plane::SetMovePlane(float fMaxInterval, float fSpeed)
{
	m_fMaxInterval = fMaxInterval;
	m_fVelocity = fSpeed;
	m_bMove = true;
}
