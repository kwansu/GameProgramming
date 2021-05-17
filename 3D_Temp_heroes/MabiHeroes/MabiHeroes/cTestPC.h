#pragma once
#include "cTransform.h"

class cTestPC :
	public cTransform
{
	friend class cWorld;

private:
	float		m_fMoveRadius;
	LPD3DXMESH	m_pMesh;
	cWorld*		m_pWorld;

public:
	cTestPC();
	~cTestPC();

	void Setup(cWorld* pWorld);
	void Update();
	void Render();
};

