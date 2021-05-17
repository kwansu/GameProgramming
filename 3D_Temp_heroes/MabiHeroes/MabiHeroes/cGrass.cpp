#include "stdafx.h"
#include "cGrass.h"


cGrass::cGrass()
{
	m_nIndex = 35;
}


cGrass::~cGrass()
{
}

void cGrass::Setup()
{
	cStructure::Setup();
	m_pSkinnedMesh = new cSkinnedMesh;

	ST_SPHERE sp;
	m_pSkinnedMesh->LoadNew("./MapData/objects/grass/", "grassS.X", sp);
}
