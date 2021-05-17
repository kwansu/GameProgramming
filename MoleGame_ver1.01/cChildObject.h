#pragma once
#include "cObject.h"

class cChildObject
{
public:
	cObject*	m_pChildObject;
	cMatrixA	m_matPos, m_matWorld;
	cMatrixA*	m_pMatParentWorld;

public:
	cChildObject(cMatrixA* pParentWorld = NULL);
	~cChildObject();
	void Setup();
	void Update();
	void Render();
};

