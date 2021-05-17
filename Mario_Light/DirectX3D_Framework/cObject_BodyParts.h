#pragma once
#include "cObject_Cube.h"
#include "cChildObject.h"

class cObject_BodyParts
	: public cObject
{
	cChildObject	m_childCube;

public:
	cObject_BodyParts();
	~cObject_BodyParts();
	void Setup();
	void Update();
	void Render();
};

