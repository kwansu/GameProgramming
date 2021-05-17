#pragma once
#include "cStructure.h"
#include "cSkinnedMesh.h"

class cCeilling :
	public cStructure
{

public:
	cCeilling();
	~cCeilling();

	virtual void Setup() override;
};

class cFloor :
	public cStructure
{

public:
	cFloor();
	~cFloor();

	virtual void Setup() override;
};
