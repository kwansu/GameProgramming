#pragma once
#include "cObject_Cube.h"

class cObject_Limbs :
	public cObject_Cube
{
protected:
	cMatrixA*	m_pmatParent;
	cMatrixA	m_matLocal;
	float		m_fSwingSpeed;
	bool		m_bWalk;
	bool		m_bRight;
	
public:
	cObject_Limbs(bool bRight);
	~cObject_Limbs();
	void Setup(cMatrixA* pmatParent, float px, float py, float pz);
	void Update();
	void Render();
	void Walking();
};

