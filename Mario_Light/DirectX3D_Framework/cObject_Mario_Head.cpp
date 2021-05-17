#include "stdafx.h"
#include "cObject_Mario_Head.h"

#define mwh 1.f/8
cObject_Mario_Head::cObject_Mario_Head()
	: cObject_Limbs(false)
{
	m_pTexture = g_pGraphics->m_ptexMario;

	m_fAngleY = 180;

	m_aVertexPNT.push_back(Vertex_PNT({ cVec3(-1, -1, -1), -m_vLook, D3DXVECTOR2(0.125f, 0.5f) }));
	m_aVertexPNT.push_back(Vertex_PNT({ cVec3(-1, 1, -1), -m_vLook, D3DXVECTOR2(0.125f, 0.25f) }));
	m_aVertexPNT.push_back(Vertex_PNT({ cVec3(1, 1, -1), -m_vLook, D3DXVECTOR2(0.25f, 0.25f) }));
	m_aVertexPNT.push_back(Vertex_PNT({ cVec3(-1, -1, -1), -m_vLook, D3DXVECTOR2(0.125f, 0.5f) }));
	m_aVertexPNT.push_back(Vertex_PNT({ cVec3(1, 1, -1), -m_vLook, D3DXVECTOR2(0.25f, 0.25f) }));
	m_aVertexPNT.push_back(Vertex_PNT({ cVec3(1, -1, -1), -m_vLook, D3DXVECTOR2(0.25f, 0.5f) }));
								   									
	m_aVertexPNT.push_back(Vertex_PNT({ cVec3(-1, -1, 1), m_vLook, D3DXVECTOR2(0.5f, 0.5f) }));
	m_aVertexPNT.push_back(Vertex_PNT({ cVec3(1, 1, 1), m_vLook, D3DXVECTOR2(0.25f, 0.25f) }));
	m_aVertexPNT.push_back(Vertex_PNT({ cVec3(-1, 1, 1), m_vLook, D3DXVECTOR2(0.375f, 0.25f) }));
	m_aVertexPNT.push_back(Vertex_PNT({ cVec3(-1, -1, 1), m_vLook, D3DXVECTOR2(0.5f, 0.5f) }));
	m_aVertexPNT.push_back(Vertex_PNT({ cVec3(1, -1, 1), m_vLook, D3DXVECTOR2(0.375f, 0.5f) }));
	m_aVertexPNT.push_back(Vertex_PNT({ cVec3(1, 1, 1), m_vLook, D3DXVECTOR2(0.25f, 0.25f) }));
								   								
	m_aVertexPNT.push_back(Vertex_PNT({ cVec3(-1, -1, 1), -m_vRight, D3DXVECTOR2(0.f, 0.5f) }));
	m_aVertexPNT.push_back(Vertex_PNT({ cVec3(-1, 1, 1), -m_vRight, D3DXVECTOR2(0.f, 0.25f) }));
	m_aVertexPNT.push_back(Vertex_PNT({ cVec3(-1, 1, -1), -m_vRight, D3DXVECTOR2(0.125f, 0.25f) }));
	m_aVertexPNT.push_back(Vertex_PNT({ cVec3(-1, -1, 1), -m_vRight, D3DXVECTOR2(0.f, 0.5f) }));
	m_aVertexPNT.push_back(Vertex_PNT({ cVec3(-1, 1, -1), -m_vRight, D3DXVECTOR2(0.125, 0.25f) }));
	m_aVertexPNT.push_back(Vertex_PNT({ cVec3(-1, -1, -1), -m_vRight, D3DXVECTOR2(0.25, 0.5f) }));
								   									
	m_aVertexPNT.push_back(Vertex_PNT({ cVec3(1, -1, -1), m_vRight, D3DXVECTOR2(0.25f, 0.5f) }));
	m_aVertexPNT.push_back(Vertex_PNT({ cVec3(1, 1, -1), m_vRight, D3DXVECTOR2(0.25f, 0.25f) }));
	m_aVertexPNT.push_back(Vertex_PNT({ cVec3(1, 1, 1), m_vRight, D3DXVECTOR2(0.375f, 0.25f) }));
	m_aVertexPNT.push_back(Vertex_PNT({ cVec3(1, -1, -1), m_vRight, D3DXVECTOR2(0.25f, 0.5f) }));
	m_aVertexPNT.push_back(Vertex_PNT({ cVec3(1, 1, 1), m_vRight, D3DXVECTOR2(0.375, 0.25f) }));
	m_aVertexPNT.push_back(Vertex_PNT({ cVec3(1, -1, 1), m_vRight, D3DXVECTOR2(0.375, 0.5f) }));
								   									
	m_aVertexPNT.push_back(Vertex_PNT({ cVec3(-1, 1, -1), m_vUp, D3DXVECTOR2(0.125f, 0.25f) }));
	m_aVertexPNT.push_back(Vertex_PNT({ cVec3(-1, 1, 1), m_vUp, D3DXVECTOR2(0.125f, 0.f) }));
	m_aVertexPNT.push_back(Vertex_PNT({ cVec3(1, 1, 1), m_vUp, D3DXVECTOR2(0.25f, 0.f) }));
	m_aVertexPNT.push_back(Vertex_PNT({ cVec3(-1, 1, -1), m_vUp, D3DXVECTOR2(0.125f, 0.25f) }));
	m_aVertexPNT.push_back(Vertex_PNT({ cVec3(1, 1, 1), m_vUp, D3DXVECTOR2(0.25, 0.f) }));
	m_aVertexPNT.push_back(Vertex_PNT({ cVec3(1, 1, -1), m_vUp, D3DXVECTOR2(0.25, 0.25f) }));
}



cObject_Mario_Head::~cObject_Mario_Head()
{
}


void cObject_Mario_Head::Render()
{
	if (m_pTexture)
		g_pDevice->SetTexture(0, m_pTexture);

	cObject_Cube::Render();
}
