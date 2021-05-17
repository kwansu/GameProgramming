#pragma once
#include "cTransform.h"

class cGameObject :
	public cTransform
{
	friend class cWorld;

public:
	cGameObject();
	virtual ~cGameObject();

	virtual void Setup() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

	virtual void Damaged(float fDamege, cGameObject* pAttacker, bool isSmash) {}

	virtual	void SetMovePoint(D3DXVECTOR3 vec3) {}
};

