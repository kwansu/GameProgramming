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
	// 3차원 회전가능한 박스충돌 함수.
	bool CubeCollision(cObject_Cube* pObject);
	bool IsCollision(cObject_Cube* pObject);
	// AABB충돌검사. 충돌시, 충돌범위를 채워준다.
	bool CollisionDetection(cVec3* pvOut, cObject_Cube* pConflictor);
	void TransformVertexMin(cVec3* pvOut);
	void TransformVertexMax(cVec3* pvOut);
	void SetLocalSize(float sx, float sy, float sz);
	cCollider* GetCollider();
};

