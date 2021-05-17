#include "stdafx.h"
#include "cPlane.h"


cPlane::cPlane()
{
}


cPlane::~cPlane()
{
}

void cPlane::Setup(float hx, float hz)
{
	m_collPlane.vHalfSize = D3DXVECTOR3(hx, 0, hz);
	SetScale(hx, 0, hz);
}

void cPlane::UpdateCollision()
{
	UpdateTransform();
	
	D3DXVec3TransformNormal(&m_collPlane.vFront, &D3DXVECTOR3(0, 1, 0), &m_matWorld);
	D3DXVec3TransformNormal(&m_collPlane.vRight, &D3DXVECTOR3(1, 0, 0), &m_matWorld);
	D3DXVec3TransformNormal(&m_collPlane.vUp, &D3DXVECTOR3(0, 0, 1), &m_matWorld);

	m_collPlane.vCenter = m_vPos;
}

void cPlane::Render()
{
	g_pCollisionRender->RenderBox(m_matWorld, m_collPlane.vHalfSize);
}
