#include "StdAfx.h"
#include "cPyramid.h"

cPyramid::cPyramid(void)
	: m_pVB(NULL)
	, m_nNumTri(0)
	, m_isPicked(false)
{
	D3DXMatrixIdentity(&m_matWorld);
}

cPyramid::~cPyramid(void)
{
}

void cPyramid::Setup(D3DXCOLOR c, D3DXMATRIXA16* pmat)
{
	std::vector<ST_PN_VERTEX>	vecVertex;

	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
	m_stMtl.Ambient = m_stMtl.Diffuse = m_stMtl.Specular = c;
	m_stMtl2.Ambient = m_stMtl2.Diffuse = m_stMtl2.Specular = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1);

	D3DXMatrixIdentity(&m_matWorld);

	D3DXVECTOR3 n(0, 0 ,0);
	D3DXVECTOR3 p;
	p = D3DXVECTOR3( 0, 0, 0); vecVertex.push_back(ST_PN_VERTEX(p, n));
	p = D3DXVECTOR3( 1,-1,-1); vecVertex.push_back(ST_PN_VERTEX(p, n));
	p = D3DXVECTOR3(-1,-1,-1); vecVertex.push_back(ST_PN_VERTEX(p, n));

	p = D3DXVECTOR3( 0, 0, 0); vecVertex.push_back(ST_PN_VERTEX(p, n));
	p = D3DXVECTOR3( 1,-1, 1); vecVertex.push_back(ST_PN_VERTEX(p, n));
	p = D3DXVECTOR3( 1,-1,-1); vecVertex.push_back(ST_PN_VERTEX(p, n));

	p = D3DXVECTOR3( 0, 0, 0); vecVertex.push_back(ST_PN_VERTEX(p, n));
	p = D3DXVECTOR3(-1,-1, 1); vecVertex.push_back(ST_PN_VERTEX(p, n));
	p = D3DXVECTOR3( 1,-1, 1); vecVertex.push_back(ST_PN_VERTEX(p, n));

	p = D3DXVECTOR3( 0, 0, 0); vecVertex.push_back(ST_PN_VERTEX(p, n));
	p = D3DXVECTOR3(-1,-1,-1); vecVertex.push_back(ST_PN_VERTEX(p, n));
	p = D3DXVECTOR3(-1,-1, 1); vecVertex.push_back(ST_PN_VERTEX(p, n));

	p = D3DXVECTOR3(-1,-1, 1); vecVertex.push_back(ST_PN_VERTEX(p, n));
	p = D3DXVECTOR3(-1,-1,-1); vecVertex.push_back(ST_PN_VERTEX(p, n));
	p = D3DXVECTOR3( 1,-1,-1); vecVertex.push_back(ST_PN_VERTEX(p, n));

	p = D3DXVECTOR3(-1,-1, 1); vecVertex.push_back(ST_PN_VERTEX(p, n));
	p = D3DXVECTOR3( 1,-1,-1); vecVertex.push_back(ST_PN_VERTEX(p, n));
	p = D3DXVECTOR3( 1,-1, 1); vecVertex.push_back(ST_PN_VERTEX(p, n));

	for (size_t i = 0; i < vecVertex.size(); i += 3)
	{
		D3DXVECTOR3 v01 = vecVertex[i + 1].p - vecVertex[i].p;
		D3DXVECTOR3 v02 = vecVertex[i + 2].p - vecVertex[i].p;
		D3DXVec3Cross(&n, &v01, &v02);
		D3DXVec3Normalize(&n, &n);
		vecVertex[i].n = vecVertex[i + 1].n = vecVertex[i + 2].n = n;
	}

	for (size_t i = 0; i < vecVertex.size(); ++i)
	{
		D3DXVec3TransformCoord(&vecVertex[i].p, &vecVertex[i].p, pmat);
		D3DXVec3TransformNormal(&vecVertex[i].n, &vecVertex[i].n, pmat);
	}


	g_pD3DDevice->CreateVertexBuffer(
		vecVertex.size() * sizeof(ST_PN_VERTEX),
		0,
		ST_PN_VERTEX::FVF,
		D3DPOOL_MANAGED,
		&m_pVB,
		NULL);

	ST_PN_VERTEX* pV;
	m_pVB->Lock(0, 0, (LPVOID*)&pV, 0);
	memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(ST_PN_VERTEX));
	m_pVB->Unlock();

	m_nNumTri = vecVertex.size() / 3;
}

void cPyramid::Update()
{

	D3DXMATRIXA16 matR, matT;
	D3DXMatrixLookAtLH(&matR,
		&D3DXVECTOR3(0, 0, 0),
		&m_vDirection,
		&D3DXVECTOR3(0, 1, 0));
	D3DXMatrixTranspose(&matR, &matR);

	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matR * matT;
}

void cPyramid::Render()
{
	g_pD3DDevice->SetMaterial(&m_stMtl);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetFVF(ST_PN_VERTEX::FVF);
	g_pD3DDevice->SetStreamSource(0, m_pVB, 0, sizeof(ST_PN_VERTEX));
	g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_nNumTri);
}

void cPyramid::Render(const D3DXMATRIXA16 * pmatWorld)
{
	if(m_isPicked)
		g_pD3DDevice->SetMaterial(&m_stMtl2);
	else
		g_pD3DDevice->SetMaterial(&m_stMtl);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, pmatWorld);
	g_pD3DDevice->SetFVF(ST_PN_VERTEX::FVF);
	g_pD3DDevice->SetStreamSource(0, m_pVB, 0, sizeof(ST_PN_VERTEX));
	g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_nNumTri);
}

bool cPyramid::IsPick(const ST_RAY & rayMouse)
{
	ST_PN_VERTEX* pV;
	m_pVB->Lock(0, 0, (LPVOID*)&pV, 0);
	
	for (int i = 0; i < 18; i += 3)
	{
		if (D3DXIntersectTri(&pV[i].p, &pV[i + 1].p, &pV[i + 2].p, &rayMouse.vOri, &rayMouse.vDir, NULL, NULL, NULL))
		{
			m_pVB->Unlock();
			m_isPicked = true;
			return true;
		}
	}

	m_pVB->Unlock();
	m_isPicked = false;

	return false;
}
