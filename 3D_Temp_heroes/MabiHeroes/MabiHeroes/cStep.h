#pragma once
#include "cStructure.h"


class cStep :
	public cStructure
{
	cSkinnedMesh* m_pMesh;
public:
	cStep();
	~cStep();

	void Setup();
	void Update();
	void Render();
};

