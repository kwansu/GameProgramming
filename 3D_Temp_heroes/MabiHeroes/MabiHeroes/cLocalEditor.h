#pragma once
#include "cTransform.h"
#include "cPyramid.h"

enum eTRANSLATE_STATE
{
	UP = 0x0001,
	FRONT = 0x0010,
	RIGHT = 0x0100
};

class cLocalEditor
{
private:
	std::vector<cPyramid*>			m_vecPyramid;
	vector<ST_COLLISION_BOX_STICK>	m_vecBox;
	D3DXMATRIXA16*					m_pmatTargetT;
	D3DXMATRIXA16*					m_pmatTargetR;
	D3DXMATRIXA16					m_matWorld;
	D3DXMATRIXA16					m_matOffset;
	LPD3DXMESH						m_pMesh;
	D3DMATERIAL9					m_mtl;

public:
	cLocalEditor();
	~cLocalEditor();

	void Setup();
	void Update(const D3DXVECTOR3 & cameraPos);
	void Render();
	void RenderRotate();

	void SetTarget(D3DXMATRIXA16* pmatTargetT, D3DXMATRIXA16* pmatTargetR, const D3DXMATRIXA16* pmatOffset = NULL);
	DWORD IsPickPyramid(const ST_RAY& rayMouse);
	bool IsPickPlane(OUT ST_PLANE& stPlane, const ST_RAY& rayMouse);
	bool IsPickRotate(OUT D3DXVECTOR3& vTransformDir, const ST_RAY& ray);
	
private:
	bool IsCollisionBox(const D3DXMATRIXA16& matWorld, 
		const ST_RAY& rayMouse, const D3DXVECTOR3& vHalfSize);
	bool RayPickPointFromPlane(OUT D3DXVECTOR3& vPickPos, const ST_RAY& ray, const ST_PLANE& plane);
};

