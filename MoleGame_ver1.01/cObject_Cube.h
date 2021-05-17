#pragma once
#include "cObject.h"

class cObject_Cube :
	public cObject
{
protected:
	vector<stVertex_PC>	m_aVertexPC;
	vector<stVertex_PT>	m_aVertexPT;
	vector<int>			m_aTextureIndex;
	pTexture			m_pTexture;

public:
	vector<cVec3>		m_aLocalPos;

public:
	cObject_Cube();
	~cObject_Cube();

	void Setup();
	void Update();
	void Render();
	bool CubeCollision(cObject_Cube* pObject);
	bool IsCollision(cObject_Cube* pObject);
};

