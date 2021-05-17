#include "StdAfx.h"
#include "cCamera.h"


cCamera* g_pCamera = NULL;

cCamera::cCamera(void)
	: m_fDist(66)
	, m_fFoV(45)
	, m_fFar(4000)
	, m_fNear(1)
	, m_vDefault(0, 0, 0)
	, m_eCameraMode(ORIGIN_VIEW)
	, m_isMouseRotate(true)
	, m_nEffectCount(0)
	, m_isUiLock(false)
{
	D3DXMatrixIdentity(&m_matProj);
	m_matView = m_matProj;
	m_pvTargetPos = &m_vDefault;
}

cCamera::~cCamera(void)
{
}

void cCamera::Setup()
{
	UpdateProjection();
	SetPosition(10, 10, 10);
}

void cCamera::Update()
{
	if (m_stCameraMove.isEnable && m_stCameraMove.fInDist > 0)
	{
		m_stCameraMove.fInDist -= m_stCameraMove.fSpeed * g_fDeltaTime;
		m_stCameraMove.fTotalDist += m_stCameraMove.fSpeed * g_fDeltaTime;

		m_fDist -= m_stCameraMove.fSpeed * g_fDeltaTime;
	}
	if (!m_stCameraMove.isEnable && m_stCameraMove.fTotalDist > 0)
	{
		m_fDist += COMEBACK_SPEED * g_fDeltaTime;
		m_stCameraMove.fTotalDist -= COMEBACK_SPEED * g_fDeltaTime;
	}
	if (!m_stCameraMove.isEnable && m_stCameraMove.fTotalDist > 0 && !m_stCameraMove.isSmashCam)
	{
		m_fDist += SMASH_COMEBACK_SPEED * g_fDeltaTime;
		m_stCameraMove.fTotalDist -= SMASH_COMEBACK_SPEED * g_fDeltaTime;
	}

	if (g_pInput->IsKeyDown('T'))
		m_eCameraMode = CAMERA_MODE::FLY_VIEW;

	if (g_pInput->IsKeyDown('G'))
	{
		m_eCameraMode = CAMERA_MODE::ORIGIN_VIEW;
		m_vDefault = D3DXVECTOR3(0, 0, 0);
	}

	if (g_pInput->IsKeyDown(VK_MENU))
		m_isMouseRotate = m_isMouseRotate ? false : true;

	switch (m_eCameraMode)
	{
	case CAMERA_MODE::FLY_VIEW:
		UpdateFlyView();
		break;

	case CAMERA_MODE::ORIGIN_VIEW:
		UpdateOriginView();
		break;
	}

	if (m_nEffectCount > 0 && m_stCameraMove.fTotalDist <= 0)
	{
		--m_nEffectCount;

		float rnd = 0;
		float rnd2 = 0;
		rnd = rand() % 2 - 2;
		rnd2 = rand() % 6 - 6;
		m_vPos.x += rnd;
		m_vPos.y += rnd;
		m_vPos.z += rnd2;
		m_vDefault.x += rnd;
		m_vDefault.y += rnd;
		m_vDefault.z += rnd2;
	}

	UpdateDirection();
	UpdateView();

	D3DXMATRIXA16 matViewProj = m_matView * m_matProj;
	g_pNormalEffect->SetMatrix("gViewProjectionMatrix", &matViewProj);
	//g_pDiffuseEffect->SetMatrix("gmatViewProjection", &matViewProj);

	g_pNormalEffect->SetVector("gCameraPos", &D3DXVECTOR4(m_vPos, 1));

	g_pNormalEffect->SetFloatArray("garrLightPos", g_pLightManager->GetActiveLightsPosArray(), 12);
	g_pNormalEffect->SetInt("nLightNum", g_pLightManager->GetActiveLightNum());
	//g_pDiffuseEffect->SetFloatArray("garrLightPos", g_pLightManager->GetActiveLightsPosArray(), 12);
	//g_pDiffuseEffect->SetInt("nLightNum", g_pLightManager->GetActiveLightNum());
}

void cCamera::UpdateView()
{
	D3DXMatrixLookAtLH(&m_matView, &m_vPos, &m_vDefault, &D3DXVECTOR3(0, 1, 0));
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &m_matView);
}

void cCamera::UpdateProjection()
{
	GetClientRect(g_hWnd, &m_rcClient);
	D3DXMatrixPerspectiveFovLH(&m_matProj, D3DXToRadian(m_fFoV),
		m_rcClient.right / (float)m_rcClient.bottom, m_fNear, m_fFar);

	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);

	m_fZBuffer = 1.0f / tan(D3DXToRadian(m_fFoV / 2.0f));
}

void cCamera::SetTarget(D3DXVECTOR3 * pvTargetPos)
{
	m_pvTargetPos = pvTargetPos;
}

void cCamera::MousePickingRay(OUT ST_RAY * prayMouse)
{
	D3DXMATRIXA16 matViewIn;
	D3DXMatrixInverse(&matViewIn, NULL, &m_matView);

	POINT mousePos = g_pInput->GetMousePos();

	prayMouse->vDir.x = mousePos.x * 2.f - m_rcClient.right;
	prayMouse->vDir.y = m_rcClient.bottom - mousePos.y * 2.f;
	prayMouse->vDir.z = (float)m_rcClient.bottom * m_fZBuffer;

	D3DXVec3TransformNormal(&prayMouse->vDir, &prayMouse->vDir, &matViewIn);
	D3DXVec3Normalize(&prayMouse->vDir, &prayMouse->vDir);

	prayMouse->vOri = m_vPos;
}

void cCamera::UpdateFlyView()
{
	if (g_pInput->IsKeyPress(VK_RBUTTON))
	{
		m_vRot.x += g_pInput->GetMouseInterval().y * CAMERA_ROTATE_SPEED;
		m_vRot.y += g_pInput->GetMouseInterval().x * CAMERA_ROTATE_SPEED;

		if (m_vRot.x > 80) m_vRot.x = 80;
		if (m_vRot.x < -60) m_vRot.x = -60;
	}

	UpdateRotation();
	UpdateDirection();

	if (g_pKeyManager->IsStayKeyDown('W'))
		m_vPos += m_vDir * CAMERA_MOVE_SPEED;
	
	if (g_pKeyManager->IsStayKeyDown('S'))
		m_vPos -= m_vDir * CAMERA_MOVE_SPEED;

	if (g_pKeyManager->IsStayKeyDown('A'))
		m_vPos -= m_vRight * CAMERA_MOVE_SPEED;

	if (g_pKeyManager->IsStayKeyDown('D'))
		m_vPos += m_vRight * CAMERA_MOVE_SPEED;

	D3DXVec3TransformCoord(&m_vDefault
		, &D3DXVECTOR3(0, 0, m_fDist), &m_matR);

	m_vDefault += m_vPos;
}

void cCamera::UpdateOriginView()
{
	if (!m_isUiLock)
	{
		if (m_isMouseRotate)
		{
			m_vRot.x += g_pInput->GetMouseInterval().y * CAMERA_ROTATE_SPEED;
			m_vRot.y += g_pInput->GetMouseInterval().x * CAMERA_ROTATE_SPEED;

			if (m_vRot.x > 60) m_vRot.x = 60;
			if (m_vRot.x < -20) m_vRot.x = -20;
		}
	}
	

	if (g_pInput->GetMouseWheel())
		m_fDist -= g_pInput->GetMouseWheel() * CAMERA_ZOOM_SPEED;

	if (m_fDist < 17)	m_fDist = 17;	
	if (m_fDist > 66)	m_fDist = 66;


	UpdateRotation();

	D3DXVECTOR3 vCamPos(0, 0, -m_fDist);


	D3DXVec3TransformCoord(&m_vPos
		, &vCamPos, &m_matR);

	if (m_pvTargetPos)
	{
		m_vDefault = *m_pvTargetPos;
		m_vDefault.y += CAMERA_HEIGHT;
		m_vPos += m_vDefault;
	}
}

void cCamera::SetCamAction(float fInDist, float fSpeed)
{
	m_stCameraMove.isEnable = true;
	m_stCameraMove.fSpeed = fSpeed;
	m_stCameraMove.fInDist = fInDist;
}

void cCamera::SetCamComeBack()
{
	m_stCameraMove.isEnable = false;
}

void cCamera::SetSmashCam()
{
	m_stCameraMove.isSmashCam = false;
}

void cCamera::CamVibrate()
{
	m_nEffectCount = 7;
}	