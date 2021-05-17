#pragma once
#include "cObject.h"

#define CAMERA_MOVE_SPEED	0.1f
#define CAMERA_ROTATE_SPEED	0.2f
#define CAMERA_ZOOM_SPEED	0.3f

class cObject_Camera :
	public cObject
{
	float		m_fDistance;
	float		m_fFOV;
	float		m_fNear;
	float		m_fFar;
	int			m_nFrameCount;

	cVec3*		m_pVecTargetPos;
	cMatrixA	m_matView;
	cMatrixA	m_matProj;
	cVec3		m_vecOri;

public:
	cObject_Camera();
	~cObject_Camera();

	void Setup();
	void Update();
	void Render();
	void UpdateView();
	void UpdateProjection();
	void SetTarget(cObject* pTarget);
};

