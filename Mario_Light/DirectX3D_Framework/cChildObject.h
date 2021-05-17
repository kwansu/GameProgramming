#pragma once
#include "cObject.h"

class cChildObject
{
protected:
	cObject*	m_pChild;
	cMatrixA*	m_pmatParentT;
	cMatrixA*	m_pmatParentR;
	cMatrixA	m_matLocal;

public:
	cChildObject();
	~cChildObject();
	void Setup(cObject* pChild, cMatrixA* pmatParentT,
		cMatrixA* pmatParentR, cMatrixA& matLocal);
	void Update();
	void Render();
	cObject* GetChildObject();
};

