#include "stdafx.h"
#include "cObject_Grid.h"


cObject_Grid::cObject_Grid()
	: m_nLine(10)
{
}


cObject_Grid::~cObject_Grid()
{
}


void cObject_Grid::Setup()
{
	if (!m_aVertex.empty())
		m_aVertex.clear();

	for (int i = -m_nLine; i <= m_nLine; ++i)
	{
		xColor color = (i % 5) ? D3DCOLOR_XRGB(128, 128, 128)
			: D3DCOLOR_XRGB(255, 255, 255);

		m_aVertex.push_back(stVertex_PC(cVec3(i, 0, m_nLine), color));
		m_aVertex.push_back(stVertex_PC(cVec3(i, 0, -m_nLine), color));
		m_aVertex.push_back(stVertex_PC(cVec3(m_nLine, 0, i), color));
		m_aVertex.push_back(stVertex_PC(cVec3(-m_nLine, 0, i), color));
	}
}


void cObject_Grid::Update()
{
}


void cObject_Grid::Render()
{
	m_matWorld = m_matScale;
	g_pDDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pDDevice->DrawPrimitiveUP(D3DPT_LINELIST
		, m_aVertex.size()/2, &m_aVertex[0], sizeof(stVertex_PC));
}


void cObject_Grid::SetLine(int nLine)
{
	m_nLine = nLine;
}
