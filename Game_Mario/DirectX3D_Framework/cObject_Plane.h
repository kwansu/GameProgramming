#pragma once
#include "cObject_Cube.h"

class cObject_Plane :
	public cObject_Cube
{
	float	m_fMaxInterval;
	float	m_fInterval;
	float	m_fVelocity;
	bool	m_bMove;

public:
	cObject_Plane();
	~cObject_Plane();
	void Setup(float sx, float sy, float sz
		, D3DCOLOR color = D3DCOLOR_XRGB(0, 0, 0));
	void Update();
	//void Render();
	void SetColor(D3DCOLOR color);		// 기본 50~210사이는 사용중. 합쳐서 RGB를 초과하지않도록
	void SetMovePlane(float fMaxInterval, float fSpeed = 1);
};

