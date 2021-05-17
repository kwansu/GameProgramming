#pragma once

// �浹ü�� �׷��ִ� �̱��� Ŭ����
class cCollisionRender
{
	SINGLETON(cCollisionRender);

private:
	LPD3DXMESH		m_pMeshBox;
	LPD3DXMESH		m_pMeshSphere;
	D3DMATERIAL9	m_mtl;
	D3DXMATRIXA16	m_matWorld;

public:
	void Setup();
	void Destroy();

	void RenderSphere(const D3DXVECTOR3& vOri, float fRadius);
	void RenderBox(const D3DXVECTOR3& vCenter, const D3DXVECTOR3& vHalfSize);
	void RenderBox(const ST_COLLISION_BOX_STICK& box, const D3DXCOLOR* pColor = NULL);
	void RenderBoxAlpha(const ST_COLLISION_BOX_STICK& box, const D3DXCOLOR color);
};

extern cCollisionRender* g_pCollisionRender;
