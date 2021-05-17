#pragma once
#include "cTransform.h"

class cPlane :
	public cTransform
{
	friend class cWorld;
private:
	ST_COLLISION_PLANE	m_collPlane;

public:
	cPlane();
	~cPlane();

	void Setup(float hx, float hz);
	void UpdateCollision();
	void Render();
};

