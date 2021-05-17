#pragma once
#include "cStructure.h"
#include "cSkinnedMesh.h"

class cGrass :
	public cStructure
{

public:
	cGrass();
	~cGrass();

	virtual void Setup() override;

};

