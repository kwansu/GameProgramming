#include "stdafx.h"
#include "cCollisionRender.h"


cCollisionRender* g_pCollisionRender = cCollisionRender::GetInstance();

cCollisionRender::cCollisionRender()
	: m_pMeshBox(NULL)
	, m_pMeshSphere(NULL)
{
}


cCollisionRender::~cCollisionRender()
{
}

void cCollisionRender::Setup()
{
	D3DXCreateBox(g_pD3DDevice, 2, 2, 2, &m_pMeshBox, NULL);
	D3DXCreateSphere(g_pD3DDevice, 1, 20, 20, &m_pMeshSphere, NULL);

	ZeroMemory(&m_mtl, sizeof(D3DMATERIAL9));
	m_mtl.Diffuse = D3DXCOLOR(0, 1, 0, 1);
	m_mtl.Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1);
}

void cCollisionRender::Destroy()
{
	SafeRelease(m_pMeshBox);
	SafeRelease(m_pMeshSphere);
}

void cCollisionRender::RenderSphere(const D3DXVECTOR3 & vOri, float fRadius)
{
	D3DXMatrixTranslation(&m_matWorld, vOri.x, vOri.y, vOri.z);
	m_matWorld._11 = m_matWorld._22 = m_matWorld._33 = fRadius;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetMaterial(&m_mtl);
	g_pD3DDevice->SetFVF(m_pMeshSphere->GetFVF());
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	
	m_pMeshSphere->DrawSubset(0);
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

void cCollisionRender::RenderBox(const D3DXVECTOR3 & vCenter, const D3DXVECTOR3 & vHalfSize)
{
	D3DXMatrixTranslation(&m_matWorld, vCenter.x, vCenter.y, vCenter.z);
	m_matWorld._11 = vHalfSize.x;
	m_matWorld._22 = vHalfSize.y;
	m_matWorld._33 = vHalfSize.z;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetMaterial(&m_mtl);
	g_pD3DDevice->SetFVF(m_pMeshBox->GetFVF());
	//g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	m_pMeshBox->DrawSubset(0);
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

void cCollisionRender::RenderBox(const ST_COLLISION_BOX_STICK & box, const D3DXCOLOR * pColor)
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	D3DXMatrixScaling(&m_matWorld, box.vHalfSize.x, box.vHalfSize.y, box.vHalfSize.z);
	m_matWorld *= box.matOffset * *box.pmatSticking;

	m_mtl.Diffuse = D3DXCOLOR(0, 1, 0, 1);

	if (pColor)
		m_mtl.Diffuse = *pColor;
	else
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	g_pD3DDevice->SetMaterial(&m_mtl);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetFVF(m_pMeshBox->GetFVF());

	m_pMeshBox->DrawSubset(0);
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

void cCollisionRender::RenderBoxAlpha(const ST_COLLISION_BOX_STICK & box, const D3DXCOLOR color)
{
	D3DXMatrixScaling(&m_matWorld, box.vHalfSize.x, box.vHalfSize.y, box.vHalfSize.z);
	m_matWorld *= box.matOffset * *box.pmatSticking;

	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	m_mtl.Diffuse = color;

	////////////// draw
	g_pD3DDevice->SetMaterial(&m_mtl);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetFVF(m_pMeshBox->GetFVF());

	m_pMeshBox->DrawSubset(0);
	//////////////////

	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

