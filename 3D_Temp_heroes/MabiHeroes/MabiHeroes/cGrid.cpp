#include "StdAfx.h"
#include "cGrid.h"
#include "cPyramid.h"
cGrid::cGrid(void)
	: m_pVB(NULL)
	, m_nNumLine(0)
{
}


cGrid::~cGrid(void)
{

}

void cGrid::Setup(int nLine, float nInterval)
{
	std::vector<ST_PC_VERTEX>	vecLine;
	D3DCOLOR c;
	float fMax = nLine * nInterval;
	for (int i = 1; i <= nLine; ++i)
	{
		if (i % 5 == 0) c = D3DCOLOR_XRGB(255, 255, 255);
		else c = D3DCOLOR_XRGB(128, 128, 128);

		vecLine.push_back(ST_PC_VERTEX(D3DXVECTOR3(-fMax, 0, -i * nInterval), c));
		vecLine.push_back(ST_PC_VERTEX(D3DXVECTOR3( fMax, 0, -i * nInterval), c));
		
		vecLine.push_back(ST_PC_VERTEX(D3DXVECTOR3(-fMax, 0,  i * nInterval), c));
		vecLine.push_back(ST_PC_VERTEX(D3DXVECTOR3( fMax, 0,  i * nInterval), c));
		
		vecLine.push_back(ST_PC_VERTEX(D3DXVECTOR3(-i * nInterval, 0,-fMax ), c));
		vecLine.push_back(ST_PC_VERTEX(D3DXVECTOR3(-i * nInterval, 0, fMax ), c));
		
		vecLine.push_back(ST_PC_VERTEX(D3DXVECTOR3( i * nInterval, 0,-fMax ), c));
		vecLine.push_back(ST_PC_VERTEX(D3DXVECTOR3( i * nInterval, 0, fMax ), c));
	}

	c = D3DCOLOR_XRGB(255, 0, 0);
	vecLine.push_back(ST_PC_VERTEX(D3DXVECTOR3(-fMax, 0, 0), c));
	vecLine.push_back(ST_PC_VERTEX(D3DXVECTOR3( fMax, 0, 0), c));

	c = D3DCOLOR_XRGB(0, 255, 0);
	vecLine.push_back(ST_PC_VERTEX(D3DXVECTOR3( 0,-fMax, 0), c));
	vecLine.push_back(ST_PC_VERTEX(D3DXVECTOR3( 0, fMax, 0), c));

	c = D3DCOLOR_XRGB(0, 0, 255);
	vecLine.push_back(ST_PC_VERTEX(D3DXVECTOR3( 0, 0,-fMax), c));
	vecLine.push_back(ST_PC_VERTEX(D3DXVECTOR3( 0, 0, fMax), c));

	// 버텍스 버퍼 생성
	g_pD3DDevice->CreateVertexBuffer(
		vecLine.size() * sizeof(ST_PC_VERTEX),
		0,
		ST_PC_VERTEX::FVF,
		D3DPOOL_MANAGED,
		&m_pVB,
		NULL);

	ST_PC_VERTEX* pV;
	m_pVB->Lock(0, 0, (LPVOID*)&pV, 0);
	memcpy(pV, &vecLine[0], vecLine.size() * sizeof(ST_PC_VERTEX));
	m_pVB->Unlock();

	m_nNumLine = vecLine.size() / 2;

	cPyramid* pPyramid = NULL;
	D3DXMATRIXA16 matWorld, matR, matS;
	D3DXMatrixScaling(&matS, 0.1f, 2.f, 0.1f);
	
	// X
	pPyramid = new cPyramid;
	D3DXMatrixRotationZ(&matR, D3DX_PI / 2.0f);
	matWorld = matS * matR;
	pPyramid->Setup(D3DXCOLOR(1, 0, 0, 1), &matWorld);
	m_vecPyramid.push_back(pPyramid);

	// Y
	pPyramid = new cPyramid;
	D3DXMatrixRotationZ(&matR, D3DX_PI);
	matWorld = matS * matR;
	pPyramid->Setup(D3DXCOLOR(0, 1, 0, 1), &matWorld);
	m_vecPyramid.push_back(pPyramid);

	// Z
	pPyramid = new cPyramid;
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);
	matWorld = matS * matR;
	pPyramid->Setup(D3DXCOLOR(0, 0, 1, 1), &matWorld);
	m_vecPyramid.push_back(pPyramid);
}

void cGrid::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	D3DXMATRIXA16 matI;
	D3DXMatrixIdentity(&matI);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matI);
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->SetStreamSource(0, m_pVB, 0, sizeof(ST_PC_VERTEX));
	g_pD3DDevice->DrawPrimitive(D3DPT_LINELIST, 0, m_nNumLine);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	for each(auto p in m_vecPyramid)
	{
		p->Render();
	}
}
