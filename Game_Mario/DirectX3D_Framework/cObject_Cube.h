#pragma once
#include "cObject.h"
#include "cCollider.h"

class cObject_Cube :
	public cObject
{
protected:
	vector<cVec3>		m_aLocalPos;
	vector<Vertex_PC>	m_aVertexPC;

	cCollider*			m_pCollider;

public:
	cObject_Cube();
	~cObject_Cube();
	void Setup();
	void Update();
	void Render();
	// 3���� ȸ�������� �ڽ��浹 �Լ�.
	bool CubeCollision(cObject_Cube* pObject);
	bool IsCollision(cObject_Cube* pObject);
	// AABB�浹�˻�. �浹��, �浹������ ä���ش�.
	bool CollisionDetection(cVec3* pvOut, cObject_Cube* pConflictor);
	void TransformVertexMin(cVec3* pvOut);
	void TransformVertexMax(cVec3* pvOut);
	void SetLocalSize(float sx, float sy, float sz);
	cCollider* GetCollider();
};

