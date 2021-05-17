#include "stdafx.h"
#include "cTestPC.h"
#include "cWorld.h"


cTestPC::cTestPC()
	: m_fMoveRadius(3)
	, m_pMesh(NULL)
{
}


cTestPC::~cTestPC()
{
}

void cTestPC::Setup(cWorld* pWorld)
{
	D3DXCreateSphere(g_pD3DDevice, m_fMoveRadius, 2, 8, &m_pMesh, NULL);
	m_vRot.z = 90;

	m_pWorld = pWorld;
}

void cTestPC::Update()
{
	UpdateDirection();

	if (g_pKeyManager->IsStayKeyDown(VK_UP))
		m_vPos += m_vDir * 0.4f;

	if (g_pKeyManager->IsStayKeyDown(VK_RIGHT))
		m_vRot.x += 3;

	if (g_pKeyManager->IsStayKeyDown(VK_LEFT))
		m_vRot.x -= 1;

	//m_pWorld->ProcessMoveCollision(this);

	UpdateTransform();
}

void cTestPC::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD ,&m_matWorld);
	m_pMesh->DrawSubset(0);
}
