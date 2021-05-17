#include "stdafx.h"
#include "cLocalEditor.h"


cLocalEditor::cLocalEditor()
	: m_pmatTargetT(NULL)
	, m_pmatTargetR(NULL)
	, m_pMesh(NULL)
{
}


cLocalEditor::~cLocalEditor()
{
	SafeRelease(m_pMesh);
}

void cLocalEditor::Setup()
{
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

	ST_COLLISION_BOX_STICK stColl;

	stColl.vHalfSize = D3DXVECTOR3(0.8f, 0, 0.8f);
	D3DXMatrixTranslation(&stColl.matOffset, 0.8f, 0, 0.8f);
	stColl.pmatSticking = &m_matWorld;
	m_vecBox.push_back(stColl);

	stColl.vHalfSize = D3DXVECTOR3(0.8f, 0.8f, 0);
	D3DXMatrixTranslation(&stColl.matOffset, 0.8f, 0.8f, 0);
	m_vecBox.push_back(stColl);

	stColl.vHalfSize = D3DXVECTOR3(0, 0.8f, 0.8f);
	D3DXMatrixTranslation(&stColl.matOffset, 0, 0.8f, 0.8f);
	m_vecBox.push_back(stColl);

	ZeroMemory(&m_mtl, sizeof(D3DMATERIAL9));
	D3DXCreateSphere(g_pD3DDevice, 2, 2, 30, &m_pMesh, NULL);
}

void cLocalEditor::Update(const D3DXVECTOR3 & cameraPos)
{
	if (!m_pmatTargetT)
		return;

	D3DXVECTOR3 vPos;
	vPos.x = m_pmatTargetT->_41;
	vPos.y = m_pmatTargetT->_42;
	vPos.z = m_pmatTargetT->_43;

	D3DXMATRIXA16 matT;
	D3DXMatrixIdentity(&matT);
	matT._41 = m_pmatTargetT->_41;
	matT._42 = m_pmatTargetT->_42;
	matT._43 = m_pmatTargetT->_43;

	vPos -= cameraPos;
	D3DXVec3Normalize(&vPos, &vPos);
	vPos = cameraPos + 10 * vPos;

	m_matWorld = *m_pmatTargetR * matT;
	m_matWorld._41 = vPos.x;
	m_matWorld._42 = vPos.y;
	m_matWorld._43 = vPos.z;

	m_matWorld = m_matOffset * m_matWorld;
}

void cLocalEditor::Render()
{
	if (!m_pmatTargetT)
		return;

	for each(const auto& p in m_vecPyramid)
	{
		p->Render(&m_matWorld);
	}

	g_pCollisionRender->RenderBoxAlpha(m_vecBox[0], D3DXCOLOR(1, 0, 0, 0.5f));
	g_pCollisionRender->RenderBoxAlpha(m_vecBox[1], D3DXCOLOR(0, 1, 0, 0.5f));
	g_pCollisionRender->RenderBoxAlpha(m_vecBox[2], D3DXCOLOR(0, 0, 1, 0.5f));
}

void cLocalEditor::RenderRotate()
{
	if (!m_pmatTargetT)
		return;

	for each(const auto& p in m_vecPyramid)
	{
		p->Render(&m_matWorld);
	}

	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	D3DXMATRIXA16 mat, matT;

	D3DXMatrixIdentity(&matT);
	matT._41 = m_matWorld._41;
	matT._42 = m_matWorld._42;
	matT._43 = m_matWorld._43;

	D3DXMatrixRotationY(&mat, D3DXToRadian(90));

	m_mtl.Ambient = D3DXCOLOR(1, 0, 0, 1);

	g_pD3DDevice->SetMaterial(&m_mtl);
	g_pD3DDevice->SetFVF(m_pMesh->GetFVF());
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matT);
	m_pMesh->DrawSubset(0);

	m_mtl.Ambient = D3DXCOLOR(0, 1, 0, 1);
	g_pD3DDevice->SetMaterial(&m_mtl);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &(mat * matT));
	m_pMesh->DrawSubset(0);

	m_mtl.Ambient = D3DXCOLOR(0, 0, 1, 1);
	g_pD3DDevice->SetMaterial(&m_mtl);
	D3DXMatrixRotationZ(&mat, D3DXToRadian(90));
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &(mat * matT));
	m_pMesh->DrawSubset(0);

	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

void cLocalEditor::SetTarget(D3DXMATRIXA16* pmatTargetT, D3DXMATRIXA16* pmatTargetR, const D3DXMATRIXA16 * pmatOffset)
{
	m_pmatTargetT = pmatTargetT;
	m_pmatTargetR = pmatTargetR;

	if (pmatOffset)
		m_matOffset = *pmatOffset;
	else
		D3DXMatrixIdentity(&m_matOffset);
}

DWORD cLocalEditor::IsPickPyramid(const ST_RAY& rayMouse)
{
	DWORD result = 0;

	D3DXMATRIXA16 matInverse;

	D3DXMatrixInverse(&matInverse, NULL, &m_matWorld);
	ST_RAY ray;

	D3DXVec3TransformCoord(&ray.vOri, &rayMouse.vOri, &matInverse);
	D3DXVec3TransformNormal(&ray.vDir, &rayMouse.vDir, &matInverse);

	if (m_vecPyramid[0]->IsPick(ray))
		result += eTRANSLATE_STATE::RIGHT;

	if (m_vecPyramid[1]->IsPick(ray))
		result += eTRANSLATE_STATE::UP;

	if (m_vecPyramid[2]->IsPick(ray))
		result += eTRANSLATE_STATE::FRONT;

	return result;
}

bool cLocalEditor::IsPickPlane(OUT ST_PLANE & stPlane, const ST_RAY& rayMouse)
{
	D3DXMATRIXA16 mat;

	D3DXMatrixTranslation(&mat, 0.8f, 0, 0.8f);
	mat *= m_matWorld;
	if (IsCollisionBox(mat, rayMouse, D3DXVECTOR3(1, 0, 1)))
	{
		D3DXVec3TransformNormal(&stPlane.vNormal, &D3DXVECTOR3(0, 1, 0), m_pmatTargetR);
		D3DXVec3Normalize(&stPlane.vNormal, &stPlane.vNormal);
		stPlane.vOther.x = m_pmatTargetT->_41;
		stPlane.vOther.y = m_pmatTargetT->_42;
		stPlane.vOther.z = m_pmatTargetT->_43;
		return true;
	}

	D3DXMatrixTranslation(&mat, 0, 0.8f, 0.8f);
	mat *= m_matWorld;
	if (IsCollisionBox(mat, rayMouse, D3DXVECTOR3(0, 1, 1)))
	{
		D3DXVec3TransformNormal(&stPlane.vNormal, &D3DXVECTOR3(1, 0, 0), m_pmatTargetR);
		D3DXVec3Normalize(&stPlane.vNormal, &stPlane.vNormal);
		stPlane.vOther.x = m_pmatTargetT->_41;
		stPlane.vOther.y = m_pmatTargetT->_42;
		stPlane.vOther.z = m_pmatTargetT->_43;
		return true;
	}

	D3DXMatrixTranslation(&mat, 0.8f, 0.8f, 0);
	mat *= m_matWorld;
	if (IsCollisionBox(mat, rayMouse, D3DXVECTOR3(1, 1, 0)))
	{
		D3DXVec3TransformNormal(&stPlane.vNormal, &D3DXVECTOR3(0, 0, 1), m_pmatTargetR);
		D3DXVec3Normalize(&stPlane.vNormal, &stPlane.vNormal);
		stPlane.vOther.x = m_pmatTargetT->_41;
		stPlane.vOther.y = m_pmatTargetT->_42;
		stPlane.vOther.z = m_pmatTargetT->_43;
		return true;
	}

	return false;
}

bool cLocalEditor::IsPickRotate(OUT D3DXVECTOR3& vTransformDir, const ST_RAY& ray)
{
	ST_PLANE plane;
	D3DXVECTOR3 vPos;
	float fDist;

	plane.vOther.x = m_matWorld._41;
	plane.vOther.y = m_matWorld._42;
	plane.vOther.z = m_matWorld._43;

	plane.vNormal = D3DXVECTOR3(1, 0, 0);
	if (RayPickPointFromPlane(vPos, ray, plane))
	{
		fDist = D3DXVec3LengthSq(&(vPos - plane.vOther));

		if (fDist < 4.4f  && fDist > 3.6f)
		{
			vTransformDir = D3DXVECTOR3(1, 0, 0);
			return true;
		}
	}

	plane.vNormal = D3DXVECTOR3(0, 1, 0);
	if (RayPickPointFromPlane(vPos, ray, plane))
	{
		fDist = D3DXVec3LengthSq(&(vPos - plane.vOther));

		if (fDist < 4.4f  && fDist > 3.6f )
		{
			vTransformDir = D3DXVECTOR3(0, 1, 0);
			return true;
		}
	}

	plane.vNormal = D3DXVECTOR3(0, 0, 1);
	if (RayPickPointFromPlane(vPos, ray, plane))
	{
		fDist = D3DXVec3LengthSq(&(vPos - plane.vOther));

		if (fDist < 4.4f  && fDist > 3.6f )
		{
			vTransformDir = D3DXVECTOR3(0, 0, 1);
			return true;
		}
	}

	return false;
}

bool cLocalEditor::IsCollisionBox(const D3DXMATRIXA16 & matWorld,
	const ST_RAY & rayMouse, const D3DXVECTOR3& vHalfSize)
{
	D3DXVECTOR3 vDist, vAxis;
	vDist.x = matWorld._41;
	vDist.y = matWorld._42;
	vDist.z = matWorld._43;

	vDist -= rayMouse.vOri;

	float t = D3DXVec3Dot(&vDist, &rayMouse.vDir);

	if (t < 0) return false;

	vDist -= t * rayMouse.vDir;

	D3DXVec3TransformNormal(&vAxis, &D3DXVECTOR3(vHalfSize.x, 0, 0), &matWorld);
	float d = fabs(D3DXVec3Dot(&vDist, &vAxis));

	D3DXVec3TransformNormal(&vAxis, &D3DXVECTOR3(0, vHalfSize.y, 0), &matWorld);
	d += fabs(D3DXVec3Dot(&vDist, &vAxis));

	D3DXVec3TransformNormal(&vAxis, &D3DXVECTOR3(0, 0, vHalfSize.z), &matWorld);
	d += fabs(D3DXVec3Dot(&vDist, &vAxis));

	t = D3DXVec3LengthSq(&vDist);
	return (d * d > t * t);
}

bool cLocalEditor::RayPickPointFromPlane(OUT D3DXVECTOR3 & vPickPos, const ST_RAY & ray, const ST_PLANE& plane)
{
	float t = D3DXVec3Dot(&ray.vDir, &plane.vNormal);

	if (IsEqual(t, 0))
		return false;

	t = D3DXVec3Dot(&(plane.vOther - ray.vOri), &plane.vNormal) / t;

	if (t < 0)
		return false;

	vPickPos = ray.vOri + t * ray.vDir;

	return true;
}
