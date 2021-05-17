#pragma once

class cCollider
{
protected:
	vector<cVec3>	m_aVertex;
	cMatrixA*		m_pmatWorld;
	cVec3			m_vMax, m_vMin;
	
public:
	cCollider(cMatrixA* pmatWorld);
	~cCollider();
	void Setup(vector<cVec3>* paVertex);
	void Update();
	void Render();
	bool InterceptCube(cVec3* pvOut, cCollider* pCollider);
	void SetMinMax(cCollider* pCollider);
	void Setup();
};

