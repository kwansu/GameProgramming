#pragma once
#include "cTransform.h"

#define CAMERA_MOVE_SPEED	8.0f
#define CAMERA_ROTATE_SPEED	0.3f
#define CAMERA_ZOOM_SPEED	0.01f
#define CAMERA_HEIGHT		9.9f
#define	COMEBACK_SPEED		20.f
#define	SMASH_COMEBACK_SPEED		95.f

enum CAMERA_MODE
{
	FLY_VIEW, ORIGIN_VIEW, TRAIL_VIEW
};

struct ST_Camera_Move
{
	bool	isEnable;
	bool	isSmashCam;
	float	fSpeed;
	float	fInDist;
	float	fTotalDist;
};

class cCamera :
	public cTransform
{
	SINGLETON(cCamera)

private:
	int				m_nEffectCount ;
	float			m_fFoV;
	float			m_fNear;
	float			m_fFar;
	float			m_fDist;
	float			m_fZBuffer;
	bool			m_isMouseRotate;
	bool			m_isUiLock;
	
	ST_Camera_Move	m_stCameraMove;

	D3DXVECTOR3		*m_pvTargetPos, m_vDefault;
	D3DXMATRIXA16	m_matView;
	D3DXMATRIXA16	m_matProj;
	RECT			m_rcClient;

	CAMERA_MODE		m_eCameraMode;

public:

	void Setup();
	void Update();
	void UpdateView();
	void UpdateProjection();
	void SetTarget(D3DXVECTOR3* pvTargetPos);
	void MousePickingRay(OUT ST_RAY* prayMouse);

	D3DXVECTOR3 GetTargetPos() { return m_vDefault; }
	float GetCamDistance() { return m_fDist; }

	void AddCamDistance(float fDelta) { m_fDist -= fDelta; }
	void SetCamAction(float fInDist, float fSpeed);
	void SetCamComeBack();
	void SetSmashCam();
	void CamVibrate();

	bool GetIsUiLock() { return m_isUiLock; }
	void SetIsUiLock(bool isUiLock) { m_isUiLock = isUiLock; }

private:
	void UpdateFlyView();
	void UpdateOriginView();
};

extern cCamera* g_pCamera;