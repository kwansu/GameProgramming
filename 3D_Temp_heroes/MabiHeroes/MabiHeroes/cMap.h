#pragma once
#include "cStructure.h"
#include "cSkinnedMesh.h"

class cMap :
	public cStructure
{

public:
	cMap();
	~cMap();

	virtual void Setup() override;
};

