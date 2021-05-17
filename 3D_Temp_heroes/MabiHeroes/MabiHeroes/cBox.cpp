#include "stdafx.h"
#include "cBox.h"


cBox::cBox()
	: m_pMesh(NULL)
	, m_pTexture(NULL)
{
		
	m_ID = "BOX";
	// make collision box
	ST_COLLISION_BOX_STICK coll;
	coll.pmatSticking = &m_matWorld;

	m_vecCollisionBox.push_back(coll);

	ZeroMemory(&m_mtl, sizeof(m_mtl));
	m_mtl.Diffuse = D3DXCOLOR(1, 1, 1, 1);
}


cBox::~cBox()
{
	SafeDelete(m_pMesh);
}

void cBox::Setup()
{
	D3DXCreateBox(g_pD3DDevice, 4, 4, 4, &m_pMesh, NULL);
}

void cBox::Update()
{
	UpdateTransform();
}

void cBox::Render()
{
	if (m_pMesh)
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
		g_pD3DDevice->SetFVF(m_pMesh->GetFVF());
		g_pD3DDevice->SetTexture(0, m_pTexture);
		g_pD3DDevice->SetMaterial(&m_mtl);
		m_pMesh->DrawSubset(0);
	}
}

void cBox::SaveData(OUT ofstream & outFile)
{
	//matrix + collision box
	outFile << m_matWorld._11 << endl;
	outFile << m_matWorld._12 << endl;
	outFile << m_matWorld._13 << endl;
	outFile << m_matWorld._14 << endl;


	outFile << m_matWorld._21 << endl;
	outFile << m_matWorld._22 << endl;
	outFile << m_matWorld._23 << endl;
	outFile << m_matWorld._24 << endl;


	outFile << m_matWorld._31 << endl;
	outFile << m_matWorld._32 << endl;
	outFile << m_matWorld._33 << endl;
	outFile << m_matWorld._34 << endl;


	outFile << m_matWorld._41 << endl;
	outFile << m_matWorld._42 << endl;
	outFile << m_matWorld._43 << endl;
	outFile << m_matWorld._44 << endl;
}
