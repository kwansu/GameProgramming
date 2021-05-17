#include "stdafx.h"
#include "cObject_Camera.h"


cObject_Camera::cObject_Camera()
	: m_fDistance(70), m_fFar(1000), m_fFOV(45), m_nFrameCount(0)
	, m_fNear(1), m_pVecTargetPos(NULL), m_vecOri(0, 0 ,0)
{
	D3DXMatrixIdentity(&m_matProj);
	D3DXMatrixIdentity(&m_matView);
}


cObject_Camera::~cObject_Camera()
{
}


void cObject_Camera::Setup()
{
	m_fAngleY = 90;
	m_fAngleX = 35;
	UpdateProjection();
}


void cObject_Camera::Update()
{
	if (g_bCollision)
	{
		g_bCollision = false;
		m_nFrameCount = 15;
	}
	if (g_pInput->IsKeyPress(VK_LBUTTON))
	{
		m_fAngleX += g_pInput->GetMouseInterval().y * CAMERA_ROTATE_SPEED;
		m_fAngleY += g_pInput->GetMouseInterval().x * CAMERA_ROTATE_SPEED;
		if (m_fAngleX > 80)		m_fAngleX = 80;
		if (m_fAngleX < -30)		m_fAngleX = -30;
	}

	if (g_pInput->IsKeyPress(VK_DOWN))
		m_fDistance += CAMERA_ZOOM_SPEED;

	if (g_pInput->IsKeyPress(VK_UP))
		m_fDistance -= CAMERA_ZOOM_SPEED;

	if (g_pInput->GetMouseWheel())
		m_fDistance -= g_pInput->GetMouseWheel() * 0.01;

	if (m_fDistance < 10)
		m_fDistance = 10;

	UpdateRotateMatrix();
	D3DXVec3TransformCoord(&m_vecPos, &cVec3(0, 0, -m_fDistance),&m_matRot);
	m_vecPos += m_vecOri;

	if (m_nFrameCount)
	{
		m_vecPos += cVec3(rand() % 1, rand() % 4, rand() % 4);
		--m_nFrameCount;
	}

	UpdateProjection();
	UpdateView();
}


void cObject_Camera::Render()
{
}


void cObject_Camera::UpdateView()
{
	if (!m_pVecTargetPos)
		m_pVecTargetPos = &m_vecOri;

	D3DXMatrixLookAtLH(&m_matView, &m_vecPos,
		m_pVecTargetPos, &cVec3(0, 1, 0));

	g_pDDevice->SetTransform(D3DTS_VIEW, &m_matView);
}


void cObject_Camera::UpdateProjection()
{
	RECT rcClient;
	GetClientRect(g_hWnd, &rcClient);

	D3DXMatrixPerspectiveFovLH(&m_matProj, D3DXToRadian(m_fFOV),
		(float)rcClient.right / rcClient.bottom,
		m_fNear, m_fFar);

	g_pDDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);
}


void cObject_Camera::SetTarget(cObject* pTarget)
{
	m_pVecTargetPos = pTarget->GetPosition();
}
