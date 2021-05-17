#include "stdafx.h"
#include "cTransform.h"


cTransform::cTransform()
	: m_vPos(0, 0, 0)
	, m_vDir(0, 0, 1)
	, m_vRot(0, 0, 0)
	, m_vScale(1, 1, 1)
	, m_vRight(1, 0, 0)
{
	D3DXMatrixIdentity(&m_matWorld);
	m_matR = m_matT = m_matS = m_matWorld;
}


cTransform::~cTransform()
{
}

void cTransform::SetPosition(const D3DXVECTOR3 * pvPos)
{
	m_vPos = *pvPos;
}

void cTransform::SetDirection(const D3DXVECTOR3 * pvDir)
{
	m_vDir = *pvDir;
}

void cTransform::SetPosition(float px, float py, float pz)
{
	m_vPos = D3DXVECTOR3(px, py, pz);
}

void cTransform::SetRotation(float rx, float ry, float rz)
{
	m_vRot.x = rx; m_vRot.y = ry; m_vRot.z = rz;
}

void cTransform::SetScale(float ratio)
{
	m_vScale.x = ratio;
	m_vScale.y = ratio;
	m_vScale.z = ratio;
}

void cTransform::SetScale(float sx, float sy, float sz)
{
	m_vScale.x = sx;
	m_vScale.y = sy;
	m_vScale.z = sz;
}

void cTransform::SetWorldMatirx(const D3DXMATRIXA16 * pmatWorld)
{
	m_matWorld = *pmatWorld;
}

void cTransform::SetWorldMatirxFromParent(const D3DXMATRIXA16 * pmatWorld)
{
	m_matWorld *= *pmatWorld;
}

void cTransform::UpdateTranslation()
{
	m_matT._41 = m_vPos.x;
	m_matT._42 = m_vPos.y;
	m_matT._43 = m_vPos.z;
}

void cTransform::UpdateRotation()
{
	D3DXMATRIXA16 matY, matZ;
	D3DXMatrixRotationX(&m_matR, D3DXToRadian(m_vRot.x));
	D3DXMatrixRotationY(&matY, D3DXToRadian(m_vRot.y));
	D3DXMatrixRotationZ(&matZ, D3DXToRadian(m_vRot.z));

	m_matR *= matY * matZ;
}

void cTransform::UpdateScaling()
{
	D3DXMatrixScaling(&m_matS, m_vScale.x, m_vScale.y, m_vScale.z);
}

void cTransform::UpdateDirection()
{
	D3DXVec3TransformNormal(&m_vDir, &D3DXVECTOR3(0, 0, 1), &m_matR);
	D3DXVec3TransformNormal(&m_vRight, &D3DXVECTOR3(1, 0, 0), &m_matR);
}

void cTransform::UpdateWorld()
{
	m_matWorld = m_matS * m_matR * m_matT;
}

void cTransform::UpdateTransform()
{
	UpdateTranslation();
	UpdateRotation();
	UpdateScaling();
	UpdateWorld();
}

void cTransform::TransformPosition(OUT D3DXVECTOR3 * pvOut)
{
	D3DXVec3TransformCoord(pvOut, pvOut, &m_matWorld);
}

void cTransform::TransformVector(OUT D3DXVECTOR3 * pvOut)
{
	D3DXVec3TransformNormal(pvOut, pvOut, &m_matWorld);
}

D3DXVECTOR3& cTransform::GetPosition()
{
	return m_vPos;
}
